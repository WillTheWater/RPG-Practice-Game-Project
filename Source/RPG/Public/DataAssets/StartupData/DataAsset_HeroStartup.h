// WillTheWater All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartupData/DataAsset_StartupBase.h"
#include "GameplayTagContainer.h"
#include "DataAsset_HeroStartup.generated.h"

USTRUCT(BlueprintType)
struct FRPGAbilitySet
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"))
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<URPGGameplayAbility> AbilityToGrant;

	bool IsValid() const;
};

UCLASS()
class RPG_API UDataAsset_HeroStartup : public UDataAsset_StartupBase
{
	GENERATED_BODY()

public:
	virtual void GiveToASC(URPGAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1) override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "StartupData", meta = (TitleProperty = "InputTag"))
	TArray<FRPGAbilitySet> HeroStartAbilitySet;
};
