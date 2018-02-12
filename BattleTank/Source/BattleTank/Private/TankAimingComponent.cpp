// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::BeginPlay()
{
	// So that first fire is after initial reload
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	FVector OutLaunchVelocity;
	FVector StartLocation;

	// Check if turret and barrel reference is set
	if (!ensure(Barrel))
	{
		return;
	}

	if (!ensure(Turret))
	{
		return;
	}

	// Find end of barrel
	StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	// For use of logging
	auto TankName = GetOwner()->GetName();
	auto BarrelLocation = Barrel->GetComponentLocation();

	// Calculate OutLaunchVelocity
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, HitLocation, LaunchSpeed, 
																			false, 0.0f, 0.0f, ESuggestProjVelocityTraceOption::DoNotTrace);
	if (bHaveAimSolution)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		//UE_LOG(LogTemp, Warning, TEXT("Tank %s aiming at %s with barrel direction %s with launch speed %f"), *TankName, *HitLocation.ToString(), *AimDirection.ToString(), LaunchSpeed);

		MoveBarrelTurretTowards(AimDirection);
		// LOG
		auto time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("%f: Barrel elevate called"), time);
	}
	else
	{
		// LOG
		auto time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("%f: No aim solve found"), time);
	}
}

void UTankAimingComponent::MoveBarrelTurretTowards(FVector AimDirection)
{
	if (!ensure(Barrel))
	{
		return;
	}

	if (!ensure(Turret))
	{
		return;
	}

	// Work-out difference between current barrel direction and aim direction
	auto BarrelRotation = Barrel->GetForwardVector().Rotation(); /// Current barrel rotation (roll pitch yaw)
	auto AimRotation = AimDirection.Rotation(); /// barrel rotation to aim to
	auto DeltaRotator = AimRotation - BarrelRotation;

	auto TankName = GetOwner()->GetName();
	//UE_LOG(LogTemp, Warning, TEXT("Tank %s barrel rotation aiming %s"), *TankName, *AimRotation.ToString());

	Barrel->Elevate(DeltaRotator.Pitch);

	// Always yaw the shortest way
	if (FMath::Abs(DeltaRotator.Yaw) < 180)
	{
		Turret->Rotate(DeltaRotator.Yaw);
	}
	else
	{
		Turret->Rotate(-DeltaRotator.Yaw);
	}
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	if (RoundsLeft <= 0)
	{
		FiringState = EFiringStatus::OutOfAmmo;
	}
	else if (((FPlatformTime::Seconds()) - LastFireTime) < ReloadTimeInSec)
	{
		FiringState = EFiringStatus::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringStatus::Aiming;
	}
	else
	{
		FiringState = EFiringStatus::Locked;
	}
}

void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel && ProjectileBlueprint))
	{
		return;
	}

	if (FiringState == EFiringStatus::Locked || FiringState == EFiringStatus::Aiming)
	{
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("Projectile")), Barrel->GetSocketRotation(FName("Projectile")));
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
		RoundsLeft--;
	}
}

int UTankAimingComponent::GetRoundsLeft() const
{
	return RoundsLeft;
}

EFiringStatus UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel))
	{
		return false;
	}

	auto BarrelForward = Barrel->GetForwardVector();

	return !BarrelForward.Equals(AimDirection, 0.01);
}