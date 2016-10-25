// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // must be last include

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	
private:
	ATank* GetControlledTank() const;

	UPROPERTY(EditAnywhere)
		float LineTraceRange = 1000000.0f;

	void BeginPlay() override;

	void Tick(float DeltaTime) override;

	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector& HitLocation) const;

	UPROPERTY(EditAnywhere) //Still just doesn't seem good, due to having to edit twice in two different blueprints
	float CrossHairXLocation = 0.5f;

	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.333333f;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;

};
