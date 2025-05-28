// WillTheWater All Rights Reserved

#pragma once
#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "RPGTypes/RPGEnumTypes.h"
#include "RPGGameplayAbility.generated.h"

class UPawnCombatComponent;
class URPGAbilitySystemComponent;

UENUM(BlueprintType)
enum class ERPGAbilityActivationPolicy : uint8
{
	ON_TRIGGERED,
	ON_GIVEN
};

UCLASS()
class RPG_API URPGGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
protected:
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;


	UPROPERTY(EditDefaultsOnly, Category = "Character|Ability")
	ERPGAbilityActivationPolicy AbilityActivationPolicy = ERPGAbilityActivationPolicy::ON_TRIGGERED;

	UFUNCTION(BlueprintPure, Category = "Character|Ability")
	UPawnCombatComponent* GetPawnCombatComponentFromActorInfo() const;
	
	UFUNCTION(BlueprintPure, Category = "Character|Ability")
	URPGAbilitySystemComponent* GetRPGASCFromActorInfo() const;
	
	FActiveGameplayEffectHandle NativeApplyEffectSpecHandleToTarget(AActor* Target, const FGameplayEffectSpecHandle& InSpecHandle);

	UFUNCTION(BlueprintCallable, Category = "Character|Ability", meta = (DisplayName = "Apply Gameplay Effect Spec Handle To Target", ExpandEnumAsExecs = "OutSuccessType"))
	FActiveGameplayEffectHandle ApplyEffectSpecHandleToTarget(AActor* Target, const FGameplayEffectSpecHandle& InSpecHandle, ERPGSuccessType& OutSuccessType);
};
