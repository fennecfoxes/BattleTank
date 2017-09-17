// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"


void UTankTrack::SetThrottle(float Throttle) 
{
	// TODO - Clamp throttle value so player can't override


	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent()); // Getting root tank body in tank blueprint

	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

