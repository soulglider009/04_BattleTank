// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), hidecategories = ("Collision", "Physics"))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// -1 is max, +1 is max up movement
	void Elevate(float RelativeSpeed);

private:

	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegressPerSecond = 20;

	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxElevation = 80; 

	UPROPERTY(EditAnywhere, Category = Setup)
	float MinElevation = 0; 
};
