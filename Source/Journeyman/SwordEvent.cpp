// Fill out your copyright notice in the Description page of Project Settings.


#include "SwordEvent.h"

#include "AttackComponent.h"
#include "Weapon.h"

void USwordEvent::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	// Cast<UAttackComponent>(Cast<AWeapon>(MeshComp->GetOwner())->OwningActor->GetComponentByClass(UAttackComponent::StaticClass()))->TriggerSword();

	UAttackComponent* Temp = Cast<UAttackComponent>(MeshComp->GetOwner()->GetComponentByClass(UAttackComponent::StaticClass()));

	if (Temp != nullptr)
	{
		// Temp->TriggerSword();
	}
}

void USwordEvent::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	// Cast<UAttackComponent>(Cast<AWeapon>(MeshComp->GetOwner())->OwningActor->GetComponentByClass(UAttackComponent::StaticClass()))->StopTriggerSword();

	UAttackComponent* Temp = Cast<UAttackComponent>(MeshComp->GetOwner()->GetComponentByClass(UAttackComponent::StaticClass()));

	if (Temp != nullptr)
	{
		// Temp->StopTriggerSword();
	}
}