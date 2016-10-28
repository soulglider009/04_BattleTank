// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleTank.h"
#include "Tank.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Find the player
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto PossessedTank = Cast<ATank>(GetPawn());

	//Protect null pointer
	if (PlayerTank && PossessedTank)	{ 
		//TODO Move toward player
		MoveToActor(PlayerTank, AcceptanceRadius);//TODO check radius is in cm of acceptance radius


		//Aim at the player
		PossessedTank->AimAt(PlayerTank->GetActorLocation());

		//Fire
		PossessedTank->Fire();

	}else{
		UE_LOG(LogTemp, Warning, TEXT("%s could not find Player or Self"), *(GetPawn()->GetName()));
		return;
	}
}


