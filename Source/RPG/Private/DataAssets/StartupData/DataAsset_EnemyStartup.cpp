// WillTheWater All Rights Reserved


#include "DataAssets/StartupData/DataAsset_EnemyStartup.h"

#include "GAS/RPGAbilitySystemComponent.h"
#include "GAS/Abilities/RPGEnemyGameplayAbility.h"

void UDataAsset_EnemyStartup::GiveToASC(URPGAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	Super::GiveToASC(InASCToGive, ApplyLevel);
	if (!EnemyCombatAbilities.IsEmpty())
	{
		for (const TSubclassOf<URPGEnemyGameplayAbility>& AbilityClass : EnemyCombatAbilities)
		{
			if (!AbilityClass) continue;
			FGameplayAbilitySpec Spec(AbilityClass);
			Spec.SourceObject = InASCToGive->GetAvatarActor();
			Spec.Level = ApplyLevel;
			InASCToGive->GiveAbility(Spec);
		}
	}
}
