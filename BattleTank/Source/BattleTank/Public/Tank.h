// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// Forward declarations
class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	// Aims tank at given location
	void AimAt(FVector HitLocation);

	// Fire projectile
	UFUNCTION(BlueprintCallable, Category = Setup)
	void Fire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Aiming component
	UTankAimingComponent* TankAimingComponent = nullptr;

private:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Sets barrel reference in tankaimingcomponent
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	// Sets turret reference in tankaimingcomponent
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurret * TurretToSet);

	// Projectile
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	// Projectile speed
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 40000;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSec = 3;

	UTankBarrel* Barrel = nullptr;

	
	
	double LastFireTime = 0;
};