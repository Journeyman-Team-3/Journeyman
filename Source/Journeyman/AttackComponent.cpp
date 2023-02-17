// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackComponent.h"
#include "Components/StaticMeshComponent.h"
#include <Components/CapsuleComponent.h>

#include "Engine/StaticMesh.h"
#include "AttackSwingCapsule.h"
#include "RangeProjectile.h"
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

	ProjectileSpawnLocation = NewObject<UArrowComponent>(OwningActor, UArrowComponent::StaticClass(), TEXT("Projectile Spawn Location"));

	if (ProjectileSpawnLocation)
	{
		ProjectileSpawnLocation->RegisterComponent();

		ProjectileSpawnLocation->AttachToComponent(OwningActor->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);

		ProjectileSpawnLocation->CreationMethod = EComponentCreationMethod::Instance;

		ProjectileSpawnLocation->SetHiddenInGame(false);
		ProjectileSpawnLocation->SetVisibility(true);
	}
	
}


// Called every frame
void UAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsSwinging)
	{
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
			bIsSwinging = false;
			
			SwingCollision->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
			SwingCollision->Destroy();
		} 
	}
}

void UAttackComponent::Attack(EAttackType AttackType, TSubclassOf<AActor> AttackActor) 
{
	// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("AttackActor Class: %s"), *AttackActor));
	switch (AttackType)
	{
	case EAttackType::Swing:
		if (Cast<AAttackSwingCapsule>(AttackActor->GetDefaultObject()) != nullptr)
		{
			SwingAttack();
			break;
		}
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Fault: Attack Component: AttackActor Does Not Match An Attack Type"));
		break;
	case EAttackType::Range:
		if (Cast<ARangeProjectile>(AttackActor.GetDefaultObject()) != nullptr)
		{
			RangeAttack(AttackActor);
			break;
		}
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Fault: Attack Component: AttackActor Does Not Match An Attack Type"));
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
		// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Destroyed Swing Due To Swing Existing")));
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

	SwingCollision->ComponentOwningPawn = OwningActor;
	
	SwingCollision->AttachToActor(OwningActor, FAttachmentTransformRules::KeepWorldTransform);

	SwingCollision->StartRotation = SwingCollision->GetActorRotation().Yaw;
	SwingCollision->CurrentRotation = SwingCollision->StartRotation;
	SwingCollision->MaxRotation = FindMaxRotation(SwingCollision->StartRotation);

	bIsSwinging = true;
}

void UAttackComponent::RangeAttack(TSubclassOf<AActor> Projectile)
{
	if (Projectile == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Fault: Attack Component: Projectile = nullptr"));
		return;
	}

	ProjectileSpawnLocation->SetRelativeLocation(SpawnOffset);
	
	FVector SpawnLocation = ProjectileSpawnLocation->GetComponentTransform().GetLocation();

	FRotator SpawnRotation = OwningActor->GetActorForwardVector().Rotation();

	UWorld* World = GetWorld();

	if (World == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Fault: Attack Component: World = nullptr"));
		return;
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = OwningActor;
	SpawnParams.Instigator = OwningActor->GetInstigator();

	ARangeProjectile* ProjectileInstance = World->SpawnActor<ARangeProjectile>(Projectile, SpawnLocation, SpawnRotation, SpawnParams);
	
	ProjectileInstance->ComponentOwningPawn = OwningActor;
}

float UAttackComponent::FindMaxRotation(float StartRotation)
{
	if (StartRotation >= 0 && StartRotation <= 180.f)
	{
		float TempNum = StartRotation + 180.f;
		if (TempNum > 180.f)
		{
			return StartRotation - 180;
		}
		else
		{
			return StartRotation - 180;
		}
	}
	else
	{
		float TempNum = StartRotation + 180;
		if (TempNum < 0)
		{
			return StartRotation + 180;
		}
		else
		{
			return StartRotation + 180;
		}
	}
	
	
}

bool UAttackComponent::IsBetween(float CurrentValue, float MaxValue, float MarginForError)
{
	if (CurrentValue >= MaxValue - MarginForError && CurrentValue <= MaxValue + MarginForError)
	{
		return true;
	}
	
	return false;
}
