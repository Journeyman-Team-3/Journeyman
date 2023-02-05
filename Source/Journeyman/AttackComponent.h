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

	UPROPERTY(EditAnywhere)
	TSubclassOf<AAttackSwingCapsule> SwingCollisionClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AAttackSwingCapsule* SwingCollision;

private:
	bool bIsSwinging;

	AActor* OwningActor;

	

protected:
	

// FUNCTIONS
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void Attack(EAttackType AttackType);

private:
	void SwingAttack();

	float FindMaxRotation(float StartRotation);

	bool IsBetween(float CurrentRotation, float MaxRotation, float MarginForError);


protected:
	// Called when the game starts
	virtual void BeginPlay() override;


		
};
