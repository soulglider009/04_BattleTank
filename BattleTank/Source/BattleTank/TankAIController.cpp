// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"
//Depends on movement component via pathfinding


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Find the player
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!ensure(PlayerTank && AimingComponent)){ return; }
	//TODO Move toward player
	MoveToActor(PlayerTank, AcceptanceRadius);//TODO check radius is in cm of acceptance radius

	//Aim at the player
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	//Fire
	AimingComponent->Fire();
}


