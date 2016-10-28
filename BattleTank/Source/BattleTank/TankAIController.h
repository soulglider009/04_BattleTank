// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:

	//how close can the AI tank get to the player before it stops moving (probably want it to be somewhere between half it's range and full range)
	UPROPERTY(EditDefaultsOnly, Category = Pathfinding)
	float AcceptanceRadius = 1000.0f;
};
