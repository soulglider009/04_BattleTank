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

	virtual void BeginPlay() override;
	
private:

	UTankTracks();

	void ApplySidewaysForce();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	//F(newtons) = M(KG) * A(m/s^2). This is derived from the Tank's primitive component mass and designer setup max speed and time to max speed.
	float MaxDrivingForce = 70000000;
	void DriveTrack();

	float CurrentThrottle = 0.0f;
};
