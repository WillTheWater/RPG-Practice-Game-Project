// WillTheWater All Rights Reserved


#include "GAS/Abilities/RPGHeroGameplayAbility.h"

#include "RPGGameplayTags.h"
#include "Characters/RPGHeroCharacter.h"
#include "Controllers/RPGHeroController.h"
#include "Components/Combat/HeroCombatComponent.h"
#include "GAS/RPGAbilitySystemComponent.h"


ARPGHeroCharacter* URPGHeroGameplayAbility::GetHeroCharacterFromActorInfo()
{
    if (!CachedHeroCharacter.IsValid())
    {
        CachedHeroCharacter = Cast<ARPGHeroCharacter>(CurrentActorInfo->AvatarActor);
    }
    return CachedHeroCharacter.IsValid() ? CachedHeroCharacter.Get() : nullptr;
}

ARPGHeroController* URPGHeroGameplayAbility::GetHeroControllerFromActorInfo()
{
    if (!CachedHeroController.IsValid())
    {
        CachedHeroController = Cast<ARPGHeroController>(CurrentActorInfo->PlayerController);
    }
    return CachedHeroController.IsValid() ? CachedHeroController.Get() : nullptr;
}

UHeroCombatComponent* URPGHeroGameplayAbility::GetHeroCombatComponentFromActorInfo()
{
    return GetHeroCharacterFromActorInfo()->GetHeroCombatComponent();
}

FGameplayEffectSpecHandle URPGHeroGameplayAbility::MakeHeroDamageEffectSpecHandle(
    TSubclassOf<UGameplayEffect> EffectClass, float InWeaponDamage, FGameplayTag InCurrentAttackTypeTag,
    int32 InUsedComboCount)
{
    check (EffectClass);
    FGameplayEffectContextHandle EffectContext = GetRPGASCFromActorInfo()->MakeEffectContext();
    EffectContext.SetAbility(this);
    EffectContext.AddSourceObject(GetAvatarActorFromActorInfo());
    EffectContext.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());
    FGameplayEffectSpecHandle EffectSpecHandle = GetRPGASCFromActorInfo()->MakeOutgoingSpec(EffectClass, GetAbilityLevel(), EffectContext);
    EffectSpecHandle.Data->SetSetByCallerMagnitude(RPGGameplayTags::Shared_SetByCaller_BaseDamage, InWeaponDamage);
    if (InCurrentAttackTypeTag.IsValid())
    {
        EffectSpecHandle.Data->SetSetByCallerMagnitude(InCurrentAttackTypeTag, InUsedComboCount);
    }
    return EffectSpecHandle;
}
