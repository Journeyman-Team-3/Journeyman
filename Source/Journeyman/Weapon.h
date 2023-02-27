// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Entity.h"
#include "EAttackType.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"


UCLASS()
class JOURNEYMAN_API AWeapon : public AActor
{
	GENERATED_BODY()
	//
public:	
	// Sets default values for this actor's properties
	AWeapon();

	// Custom properties
	// Attack Type for the weapon, used to determine what to do when Attack is called.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Properties")
		EAttackType weaponType = EAttackType::Null;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Properties")
		USkeletalMesh* weaponMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Properties")
		int32 baseDamage = 1; // may want to put this on projectiles, made with scythe in mind

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Properties")
		int32 ammo = 1; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Properties")
		float timeBetweenAttacks = .3f; 

	UPROPERTY(BlueprintReadWrite, Category = "Custom Properties")
		float gameTimeAtLastAttack; // store game time when attack is called

	AActor* OwningActor = nullptr;

	// --How I am imagining the BP_Scythe implementation--
	// attacking event trigger-> if (ammo > 0): Attack(), ammo -= 1;
	// tick event-> if (ammo <= 0): if (current game time >= (gameTimeAtLastAttack + timeBetweenAttacks)): ammo = 1;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// custom functions
	UFUNCTION(BlueprintCallable, Category="Custom Functions")
		void DealDamage(AEntity* _enty, int32 _dmg) { _enty->TakeDamage(_dmg); }
	
};
