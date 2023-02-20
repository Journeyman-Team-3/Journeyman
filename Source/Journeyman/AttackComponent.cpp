// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackComponent.h"

#include "AttackSwingCapsule.h"
#include "RangeProjectile.h"
#include "GameFramework/Character.h"
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
}

void UAttackComponent::Attack(TSubclassOf<AWeapon> AttackActor) 
{
	if (AttackActor == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Fault: Attack Component: AttackActor is nullptr"));
		return;
	}
	
	switch (AttackActor.GetDefaultObject()->weaponType)
	{
	case EAttackType::Melee:
		if (Cast<AAttackSwingCapsule>(AttackActor->GetDefaultObject()) != nullptr)
		{
			SwingAttack(AttackActor);
			break;
		}
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Fault: Attack Component: AttackActor Does Not Match An Attack Type - Melee"));
		break;
	case EAttackType::Range:
		if (Cast<ARangeProjectile>(AttackActor.GetDefaultObject()) != nullptr)
		{
			RangeAttack(AttackActor);
			break;
		}
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Fault: Attack Component: AttackActor Does Not Match An Attack Type - Range"));
		break;
	case EAttackType::Null:
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Fault: Attack Component weaponType on Actor of Class Type AWeapon: has not been set"));
		break;
	}
}

void UAttackComponent::SwingAttack(TSubclassOf<AWeapon> Weapon)
{
	// Using animation montages
	// Attach weapon to character
	// Play the montage
	// While playing draw line trace between two points
	// These two points will be set on the skelatal mesh for the weapon
	// Stop drawing line traces when montage has finished
	// Done using notifies

	USkeletalMeshComponent* OwningActorMeshComp = Cast<USkeletalMeshComponent>(OwningActor->FindComponentByClass(USkeletalMeshComponent::StaticClass()));

	USkeletalMeshComponent* WeaponMesh = NewObject<USkeletalMeshComponent>(OwningActor, USkeletalMeshComponent::StaticClass(), TEXT("Weapon Mesh"));

	if (WeaponMesh)
	{
		WeaponMesh->SetupAttachment(OwningActorMeshComp, TEXT("sword"));
		WeaponMesh->RegisterComponent();
		WeaponMesh->SkeletalMesh = Weapon.GetDefaultObject()->weaponMesh;
		
		OwningActor->AddInstanceComponent(WeaponMesh);
	}
	
	bool bAttackOnce = true;

	if (bAttackOnce)
	{
		bAttackOnce = false;

		UAnimInstance* AnimInstance = OwningActorMeshComp->GetAnimInstance();

		if (AnimInstance != nullptr)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("AnimInstance"));
			float animTime = AnimInstance->Montage_Play(AttackAnimation);

			FTimerHandle DelayTimerHandle;
			GetWorld()->GetTimerManager().SetTimer(DelayTimerHandle, [&]()
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("ResetDoOnce"));
				// Resets so that the player can attack again
				bAttackOnce = true;
			}, animTime, false);
		}
	}






	/*
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
	*/
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

