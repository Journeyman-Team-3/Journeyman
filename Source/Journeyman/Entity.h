// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Character.h"
#include "Entity.generated.h"

UCLASS(config = Game)
class JOURNEYMAN_API AEntity : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEntity();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	// si senior
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Properties")
		int32 max_health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Properties")
		int32 max_stamina;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Properties")
		int32 max_mana;

	UPROPERTY(BlueprintReadWrite, Category="Custom Properties")
	float health;
	UPROPERTY(BlueprintReadWrite, Category="Custom Properties")
	float stamina;
	UPROPERTY(BlueprintReadWrite, Category = "Custom Properties")
	float mana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Custom Properties")
	int32 speed = 1;

	// Stores hit state / used to stop being hit multiple times per attack
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Properties")
	bool isPenetrated = false;

	// switches 'isPenetrated' back to false after being switched to true in AttackComponent::SwordLineTrace
	void ResetEntityBool() { isPenetrated = false; };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Properties")
	FTimerHandle TH_ResetEntityBool;
private:
	

protected:
	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:	
	UFUNCTION(BlueprintCallable, Category = "Custom Functions", meta = (ToolTip = "Needed to start"))
		void Constructor()
	{
		// Set health, stam and mana
		health = max_health;
		stamina = max_stamina;
		mana = max_mana;
	};
	// si seniorita
	UFUNCTION(BlueprintCallable, Category = "Custom Functions", meta = (ToolTip = "Damages entity by x, returns false if Entity health is now below 0"))
		bool TakeDamage(int32 _dmg)
	{
		bool isStillAlive = true;
		health -= _dmg;

		if (health <= 0)
		{
			isStillAlive = false;
			return isStillAlive;
		}
		else
			return isStillAlive;
	};

	UFUNCTION(BlueprintCallable, Category="Custom Functions", meta=(ToolTip = "Heals entity by x, never goes above entity max_health"))
		void Heal(int32 _heal) 
	{ 
		if (health < max_health)
		{
			if (health + _heal > max_health)
			{
				health = max_health;
			}
			else
				health += _heal;
		}
	}
	
	UFUNCTION(BlueprintCallable, Category="Custom Functions", meta=(ToolTip = "Heals entity mana by x, never goes above entity max_mana"))
    		void ManaHeal(int32 _mana) 
    	{ 
    		if (mana < max_mana)
    		{
    			if (mana + _mana > max_mana)
    			{
    				mana = max_mana;
    			}
    			else
    				mana += _mana;
    		}
    	}


};
