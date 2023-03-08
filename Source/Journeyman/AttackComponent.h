// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttackSwingCapsule.h"
#include "RangeProjectile.h"
#include "AIController.h"
#include "Spell.h"
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

	void TriggerSword();
	void StopTriggerSword();

	UFUNCTION(BlueprintCallable)
	TArray<ASpell*> GetAllSpells();

	// Returns the first spell of that type in array.
	UFUNCTION(BlueprintCallable)
	ASpell* GetSpellOfType(ASpell* Spell, TArray<ASpell*> Spells);

	// Adds a spell to the provided array
	UFUNCTION(BlueprintCallable)
	void AddSpell(ASpell* Spell, TArray<ASpell*> Spells);

private:
	AActor* OwningActor;
	
	bool bAttackOnce = true;

	void SwordLineTrace();

	FTimerHandle SwordSwingTimerHandle;

	void SwingAttack(TSubclassOf<AWeapon> Weapon);
	void RangeAttack(TSubclassOf<AWeapon> Projectile);
	void SpellAttack(TSubclassOf<AWeapon> Spell);

	USkeletalMeshComponent* WeaponMesh;
	AWeapon* CurrentWeapon = nullptr;

	UPROPERTY(VisibleAnywhere)
	TArray<ASpell*> CurrentSpells;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY()
	UArrowComponent* ProjectileSpawnLocation;

	
};
