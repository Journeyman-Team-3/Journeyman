// Fill out your copyright notice in the Description page of Project Settings.


#include "Potion.h"

// Sets default values
APotion::APotion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APotion::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APotion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APotion::DrinkPotion(APotion* PotionToDrink)
{
	switch (PotionToDrink->PotionStyle)
	{
	case EPotionStyle::Null:

		break;
	case EPotionStyle::SingleUse:
		SingleUsePotion(PotionToDrink);
		break;
	case EPotionStyle::Timed:
		TimedPotion(PotionToDrink);
		break;
	default:
		break;
	}
}

void APotion::TimedPotion(APotion* TimedPotion)
{
}

void APotion::SingleUsePotion(APotion* SingleUsePotion)
{
	
}

void APotion::UpdateStats(AEntity* Entity, APotion* Potion, float Value)
{
	switch (Potion->PotionType)
	{
	/*
	 * Health
	*/
	case EPotionType::Health:
		if (Potion->AdditiveType == EAdditiveType::Positive)
		{
			Entity->Heal(Value);
		}
		else if (Potion->AdditiveType == EAdditiveType::Negative)
		{
			Entity->TakeDamage(Value);
		}
		break;
	/*
	 * Manna
	*/

	/*
	 * Stamina
	*/
	}
}

