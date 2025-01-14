// WillTheWater All Rights Reserved

#pragma once
#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "RPGAbilitySystemComponent.generated.h"

struct FRPGAbilitySet;

UCLASS()
class RPG_API URPGAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void OnAbilityInputPressed(const FGameplayTag& InInput);
	void OnAbilityInputReleased(const FGameplayTag& InInput);

	UFUNCTION(BlueprintCallable, Category = "Character|Ability", meta = (ApplyLevel = "1"))
	void GrantHeroWeaponAbilities(const TArray<FRPGAbilitySet>& InDefaultWeaponAbilities, int32 ApplyLevel, TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandle);
	
	UFUNCTION(BlueprintCallable, Category = "Character|Ability")
	void RemoveGrantHeroWeaponAbilities(UPARAM(ref) TArray<FGameplayAbilitySpecHandle>& RemoveAbilitySpecHandle);
};