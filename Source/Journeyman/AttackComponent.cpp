// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackComponent.h"

#include "AttackSwingCapsule.h"
#include "DrawDebugHelpers.h"
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

	CurrentWeapon = AttackActor.GetDefaultObject();
	
	switch (AttackActor.GetDefaultObject()->weaponType)
	{
	case EAttackType::Melee:
		SwingAttack(AttackActor);
		break;
	case EAttackType::Range:
		RangeAttack(AttackActor);
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

	WeaponMesh = NewObject<USkeletalMeshComponent>(OwningActor, USkeletalMeshComponent::StaticClass(), TEXT("Weapon Mesh"));

	if (WeaponMesh)
	{
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
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("AnimInstance"));
			float animTime = AnimInstance->Montage_Play(Weapon.GetDefaultObject()->AttackAnimation);

			FTimerHandle DelayTimerHandle;
			GetWorld()->GetTimerManager().SetTimer(DelayTimerHandle, [&]()
			{
				//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("ResetDoOnce"));

				// Resets so that the player can attack again
				
				// TODO: Remove Mesh from hand?

				WeaponMesh->SkeletalMesh = nullptr;
				bAttackOnce = true;
			}, animTime, false);
		}
	}
}

void UAttackComponent::TriggerSword()
{
	/*
	 
	ACharacter* OwningCharacter = Cast<ACharacter>(OwningActor);
	AController* ActorController = OwningCharacter->GetController();

	AAIController* AIOwningController = Cast<AAIController>(ActorController);

	if (ActorController->IsLocalPlayerController())
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Player Controller"));
		// OwningCharacter->DisableInput(Cast<APlayerController>(ActorController));
	}
	else if (AIOwningController != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("AI Controller"));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Fault: TriggerSword: ActorController is neither AI or Player - No Controller Found"));
	}
	*/
	
	GetWorld()->GetTimerManager().SetTimer(SwordSwingTimerHandle, this, &UAttackComponent::SwordLineTrace, 0.0001, true);
}

void UAttackComponent::SwordLineTrace()
{
	FVector StartLocation = WeaponMesh->GetSocketLocation(TEXT("start"));
	FVector EndLocation = WeaponMesh->GetSocketLocation(TEXT("end"));

	//DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Magenta, false, 3.f, 0, 15);
	
	FHitResult HitResult;
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Camera))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Hit Something"));

		AActor* HitActor = HitResult.GetActor();

		if (HitActor != GetOwner())
		{
			AEntity* EntityHit = Cast<AEntity>(HitActor);

			if (EntityHit == nullptr)
			{
				//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Fault: MeleeAttack: HitActorDamage is nullptr"));
				return;
			}
			else
			{
				//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Entity Hit"));
				if (!EntityHit->isPenetrated)
				{
					CurrentWeapon->OnHitActor(EntityHit);
					EntityHit->isPenetrated = true;
				}
					
			}	
		}
	}
}

void UAttackComponent::StopTriggerSword()
{
	GetWorld()->GetTimerManager().ClearTimer(SwordSwingTimerHandle);

	ACharacter* OwningCharacter = Cast<ACharacter>(OwningActor);
	AController* ActorController = OwningCharacter->GetController();

	AAIController* AIOwningController = Cast<AAIController>(ActorController);

	if (ActorController->IsLocalPlayerController())
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Player Controller"));
		OwningCharacter->EnableInput(Cast<APlayerController>(ActorController));
	}
	else if (AIOwningController != nullptr)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("AI Controller"));
	}
	else
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Fault: TriggerSword: ActorController is neither AI or Player - No Controller Found"));
	}
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
