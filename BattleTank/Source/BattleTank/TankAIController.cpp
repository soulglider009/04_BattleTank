// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleTank.h"
#include "Tank.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	PossessedTank = GetControlledTank();
	if (PossessedTank == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("No Tank Possessed in AI Controller"));
	}

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Find player location(if there, might be dead), aim there
	Player = GetPlayer();
	if (Player)
	{
		//TODO Move toward player

		PossessedTank->AimAt(Player->GetActorLocation());

		//Fire at player
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("%s could not find Player"), *(PossessedTank->GetName()));
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

