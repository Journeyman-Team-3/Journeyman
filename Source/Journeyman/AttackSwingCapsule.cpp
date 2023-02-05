// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackSwingCapsule.h"

// Sets default values
AAttackSwingCapsule::AAttackSwingCapsule()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));

	CentrePoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Centre Point"));
	CentrePoint->AttachTo(this->RootComponent);

	SwingColision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Swing Collision"));
	SwingColision->AttachTo(this->CentrePoint);

	// SwingColision->SetHiddenInGame(false);
	// SwingColision->SetVisibility(true);
	SwingColision->SetGenerateOverlapEvents(true);
	
	SwingColision->SetCollisionProfileName(TEXT("SwingAttack"));

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon Mesh"));
	WeaponMesh->AttachTo(this->CentrePoint);

	// Sets transform properties
	const FRotator SwingRotation = FRotator(90.f, 90.f, 0.f);
	const FVector SwingLocation = FVector(0.f, -90.f, 0.f);
	const FVector SwingScale = FVector(1.f, 1.f, 1.f);
	const FTransform SwingTransform = FTransform(SwingRotation, SwingLocation, SwingScale);
	
	SwingColision->SetRelativeTransform(SwingTransform);
	WeaponMesh->SetRelativeTransform(SwingTransform);
}

// Called when the game starts or when spawned
void AAttackSwingCapsule::BeginPlay()
{
	Super::BeginPlay();

	SwingColision->OnComponentBeginOverlap.AddDynamic(this, &AAttackSwingCapsule::OnOverlapBeginSwing);
}

// Called every frame
void AAttackSwingCapsule::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAttackSwingCapsule::OnOverlapBeginSwing(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	if (OtherActor != ComponentOwningPawn)
	{
		OnHitActor(OtherActor);
	}
}

