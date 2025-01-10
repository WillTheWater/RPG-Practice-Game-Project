// WillTheWater All Rights Reserved


#include "GAS/RPGAbilitySystemComponent.h"

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
}
