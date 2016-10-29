// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void LaunchProjectile(float speed);

private:
	UProjectileMovementComponent* ProjectileMovement = nullptr;
	
	void DestroyThis();

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float Damage = 25.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float DestroyDelay = 5.0f;

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* CollisionMesh = nullptr; //TSubclass is built in as a pointer

	UPROPERTY(EditAnywhere, Category = "Components")
	UParticleSystemComponent* LaunchBlast = nullptr; //TSubclass is built in as a pointer

	UPROPERTY(EditAnywhere, Category = "Components")
	UParticleSystemComponent* ImpactBlast = nullptr; //TSubclass is built in as a pointer

	UPROPERTY(EditAnywhere, Category = "Components")
	URadialForceComponent* ExplosionForce = nullptr;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
};
