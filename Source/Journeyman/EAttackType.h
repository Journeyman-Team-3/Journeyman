// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EAttackType.generated.h"

UENUM(BlueprintType)
enum class EAttackType : uint8 {
	Null,
	Melee,
	Range,
	Spell
};
