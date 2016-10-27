// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTracks.h"



void UTankTracks::BeginPlay()
{
	Super::BeginPlay();
	auto SpeedInMetersPerSecond = SpeedConverter(MaxSpeed);
	MaxDrivingForce = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent())->GetMass() * (SpeedInMetersPerSecond/ TimeToMaxSpeed);
	

}

///TODO add forward + backward reading on tank and multiply
void UTankTracks::SetThrottle(float Throttle)
{

	//TODO clamp actual throttle value

	auto ForceApplied = GetForwardVector() * Throttle * MaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);

}

//Takes Kilometers per hour and converts to meters per second
float UTankTracks::SpeedConverter(float KilometerPerHour)
{
	return (KilometerPerHour * 1000 / 60 / 60);
}
