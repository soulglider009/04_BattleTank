// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTracks;

/**
 * Responsible for driving the tank tracks TODO fix movement to always work and not have strange right turn issues
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankTracks* LeftTrackToSet, UTankTracks* RightTrackToSet);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void IntendMoveForward(float Throw);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void IntendTurnRight(float Throw);
	
private:
	//Call from pathfinding logic by AI controller
	void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

	UTankTracks* LeftTrack = nullptr;
	UTankTracks* RightTrack = nullptr;

};
