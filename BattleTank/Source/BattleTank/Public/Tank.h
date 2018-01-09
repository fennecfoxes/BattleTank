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
class UTankMovementComponent;

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
	// Aiming component
	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent* TankAimingComponent = nullptr;

	// Movement component
	UPROPERTY(BlueprintReadOnly)
	UTankMovementComponent* TankMovementComponent = nullptr;

private:
	virtual void BeginPlay() override;

	// Projectile
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	// Projectile speed
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 40000;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSec = 3;

	UTankBarrel* Barrel = nullptr; // TODO remove

	double LastFireTime = 0;
};