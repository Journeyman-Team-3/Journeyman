// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
<<<<<<< HEAD
#include "GameFramework/Character.h"
=======
>>>>>>> main
#include "GameFramework/Pawn.h"
#include "Entity.generated.h"

UCLASS()
<<<<<<< HEAD
class JOURNEYMAN_API AEntity : public ACharacter
=======
class JOURNEYMAN_API AEntity : public APawn
>>>>>>> main
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEntity();

	// si senior
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Custom Properties")
		int32 health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Custom Properties")
		int32 stamina;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Custom Properties")
		int32 speed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// si seniorita
	UFUNCTION(BlueprintCallable, Category="Custom Functions")
		void TakeDamage(int32 _dmg) { health -= _dmg; }

	UFUNCTION(BlueprintCallable, Category="Custom Functions")
		void Heal(int32 _heal) { health += _heal; }


};
