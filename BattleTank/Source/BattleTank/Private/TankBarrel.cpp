// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

// Move barrel the right amount this frame given barrel movement speed and frame time
void UTankBarrel::Elevate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);

	/// Calculate elevation change based on speed, max degrees per second, and framerate
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;

	/// Get new elevation given currentn elevation and elevation change
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;

	/// Restrict elevation based on min and max elevation degrees
	auto NewElevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);
	//UE_LOG(LogTemp, Warning, TEXT("Barrel RawNewElevation: %f"), NewElevation);

	SetRelativeRotation(FRotator(NewElevation, 0, 0));
}


