// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true; // TODO should this tick?

	// ...
}


void UTankAimingComponent::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	FVector OutLaunchVelocity;
	FVector StartLocation;

	// Check if barrel reference is set
	if (!Barrel)
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
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		//UE_LOG(LogTemp, Warning, TEXT("Tank %s aiming at %s with barrel direction %s with launch speed %f"), *TankName, *HitLocation.ToString(), *AimDirection.ToString(), LaunchSpeed);

		MoveBarrelTowards(AimDirection);

		// LOG
		auto time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: Barrel elevate called"), time);
	}
	else
	{
		// LOG
		auto time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: No aim solve found"), time);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	// Work-out difference between current barrel direction and aim direction
	auto BarrelRotation = Barrel->GetForwardVector().Rotation(); /// Current barrel rotation (roll pitch yaw)
	auto AimRotation = AimDirection.Rotation(); /// barrel rotation to aim to
	auto DeltaRotator = AimRotation - BarrelRotation;

	auto TankName = GetOwner()->GetName();
	//UE_LOG(LogTemp, Warning, TEXT("Tank %s barrel rotation aiming %s"), *TankName, *AimRotation.ToString());

	Barrel->Elevate(5);
}
