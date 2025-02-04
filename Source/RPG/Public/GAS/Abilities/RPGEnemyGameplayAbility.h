// WillTheWater All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GAS/Abilities/RPGGameplayAbility.h"
#include "RPGEnemyGameplayAbility.generated.h"

class UEnemyCombatComponent;
class ARPGEnemyCharacter;

UCLASS()
class RPG_API URPGEnemyGameplayAbility : public URPGGameplayAbility
{
	GENERATED_BODY()
	public:
	UFUNCTION(BlueprintPure, Category = "Character|Ability")
	ARPGEnemyCharacter* GetEnemyCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Character|Ability")
	UEnemyCombatComponent* GetEnemyCombatComponentFromActorInfo();

	private:
	TWeakObjectPtr<ARPGEnemyCharacter> CachedEnemyCharacter;
};
