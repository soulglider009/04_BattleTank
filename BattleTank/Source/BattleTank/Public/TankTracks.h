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

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = INPUT)
	void SetThrottle(float Throttle);



private:

	float SpeedConverter(float KilometerPerHour);

	//F(newtons) = M(KG) * A(m/s^2). This is derived from the Tank's primitive component mass and designer setup max speed and time to max speed.
	float MaxDrivingForce;

	//Max Speed in km per hour, which in code is then calculated to meters per second
	UPROPERTY(EditDefaultsOnly, Category = Movement)
	float MaxSpeed = 15000;

	//Time to get to max speed in seconds
	UPROPERTY(EditDefaultsOnly, Category = Movement)
	float TimeToMaxSpeed = 2;
};
