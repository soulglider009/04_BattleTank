// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"


void UTankBarrel::Elevate(float RelativeSpeed)
{
	//Move right amount this frame
	auto ElevationChange = FMath::Clamp(RelativeSpeed, -1.0f, 1.0f) * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds; //Makes it framerate independent (if a frame is long or short, this will still change correctly)

	//Relative rotation is a property of the scene component, basically just the rotation relative to its parent.
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	auto Elevation = FMath::Clamp(RawNewElevation, MinElevation, MaxElevation);
	
	SetRelativeRotation(FRotator(Elevation, 0.0f, 0.0f));
}