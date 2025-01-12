// WillTheWater All Rights Reserved

#pragma once
#include "RPGStructTypes.generated.h"

class URPGLinkedAnimInstance;

USTRUCT(BlueprintType)
struct FRPGHeroWeaponData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<URPGLinkedAnimInstance> WeaponAnimLayerToLink;
};