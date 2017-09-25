// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!LeftTrackToSet || !RightTrackToSet)
	{
		UE_LOG(LogTemp, Warning, TEXT("TankMovementComponent: Left or right track to set not set!"));
		return;
	}

	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!LeftTrack|| !RightTrack)
	{
		UE_LOG(LogTemp, Warning, TEXT("TankMovementComponent: MoveForward Left or right track to set not set!"));
		return;
	}

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);

	// TODO - prevent double speed due to due control use
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!LeftTrack || !RightTrack)
	{
		UE_LOG(LogTemp, Warning, TEXT("TankMovementComponent: MoveRight Left or right track to set not set!"));
		return;
	}

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}