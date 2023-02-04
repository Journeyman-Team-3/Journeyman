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
		// if (SwingCollision->CurrentRotation != SwingCollision->MaxRotation)
		if (!IsBetween(SwingCollision->CurrentRotation, SwingCollision->MaxRotation, 5.f))
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
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Destroyed Swing Due To Swing End")));
			bIsSwinging = false;
			
			SwingCollision->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
			SwingCollision->Destroy();
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

	if (SwingCollision != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Destroyed Swing Due To Swing Existing")));
		SwingCollision->Destroy();
	}
	
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	const FVector SpawnLocation = OwningActor->GetActorLocation();
	const FRotator SpawnRotation = OwningActor->GetActorRotation();
	SwingCollision = Cast<AAttackSwingCapsule>(GetWorld()->SpawnActor(SwingCollisionClass, &SpawnLocation, &SpawnRotation, SpawnInfo));

	if (SwingCollision == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Fault: Attack Component: SwingCollision = nullptr - has it been set on the owning actor?"));
		return;
	}
	
	SwingCollision->AttachToActor(OwningActor, FAttachmentTransformRules::KeepWorldTransform);

	SwingCollision->StartRotation = SwingCollision->GetActorRotation().Yaw;
	SwingCollision->CurrentRotation = SwingCollision->StartRotation;
	SwingCollision->MaxRotation = FindMaxRotation(SwingCollision->StartRotation);
	
	// SwingCollision->Tags.AddUnique("AttackSystemTemp");

	bIsSwinging = true;
}

float UAttackComponent::FindMaxRotation(float StartRotation)
{
	if (StartRotation >= 0 && StartRotation <= 180.f)
	{
		float TempNum = StartRotation + 180.f;
		if (TempNum > 180.f)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("StartNum: %f - MaxRotation: %f"), StartRotation, StartRotation - 180));
			return StartRotation - 180;
		}
		// TODO: Might Not Be Needed
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("ELSE: StartNum: %f - MaxRotation: %f"), StartRotation, StartRotation - 180));
		return 0;
	}
	
	float TempNum = StartRotation + 180;
	if (TempNum < 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("StartNum: %f - MaxRotation: %f"), StartRotation, StartRotation + 180));
		return StartRotation + 180;
	}
	// TODO: Might Not Be Needed
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("ELSE: StartNum: %f - MaxRotation: %f"), StartRotation, StartRotation + 180));
	return 0;
}

bool UAttackComponent::IsBetween(float CurrentRotation, float MaxRotation, float MarginForError)
{
	if (CurrentRotation >= MaxRotation - MarginForError && CurrentRotation <= MaxRotation + MarginForError)
	{
		return true;
	}

	return false;
}

