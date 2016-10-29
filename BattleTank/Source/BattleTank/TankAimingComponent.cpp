// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{

	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::BeginPlay()
{
	LastFireTime = GetWorld()->GetTimeSeconds();
	CurrentAmmo = MaxAmmo;
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	//Change reload check to here
	auto Time = GetWorld()->GetTimeSeconds();
	if (CurrentAmmo == 0) 
	{
			FiringStatus = EFiringStatus::Out_Of_Ammo;
	}
	else if((Time - LastFireTime) < ReloadTimeInSeconds)
	{
		FiringStatus = EFiringStatus::Reloading;

	}
	else if (IsBarrelMoving() )
	{
		FiringStatus = EFiringStatus::Moving;
	}
	else {
		FiringStatus = EFiringStatus::Ready;

	}

	//TODO handle aiming and locked states

}

EFiringStatus UTankAimingComponent::GetFiringState() const
{
	return FiringStatus;
}

int32 UTankAimingComponent::GetAmmoLeft()
{
	return CurrentAmmo;
}


bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	auto BarrelForward = Barrel->GetForwardVector();
	return !BarrelForward.Equals(AimDirection, 0.01);
}


void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) { return; }
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace //if do not add this will not run correctly
	);
	if(bHaveAimSolution)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal(); //turns it into unit vector
		auto TankName = GetOwner()->GetName();
		auto Time = GetWorld()->GetTimeSeconds();
		MoveBarrelTowards(AimDirection);
	}
	else {
		auto Time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("%f No aim solve found"))
	}

}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(Barrel && Turret)) { return; }

	//Find difference between current rotation and aim direction
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimRotator = AimDirection.Rotation();
	auto DeltaRotator = AimRotator - BarrelRotator; //the change still left to go

	//TODO fix yaw for the rotator when aim rotator comes out to -180 vs 180
	if (FMath::Abs(DeltaRotator.Yaw) > 180)
	{
		DeltaRotator.Yaw *= -1;
	}
	Barrel->Elevate(DeltaRotator.Pitch); 
	Turret->YawRotate(DeltaRotator.Yaw);
}

void UTankAimingComponent::Fire()
{
	if (FiringStatus == EFiringStatus::Moving || FiringStatus == EFiringStatus::Ready) {
		if (!ensure(Barrel)) { return; }
		if (!ensure(ProjectileBlueprint)) { return; }
		//Spawn projectile at socket location on the barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")), //This is very dangerous, this is hardcoded. TODO reference this socket blueprint
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		Projectile->LaunchProjectile(LaunchSpeed);
		CurrentAmmo--;
		LastFireTime = GetWorld()->GetTimeSeconds();
	}
		//TODO change the cursor color on the player UI (it's strange to have this here though..)
}

void UTankAimingComponent::ReloadAmmo()
{
	//TODO write the reload function
}

