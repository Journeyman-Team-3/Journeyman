// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackComponent.h"
#include "Components/StaticMeshComponent.h"
#include <Components/CapsuleComponent.h>

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
	
}


// Called every frame
void UAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}

void UAttackComponent::Attack(EAttackType AttackType) 
{
	switch (AttackType)
	{
	case EAttackType::AE_Swing:
		break;
	case EAttackType::AE_Range:
		break;
	default:
		break;
	}
}

void UAttackComponent::SwingAttack()
{
	// Checks if it is not null, if it is then return
	if (OwningActor == nullptr)
	{
		return;
	}

	// Add CentrePoint To Owner
	UActorComponent* CentrePoint = OwningActor->AddComponentByClass(UCapsuleComponent, false);
}

