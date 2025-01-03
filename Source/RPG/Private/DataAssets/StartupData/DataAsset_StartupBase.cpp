// WillTheWater All Rights Reserved


#include "DataAssets/StartupData/DataAsset_StartupBase.h"
#include "GAS/RPGAbilitySystemComponent.h"
#include "GAS/Abilities/RPGGameplayAbility.h"

void UDataAsset_StartupBase::GiveToASC(URPGAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	check(InASCToGive);
	GrantAbilities(ActivateOnGivenAbilities, InASCToGive, ApplyLevel);
	GrantAbilities(ReactiveAbilities, InASCToGive, ApplyLevel);
}

void UDataAsset_StartupBase::GrantAbilities(const TArray<TSubclassOf<URPGGameplayAbility>>& InAbilitiesToGive, URPGAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	if (InAbilitiesToGive.IsEmpty()) { return; }

	for (const TSubclassOf<URPGGameplayAbility>& Ability : InAbilitiesToGive)
	{
		if (Ability) { continue; }

		FGameplayAbilitySpec AbilitySpec(Ability);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		InASCToGive->GiveAbility(AbilitySpec);
	}
}
