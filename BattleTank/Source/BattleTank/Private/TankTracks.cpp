// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTracks.h"



///TODO add forward + backward reading on tank and multiply
void UTankTracks::SetThrottle(float Throttle)
{

	auto ForceApplied = GetForwardVector() * Throttle * MaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);

}