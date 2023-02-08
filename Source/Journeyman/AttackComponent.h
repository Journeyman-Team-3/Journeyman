// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttackSwingCapsule.h"
#include "Components/ActorComponent.h"
#include "AttackComponent.generated.h"

UENUM(BlueprintType)
enum class EAttackType : uint8 {
	Swing,
	Range
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class JOURNEYMAN_API UAttackComponent : public UActorComponent
{
	GENERATED_BODY()

// VARIABLES
public:	
	// Sets default values for this component's properties
	UAttackComponent();

	// Swing
	UPROPERTY(EditAnywhere)
	TSubclassOf<AAttackSwingCapsule> SwingCollisionClass;

	// Range

private:
	// Swing
	bool bIsSwinging;
	AActor* OwningActor;
	UPROPERTY()
	AAttackSwingCapsule* SwingCollision;

	// Range

protected:
	

// FUNCTIONS
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void Attack(EAttackType AttackType);

private:
	void SwingAttack();
	void RangeAttack();
	bool IsBetween(float CurrentValue, float MaxValue, float MarginForError);

	// Swing
	float FindMaxRotation(float StartRotation);


protected:
	// Called when the game starts
	virtual void BeginPlay() override;


		
};
