// WillTheWater All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAsset_StartupBase.generated.h"

class URPGGameplayAbility;
class URPGAbilitySystemComponent;
class UGameplayEffect;

UCLASS()
class RPG_API UDataAsset_StartupBase : public UDataAsset
{
	GENERATED_BODY()

public:
	virtual void GiveToASC(URPGAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "StartupData")
	TArray<TSubclassOf<URPGGameplayAbility>> ActivateOnGivenAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "StartupData")
	TArray<TSubclassOf<URPGGameplayAbility>> ReactiveAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "StartupData")
	TArray<TSubclassOf<UGameplayEffect>> StartupGameplayEffects;

	void GrantAbilities(const TArray<TSubclassOf<URPGGameplayAbility>>& InAbilitiesToGive, URPGAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);
};
