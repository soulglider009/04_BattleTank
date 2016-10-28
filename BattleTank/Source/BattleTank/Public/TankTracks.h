// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTracks.generated.h"

/**
 * Tank Track is used to set maximum driving force, and to apply forces to the tank.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTracks : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = INPUT)
	void SetThrottle(float Throttle);



private:

	//F(newtons) = M(KG) * A(m/s^2). This is derived from the Tank's primitive component mass and designer setup max speed and time to max speed.
	float MaxDrivingForce = 30000000;

};
