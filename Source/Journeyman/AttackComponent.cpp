// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackComponent.h"
#include "Components/StaticMeshComponent.h"
#include <Components/CapsuleComponent.h>

#include "AttackSwingCapsule.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UAttackComponent::UAttackComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	// Makes sure we have a reference to the actor the the component is attached too
	OwningActor = GetOwner();
	
}


// Called every frame
void UAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsSwinging)
	{
		if (SwingCollision->CurrentRotation != SwingCollision->MaxRotation)
		{
			float NewYaw = SwingCollision->GetActorRotation().Yaw + (DeltaTime * SwingCollision->RotationSpeed);
			
			SwingCollision->SetActorRotation(FRotator(
				SwingCollision->GetActorRotation().Pitch,
				NewYaw,
				SwingCollision->GetActorRotation().Roll));

			SwingCollision->CurrentRotation = NewYaw;
		}
		else
		{
			AActor* ComponentToDelete = UGameplayStatics::GetActorOfClass(GetWorld(), AAttackSwingCapsule::StaticClass());

			ComponentToDelete->Destroy();

			SwingCollision->CurrentRotation = 0.f;
		} 
	}
}

void UAttackComponent::Attack(EAttackType AttackType) 
{
	switch (AttackType)
	{
	case EAttackType::Swing:
		SwingAttack();
		break;
	case EAttackType::Range:
		break;
	default:
		break;
	}
}

void UAttackComponent::SwingAttack()
{
	// Checks if it is not null, if it is then return
	if (OwningActor == nullptr)
	{
		return;
	}
	
	// Add SwingCollision to the centre point on the owner
	// TODO: Spawn Actor
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	const FVector SpawnLocation = OwningActor->GetActorLocation();
	const FRotator SpawnRotation = OwningActor->GetActorRotation();
	SwingCollision = Cast<AAttackSwingCapsule>(GetWorld()->SpawnActor(SwingCollisionClass, &SpawnLocation, &SpawnRotation, SpawnInfo));

	SwingCollision->AttachToActor(OwningActor, FAttachmentTransformRules::KeepWorldTransform);

	SwingCollision->StartRotation = SwingCollision->GetActorRotation().Yaw;
	SwingCollision->CurrentRotation = SwingCollision->StartRotation;
	SwingCollision->MaxRotation = SwingCollision->CurrentRotation + 180.f;
	
	// SwingCollision->Tags.AddUnique("AttackSystemTemp");

	bIsSwinging = true;
}

