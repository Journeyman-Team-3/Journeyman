// Fill out your copyright notice in the Description page of Project Settings.


#include "RangeProjectile.h"

// Sets default values
ARangeProjectile::ARangeProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	ProjectileMesh->AttachTo(this->RootComponent);

	ProjectileCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Projectile Collision"));
	ProjectileCollision->AttachTo(this->ProjectileMesh);
}

// Called when the game starts or when spawned
void ARangeProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARangeProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

