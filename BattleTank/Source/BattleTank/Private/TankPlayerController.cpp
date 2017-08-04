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

ATank* ATankPlayerController::GetControlTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlTank())
	{
		UE_LOG(LogTemp, Warning, TEXT("TankPlayerController not possessing a tank, cannot aim towards crosshair"));
		return;
	}

	// Get world location with linetrace through crosshair
	// If it hits the landscape, tell tank to aim at the location
}
