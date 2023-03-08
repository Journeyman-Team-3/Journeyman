// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackComponent.h"

#include "AttackSwingCapsule.h"
<<<<<<< HEAD
#include "DrawDebugHelpers.h"
=======
>>>>>>> main
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
<<<<<<< HEAD
=======

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
>>>>>>> main

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
<<<<<<< HEAD

	// AttackActor.GetDefaultObject()->OwningActor = OwningActor;
=======
>>>>>>> main
	
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

<<<<<<< HEAD
	WeaponMesh = NewObject<USkeletalMeshComponent>(OwningActor, USkeletalMeshComponent::StaticClass(), TEXT("Weapon Mesh"));

	if (WeaponMesh)
=======
	USkeletalMeshComponent* WeaponMesh = NewObject<USkeletalMeshComponent>(OwningActor, USkeletalMeshComponent::StaticClass(), TEXT("Weapon Mesh"));

	if (WeaponMesh)
	{
		// WeaponMesh->SetVisibility(true);
		WeaponMesh->SetupAttachment(OwningActorMeshComp, TEXT("sword"));
		WeaponMesh->SkeletalMesh = Weapon.GetDefaultObject()->weaponMesh;
		WeaponMesh->RegisterComponent();
		
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
				// WeaponMesh->SetVisibility(false);
				bAttackOnce = true;
			}, animTime, false);
		}
	}
	/*
	// TODO: Get Socket Locations
	FVector StartLocation;
	FVector EndLocation;

	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_WorldDynamic);

	*/





	/*
	// Checks if it is not null, if it is then return
	if (OwningActor == nullptr)
>>>>>>> main
	{
		// WeaponMesh->SetVisibility(true);
		WeaponMesh->SetupAttachment(OwningActorMeshComp, TEXT("sword"));
		WeaponMesh->SkeletalMesh = Weapon.GetDefaultObject()->weaponMesh;
		WeaponMesh->RegisterComponent();
		
		OwningActor->AddInstanceComponent(WeaponMesh);
	}

	if (bAttackOnce)
	{
		bAttackOnce = false;

		UAnimInstance* AnimInstance = OwningActorMeshComp->GetAnimInstance();

		if (AnimInstance != nullptr)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("AnimInstance"));
			float animTime = AnimInstance->Montage_Play(Weapon.GetDefaultObject()->AttackAnimation);

			FTimerHandle DelayTimerHandle;
			GetWorld()->GetTimerManager().SetTimer(DelayTimerHandle, [&]()
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("ResetDoOnce"));
				// Resets so that the player can attack again
				// WeaponMesh->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
				WeaponMesh->SkeletalMesh = nullptr;
				bAttackOnce = true;
			}, animTime, false);
		}
	}
}

void UAttackComponent::TriggerSword()
{
	GetWorld()->GetTimerManager().SetTimer(SwordSwingTimerHandle, this, &UAttackComponent::SwordLineTrace, 0.001, true);
}

void UAttackComponent::SwordLineTrace()
{
	FVector StartLocation = WeaponMesh->GetSocketLocation(TEXT("start"));
	FVector EndLocation = WeaponMesh->GetSocketLocation(TEXT("end"));

	DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Magenta, false, 3.f, 0, 15);
	
	FHitResult HitResult;
	bool Hit = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Camera);

	if (Hit)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Hit Something"));
	}
	
	AActor* HitActor = nullptr;
	HitActor = HitResult.GetActor();
	
	if (HitActor != GetOwner())
	{
		// TODO: Check that its not nullptr
		AEntity* HitActorDamage = Cast<AEntity>(HitActor);

		if (HitActorDamage == nullptr)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Fault: MeleeAttack: HitActorDamage is nullptr"));
			return;
		}
		
		// Cast<AWeapon>(WeaponMesh->GetOwner())->DealDamage(Cast<AEntity>(HitActor), Cast<AWeapon>(WeaponMesh->GetOwner())->baseDamage);
		HitActorDamage->Destroy();
		// OnHitActor(OtherActor);
	}
}

void UAttackComponent::StopTriggerSword()
{
	GetWorld()->GetTimerManager().ClearTimer(SwordSwingTimerHandle);
}

void UAttackComponent::RangeAttack(TSubclassOf<AWeapon> Projectile)
{
	if (Projectile == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Fault: Attack Component: Projectile = nullptr"));
		return;
	}

	ProjectileSpawnLocation->SetRelativeLocation(Projectile.GetDefaultObject()->SpawnOffset);
	
	FVector SpawnLocation = ProjectileSpawnLocation->GetComponentTransform().GetLocation();

<<<<<<< HEAD
=======
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

>>>>>>> main
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

bool UAttackComponent::IsBetween(float CurrentValue, float MaxValue, float MarginForError)
{
	if (CurrentValue >= MaxValue - MarginForError && CurrentValue <= MaxValue + MarginForError)
	{
<<<<<<< HEAD
=======
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
>>>>>>> main
		return true;
	}
	
	return false;
}

