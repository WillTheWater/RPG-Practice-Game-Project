// WillTheWater All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartupData/DataAsset_StartupBase.h"
#include "DataAsset_EnemyStartup.generated.h"

class URPGEnemyGameplayAbility;
/**
 * 
 */
UCLASS()
class RPG_API UDataAsset_EnemyStartup : public UDataAsset_StartupBase
{
	GENERATED_BODY()

public:
	virtual void GiveToASC(URPGAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1) override;
		
private:
	UPROPERTY(EditDefaultsOnly, Category = "StartupData")
	TArray<TSubclassOf<URPGEnemyGameplayAbility>> EnemyCombatAbilities;
};
