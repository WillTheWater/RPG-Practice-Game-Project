// WillTheWater All Rights Reserved


#include "GAS/Abilities/RPGGameplayAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Components/Combat/PawnCombatComponent.h"
#include "GAS/RPGAbilitySystemComponent.h"

void URPGGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);

	if (AbilityActivationPolicy == ERPGAbilityActivationPolicy::ON_GIVEN)
	{
		if (ActorInfo && !Spec.IsActive())
		{
			ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
		}
	}
}

void URPGGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if (AbilityActivationPolicy == ERPGAbilityActivationPolicy::ON_GIVEN)
	{
		if (ActorInfo)
		{
			ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
		}
	}
}

UPawnCombatComponent* URPGGameplayAbility::GetPawnCombatComponentFromActorInfo() const
{
	return GetAvatarActorFromActorInfo()->FindComponentByClass<UPawnCombatComponent>();
	
}

URPGAbilitySystemComponent* URPGGameplayAbility::GetRPGAbilitySystemComponentFromActorInfo() const
{
	return Cast<URPGAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);
}

FActiveGameplayEffectHandle URPGGameplayAbility::NativeApplyEffectSpecHandleToTarget(AActor* Target,
	const FGameplayEffectSpecHandle& InSpecHandle)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target);
	check(TargetASC);
	check(InSpecHandle.IsValid());

	return GetRPGAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(*InSpecHandle.Data, TargetASC);
}

FActiveGameplayEffectHandle URPGGameplayAbility::ApplyEffectSpecHandleToTarget(AActor* Target,
	const FGameplayEffectSpecHandle& InSpecHandle, ERPGSuccessType& OutSuccessType)
{
	FActiveGameplayEffectHandle ActiveGEHandle = NativeApplyEffectSpecHandleToTarget(Target, InSpecHandle);
	OutSuccessType =ActiveGEHandle.WasSuccessfullyApplied()? ERPGSuccessType::Successful : ERPGSuccessType::Failed;
	return ActiveGEHandle;
}
