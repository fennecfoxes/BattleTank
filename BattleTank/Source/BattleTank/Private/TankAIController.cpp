// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("TankAIController BeginPlay"));

	auto ControlTank = GetPlayerTank();
	if (!ControlTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("TankAIController not finding player tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TankAIController found %s"), *ControlTank->GetName());
	}
}

ATank* ATankAIController::GetControlTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}
