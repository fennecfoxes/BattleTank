// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

void UTankBarrel::Elevate(float DegreesPerSecond)
{
	// Move barrel the right amount this frame given barrel movement speed and frame time
	UE_LOG(LogTemp, Warning, TEXT("Barrel elevate called at speed %f"), DegreesPerSecond);
}


