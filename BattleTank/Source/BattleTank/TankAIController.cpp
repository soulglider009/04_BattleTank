// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "Tank.h" //So we can implement OnDeath
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
	if (AimingComponent->GetFiringState() == EFiringStatus::Ready)
	{
		AimingComponent->Fire();
	}
}

void ATankAIController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; };
		
		//Registers with the possessed tank for the on death broadcast
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
	}
}

void ATankAIController::OnPossessedTankDeath()
{
	//DetachFromControllerPendingDestroy()
	if (!ensure(GetPawn())) { return; } //TODO remove if OK. Production code should not be crashing the game
	GetPawn()->DetachFromControllerPendingDestroy();
	UE_LOG(LogTemp, Warning, TEXT("AI Tank dead"));
}


