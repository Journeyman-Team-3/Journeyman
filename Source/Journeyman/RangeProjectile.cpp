// Fill out your copyright notice in the Description page of Project Settings.


#include "RangeProjectile.h"

// Sets default values
ARangeProjectile::ARangeProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    if (!RootComponent)
    {
	    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Scene Component"));
    }

    if (!CollisionComponent)
    {
	    CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Collision Component"));
    	CollisionComponent->InitSphereRadius(CollisionRadius);

    	RootComponent = CollisionComponent;
    }

    if (!ProjectileMovementComponent)
    {
	    ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
    	ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
    	ProjectileMovementComponent->bRotationFollowsVelocity = true;
    	ProjectileMovementComponent->bShouldBounce = true;
    	ProjectileMovementComponent->Bounciness = 0.3f;
    	ProjectileMovementComponent->ProjectileGravityScale = 0.f;
    }
}

// Called when the game starts or when spawned
void ARangeProjectile::BeginPlay()
{
	Super::BeginPlay();

	if (!ProjectileMovementComponent)
	{
		ProjectileMovementComponent->InitialSpeed = InitialSpeed;
		ProjectileMovementComponent->MaxSpeed = MaxSpeed;
	}
	
}

// Called every frame
void ARangeProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARangeProjectile::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

