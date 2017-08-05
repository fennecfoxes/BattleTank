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

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetPlayerTank() && GetControlTank())
	{
		// TODO Move towards player

		// Aim towards player
		GetControlTank()->AimAt(GetPlayerTank()->GetActorLocation());

		// Fire towards player
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
