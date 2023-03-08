// Fill out your copyright notice in the Description page of Project Settings.


#include "RangeProjectile.h"

// Sets default values
ARangeProjectile::ARangeProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	InitialLifeSpan = 10.f;
	
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Scene Component"));

    if (!CollisionComponent)
    {
	    CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Collision Component"));
    	CollisionComponent->InitSphereRadius(CollisionRadius);
    	CollisionComponent->SetGenerateOverlapEvents(true);
    	CollisionComponent->SetCollisionProfileName(TEXT("SwingAttack"));
    	CollisionComponent->AttachTo(this->RootComponent);
    }

    if (!ProjectileMeshComponent)
    {
	    ProjectileMeshComponent = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh Component"));
    	ProjectileMeshComponent->AttachTo(this->RootComponent);
    }

    if (!ProjectileMovementComponent)
    {
	    ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
    	ProjectileMovementComponent->SetUpdatedComponent(RootComponent);
    	ProjectileMovementComponent->bRotationFollowsVelocity = true;
    	ProjectileMovementComponent->bShouldBounce = false;
    	ProjectileMovementComponent->Bounciness = 0.f;
    	ProjectileMovementComponent->ProjectileGravityScale = 0.f;
    }
}

// Called when the game starts or when spawned
void ARangeProjectile::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(10.f);

	if (!ProjectileMovementComponent)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Fault: RangeProjectile: ProjectileMovementComponent is nullptr"));
		return;
	}

	ProjectileMovementComponent->InitialSpeed = InitialSpeed;
	ProjectileMovementComponent->MaxSpeed = MaxSpeed;

	if (!CollisionComponent)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Fault: RangeProjectile: ProjectileCollision is nullptr"));
		return;
	}

	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ARangeProjectile::OnOverlapBegin);
	
}

// Called every frame
void ARangeProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARangeProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Overlap Detected"));
	
	if (OtherActor != GetOwner())
	{
		// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Overlap Detected - Not Owner"));
		if (OtherActor != this)
		{
			// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Overlap Detected - Not Self"));
			
			AEntity* HitActor = Cast<AEntity>(OtherActor);

			if (HitActor == nullptr)
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Fault: RangeProjectile: HitActor is nullptr"));
				return;
			}
			
			// DealDamage(Cast<AEntity>(OtherActor), baseDamage);
			OnHitActor(HitActor);
		}
	}
}



