// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Actor.h"
#include "AttackSwingCapsule.generated.h"

UCLASS()
class JOURNEYMAN_API AAttackSwingCapsule : public AWeapon
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAttackSwingCapsule();


private:


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void Damage(AActor* OverlappedActor);

	UFUNCTION()
	void OnOverlapBeginSwing(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);

};


