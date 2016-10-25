// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ATank* PossessedTank = GetControlledTank();
	if (PossessedTank == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Tank Possessed in AI Controller"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI possessing %s"), *(PossessedTank->GetName()));
	}

	Player = GetPlayer();
	if (!Player) 
	{
		UE_LOG(LogTemp, Warning, TEXT("%s could not find Player"), *(PossessedTank->GetName()));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("%s found Player %s"), *(PossessedTank->GetName()), *(Player->GetName()));
	}
}

ATank * ATankAIController::GetPlayer()
{
	auto PlayerPawn =  GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) { return nullptr; }
	return Cast<ATank>(PlayerPawn);
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}