// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTracks.h"
#include "TankMovementComponent.h"


void UTankMovementComponent::Initialise(UTankTracks* LeftTrackToSet, UTankTracks* RightTrackToSet)
{

	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	//auto TankName = GetOwner()->GetName();
	//UE_LOG(LogTemp, Warning, TEXT("%s is requesting to move at %s"), *TankName, *MoveVelocity.GetSafeNormal().ToString());

	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	//My guess, will get forward vector, then will send some kind of movement on the tracks to aim that direction for forward and left/right (from 0 to 1 on the throw)
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!LeftTrack || !RightTrack)
	{
		UE_LOG(LogTemp, Error, TEXT("No LeftTrack or RightTrack on TankMovementComponent"));
		return;
	}
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
	//TODO prevent double speed
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!LeftTrack || !RightTrack)
	{
		UE_LOG(LogTemp, Error, TEXT("No LeftTrack or RightTrack on TankMovementComponent"));
		return;
	}
	LeftTrack->SetThrottle(Throw);

	//TODO prevent double speed
}

void UTankMovementComponent::IntendTurnLeft(float Throw)
{
	if (!LeftTrack || !RightTrack)
	{
		UE_LOG(LogTemp, Error, TEXT("No LeftTrack or RightTrack on TankMovementComponent"));
		return;
	}
	RightTrack->SetThrottle(Throw);
	//TODO prevent double speed
}
