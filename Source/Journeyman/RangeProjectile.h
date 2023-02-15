// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "RangeProjectile.generated.h"

UCLASS()
class JOURNEYMAN_API ARangeProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARangeProjectile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category=Projectile)
	float CollisionRadius = 15.f;

	UPROPERTY(EditAnywhere, Category=Projectile)
	float InitialSpeed = 3000.f;

	UPROPERTY(EditAnywhere, Category=Projectile)
	float MaxSpeed = 3000.f;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
	USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, Category=Movement)
	UProjectileMovementComponent* ProjectileMovementComponent;

	void FireInDirection(const FVector& ShootDirection);
};
