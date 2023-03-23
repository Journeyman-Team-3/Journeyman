// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Entity.h"
#include "GameFramework/Actor.h"
#include "Potion.generated.h"

UENUM(BlueprintType)
enum class EPotionType : uint8 {
	Null,
	Mana,
	Health
};

UENUM(BlueprintType)
enum class EPotionStyle : uint8 {
	Null,
	SingleUse,
	Timed
};

UENUM(BlueprintType)
enum class EAdditiveType : uint8 {
	Null,
	Positive,
	Negative
};

UCLASS()
class JOURNEYMAN_API APotion : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APotion();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Potion Type - Mana, Health, Stamina Etc... 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Properties")
	EPotionType PotionType = EPotionType::Null;

	/*
		Timed Potion adds/removes a set amount per second
		Single Use Potions do a on time add or remove
	*/
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Custom Properties")
	EPotionStyle PotionStyle = EPotionStyle::Null;

	/*
		Positive - Adds value
		Negative - Removed value
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Properties")
	EAdditiveType AdditiveType = EAdditiveType::Null;

	// Value to add/remove from statistic
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Properties", meta = (EditCondition = "PotionStyle == EPotionStyle::SingleUse"))
		float PotionValue = 5.f;

	// Duration of the potion in seconds
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Properties", meta = (EditCondition = "PotionStyle == EPotionStyle::Timed"))
		float UseLength = 3.f;

	// Value to add/remove from statistic in seconds
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Properties", meta = (EditCondition = "PotionStyle == EPotionStyle::Timed"))
		float PotionValueRate = 0.3f;

	// Components Needed:
	// Capsule (for pickup)
	// Static Mesh for visuals

	UFUNCTION(BlueprintCallable)
	void DrinkPotion(APotion* PotionToDrink);

	void TimedPotion(APotion* TimedPotion);
	void SingleUsePotion(APotion* SingleUsePotion);

	/*
		@param Entity - Entity which needs stats modifying
	*/
	void UpdateStats(AEntity* Entity, APotion* Potion, float Value);
};
