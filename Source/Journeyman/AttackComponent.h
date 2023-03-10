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

// VARIABLES
public:	
	// Sets default values for this component's properties
	UAttackComponent();

	// Swing
	UPROPERTY(EditAnywhere, Category=Components)
	TSubclassOf<AAttackSwingCapsule> SwingCollisionClass;

	// Range
	TSubclassOf<ARangeProjectile> RangeProjectileClass;

private:
	// Swing
	bool bIsSwinging;
	AActor* OwningActor;
	
	UPROPERTY()
	AAttackSwingCapsule* SwingCollision;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector SpawnOffset;

	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class ARangeProjectile> ProjectileClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Components)
	UArrowComponent* ProjectileSpawnLocation;

	UPROPERTY(EditAnywhere, Category=Gameplay)
	UAnimMontage* AttackAnimation;

// FUNCTIONS
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void Attack(TSubclassOf<AWeapon> AttackActor);

private:
	void SwingAttack(TSubclassOf<AWeapon> Weapon);
	void RangeAttack(TSubclassOf<AActor> Projectile);
	bool IsBetween(float CurrentValue, float MaxValue, float MarginForError);

	// Swing
	float FindMaxRotation(float StartRotation);


protected:
	// Called when the game starts
	virtual void BeginPlay() override;


		
};
