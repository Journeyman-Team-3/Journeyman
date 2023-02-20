// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackSwingCapsule.h"

// Sets default values
AAttackSwingCapsule::AAttackSwingCapsule()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAttackSwingCapsule::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAttackSwingCapsule::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAttackSwingCapsule::OnOverlapBeginSwing(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{

}

