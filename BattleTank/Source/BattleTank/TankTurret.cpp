// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTurret.h"



void UTankTurret::YawRotate(float RelativeSpeed)
{

	//rotates toward new direction depending on delta time not frames, delinks from frame
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
	auto YawChange =  RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;

	//Relative rotation is a property of the scene component, basically just the rotation relative to its parent.
	auto NewYaw = RelativeRotation.Yaw + YawChange;

	SetRelativeRotation(FRotator(0, NewYaw, 0));
}
