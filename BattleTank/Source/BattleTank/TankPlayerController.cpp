// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"



void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	ATank* PossessedTank = GetControlledTank();
	if (PossessedTank == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Tank Possessed in Player Controller"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing %s"), *(PossessedTank->GetName()));
	}
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}