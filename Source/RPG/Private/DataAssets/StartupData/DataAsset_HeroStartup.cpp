// WillTheWater All Rights Reserved

#include "DataAssets/StartupData/DataAsset_HeroStartup.h"
#include "GAS/Abilities/RPGGameplayAbility.h"
#include "GAS/RPGAbilitySystemComponent.h"
#include "DebugHelpers.h"

void UDataAsset_HeroStartup::GiveToASC(URPGAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
    Super::GiveToASC(InASCToGive, ApplyLevel);

    

    for (const FRPGAbilitySet& Abilities : HeroStartAbilitySet)
    {
        if (!Abilities.IsValid()) { continue; }
        
        FGameplayAbilitySpec Spec(Abilities.AbilityToGrant);
        Spec.SourceObject = InASCToGive->GetAvatarActor();
        Spec.Level = ApplyLevel;
        Spec.DynamicAbilityTags.AddTag(Abilities.InputTag);
        InASCToGive->GiveAbility(Spec);
    }
}
