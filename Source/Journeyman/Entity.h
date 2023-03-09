// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Entity.generated.h"

UCLASS()
class JOURNEYMAN_API AEntity : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEntity();

	// si senior
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Custom Properties")
		int32 health = 10;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Custom Properties")
		int32 stamina = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Custom Properties")
		int32 speed = 1;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// si seniorita
	UFUNCTION(BlueprintCallable, Category = "Custom Functions")
		void TakeDamage(int32 _dmg);

	UFUNCTION(BlueprintCallable, Category="Custom Functions")
		void Heal(int32 _heal) { health += _heal; }


};
