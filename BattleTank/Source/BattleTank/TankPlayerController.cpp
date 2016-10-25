// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"



void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	ATank* PossessedTank = GetControlledTank();
	if (PossessedTank == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Tank Possessed in Player Controller"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing %s"), *(PossessedTank->GetName()));
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return;}


	FVector HitLocation; //Out parameter
	if (GetSightRayHitLocation(HitLocation)) 
	{
		GetControlledTank()->AimAt(HitLocation);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No Hit Location Located"));
	}
	

}

//get world location of linetrace through crosshair, true if hits landscape
//may not be good because passes hitlocation down to a 3rd method, making this hard to follow
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	//Find crosshair position
	int32 ViewportSizeX, ViewPortSizeY;
	GetViewportSize(ViewportSizeX, ViewPortSizeY);
	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewPortSizeY * CrossHairYLocation);

	
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		if (GetLookVectorHitLocation(LookDirection, HitLocation))
		{
			return true;
		}
		else {
			return false;
		}
	}else {
		return false;
	}

	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation;
	//De-project screen position of crosshair to world direction
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const //returns the location hit at
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + LookDirection * LineTraceRange;
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility))
	{
		HitLocation = HitResult.Location;
		return true;
	}
	return false;
}
	