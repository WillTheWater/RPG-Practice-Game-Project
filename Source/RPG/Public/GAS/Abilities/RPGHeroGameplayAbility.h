// WillTheWater All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GAS/Abilities/RPGGameplayAbility.h"
#include "RPGHeroGameplayAbility.generated.h"

class ARPGHeroCharacter;
class ARPGHeroController;
class UHeroCombatComponent;

UCLASS()
class RPG_API URPGHeroGameplayAbility : public URPGGameplayAbility
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "Character|Ability")
	ARPGHeroCharacter* GetHeroCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Character|Ability")
	ARPGHeroController* GetHeroControllerFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Character|Ability")
	UHeroCombatComponent* GetHeroCombatComponentFromActorInfo();

private:
	TWeakObjectPtr<ARPGHeroCharacter> CachedHeroCharacter;
	TWeakObjectPtr<ARPGHeroController> CachedHeroController;
};
