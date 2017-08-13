// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);

	/// Calculate elevation change based on speed, max degrees per second, and framerate
	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;

	/// Get new elevation given currentn elevation and elevation change
	auto NewRotation = RelativeRotation.Yaw + RotationChange;

	UE_LOG(LogTemp, Warning, TEXT("Barrel NewRotation: %f"), NewRotation);

	SetRelativeRotation(FRotator(0, NewRotation, 0));
}


