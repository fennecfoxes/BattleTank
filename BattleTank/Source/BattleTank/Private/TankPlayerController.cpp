// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("TankPlayerController BeginPlay"));

	auto ControlTank = GetControlTank();
	if (!ControlTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("TankPlayerController not possessing a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TankPlayerController possessing %s"), *ControlTank->GetName());
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}

// Return tank that is being controlled
ATank* ATankPlayerController::GetControlTank() const
{
	return Cast<ATank>(GetPawn());
}

// Tell tank to aim towards crosshair
void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlTank())
	{
		UE_LOG(LogTemp, Warning, TEXT("TankPlayerController not possessing a tank, cannot aim towards crosshair"));
		return;
	}

	FVector HitLocation; // Out parameter

	if (GetSightRayHitLocation(HitLocation))
	{
		UE_LOG(LogTemp, Warning, TEXT("Hitlocation hitting %s"), *HitLocation.ToString());

		
		//tell tank to aim at the location
	}
}

// Get world location with linetrace through crosshair
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	int32 ViewportSizeX, ViewportSizeY; // size of current viewport (window screen)
	FVector LookDirection;

	/// Find xhair position
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
	UE_LOG(LogTemp, Warning, TEXT("Screen location is %s"), *ScreenLocation.ToString());

	/// de-project screen position of xhair to world direction
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		/// line-trace along world look direction to see what we hit (up to max range)
		if (GetLookVectorHitLocation(LookDirection, OutHitLocation))
		{
			return true;
		}
	}

	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& OutLookDirection) const
{
	FVector CameraWorldLocation; // not being used

	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, OutLookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + LookDirection * LineTraceRange;

	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility))
	{
		OutHitLocation = HitResult.Location;
		return true;
	}

	return false;
}
