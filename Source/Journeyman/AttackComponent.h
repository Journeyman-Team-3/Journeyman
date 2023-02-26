// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttackSwingCapsule.h"
#include "RangeProjectile.h"
#include "Components/ActorComponent.h"
#include "Components/ArrowComponent.h"
#include "AttackComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class JOURNEYMAN_API UAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAttackComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void Attack(TSubclassOf<AWeapon> AttackActor);

private:
	AActor* OwningActor;
	
	bool bAttackOnce = true;

	void TriggerSword();

	void SwordLineTrace();

	void SwingAttack(TSubclassOf<AWeapon> Weapon);
	void RangeAttack(TSubclassOf<AWeapon> Projectile);
	bool IsBetween(float CurrentValue, float MaxValue, float MarginForError);

	USkeletalMeshComponent* WeaponMesh;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector SpawnOffset;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Components)
	UArrowComponent* ProjectileSpawnLocation;

	UPROPERTY(EditAnywhere, Category=Gameplay)
	UAnimMontage* AttackAnimation;
};
