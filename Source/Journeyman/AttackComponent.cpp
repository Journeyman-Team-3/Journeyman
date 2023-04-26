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
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UAttackComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

AWeapon* UAttackComponent::GetDefaultWeaponObject(TSubclassOf<AWeapon> Weapon)
{
	return Weapon.GetDefaultObject();
}