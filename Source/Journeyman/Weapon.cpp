// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

bool AWeapon::CanEditChange(const FProperty* InProperty) const
{
	const bool ParentValue = Super::CanEditChange(InProperty);

	const FName PropertyName = InProperty->GetFName();

	if (PropertyName == GET_MEMBER_NAME_CHECKED(AWeapon, weaponMesh))
	{
		return ParentValue && weaponType != EAttackType::Null;
	}
	
	if (PropertyName == GET_MEMBER_NAME_CHECKED(AWeapon, SpawnOffset))
	{
		return ParentValue && weaponType == EAttackType::Range;
	}

	if (PropertyName == GET_MEMBER_NAME_CHECKED(AWeapon, NoAnimRequired))
	{
		return ParentValue && weaponType == EAttackType::Range;
	}

	if (PropertyName == GET_MEMBER_NAME_CHECKED(AWeapon, AttackAnimation))
	{
		return ParentValue && (weaponType == EAttackType::Range && NoAnimRequired == false) || (weaponType == EAttackType::Melee);
	}

	return ParentValue;
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

