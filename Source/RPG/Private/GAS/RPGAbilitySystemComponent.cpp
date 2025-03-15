// WillTheWater All Rights Reserved


#include "GAS/RPGAbilitySystemComponent.h"

#include "RPGGameplayTags.h"
#include "RPGTypes/RPGStructTypes.h"
#include "GAS/Abilities/RPGGameplayAbility.h"

void URPGAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InInput)
{
	if (!InInput.IsValid()) { return; }

	for (const FGameplayAbilitySpec& Spec : GetActivatableAbilities())
	{
		if (!Spec.DynamicAbilityTags.HasTagExact(InInput)) { continue; }

		TryActivateAbility(Spec.Handle);
	}
}

void URPGAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InInput)
{
	if (!InInput.IsValid() || !InInput.MatchesTag(RPGGameplayTags::InputTag_MustBeHeld))
	{
		return;
	}
	for (const FGameplayAbilitySpec& Spec : GetActivatableAbilities())
	{
		if (!Spec.DynamicAbilityTags.HasTagExact(InInput) && Spec.IsActive())
		{
			CancelAbilityHandle(Spec.Handle);
		}
	}
}

void URPGAbilitySystemComponent::GrantHeroWeaponAbilities(const TArray<FRPGAbilitySet>& InDefaultWeaponAbilities, int32 ApplyLevel, TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandle)
{
	if (InDefaultWeaponAbilities.IsEmpty()) { return; }

	for (const FRPGAbilitySet& Ability : InDefaultWeaponAbilities)
	{
		if (!Ability.IsValid()) { continue; }
		FGameplayAbilitySpec Spec(Ability.AbilityToGrant);
		Spec.SourceObject = GetAvatarActor();
		Spec.Level = ApplyLevel;
		Spec.DynamicAbilityTags.AddTag(Ability.InputTag);
		
		OutGrantedAbilitySpecHandle.AddUnique(GiveAbility(Spec));
	}
}

void URPGAbilitySystemComponent::RemoveGrantHeroWeaponAbilities(UPARAM(ref)TArray<FGameplayAbilitySpecHandle>& RemoveAbilitySpecHandle)
{
	if (RemoveAbilitySpecHandle.IsEmpty()) { return; }
	for (const FGameplayAbilitySpecHandle SpecHandle : RemoveAbilitySpecHandle)
	{
		if (SpecHandle.IsValid())
		{
			ClearAbility(SpecHandle);
		}
	}
	RemoveAbilitySpecHandle.Empty();
}
