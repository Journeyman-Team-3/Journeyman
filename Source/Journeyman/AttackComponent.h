// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttackComponent.generated.h"

UENUM(BlueprintType)
enum class EAttackType : uint8 {
	AE_Swing       
	UMETA(DisplayName = "Swing Attack"),

	AE_Range       
	UMETA(DisplayName = "Range Attack")
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class JOURNEYMAN_API UAttackComponent : public UActorComponent
{
	GENERATED_BODY()

// VARIABLES
public:	
	// Sets default values for this component's properties
	UAttackComponent();

private:
	bool bIsSwinging;

	UPROPERTY(EditAnywhere)
	float RotationSpeed = 10.f;

	float CurrentRotation = 0.f;
	float MaxRotation = 180.f;

	AActor* OwningActor;

protected:
	

// FUNCTIONS
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Attack(EAttackType AttackType);

private:
	void SwingAttack();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


		
};
