// WillTheWater All Rights Reserved


#include "RPGFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GAS/RPGAbilitySystemComponent.h"
#include "Interfaces/PawnCombatInterface.h"

URPGAbilitySystemComponent* URPGFunctionLibrary::NativeGetASCFromActor(AActor* InActor)
{
	check(InActor);
	return CastChecked<URPGAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor));
}

void URPGFunctionLibrary::AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag InTag)
{
	URPGAbilitySystemComponent* ASC = NativeGetASCFromActor(InActor);
	if (!ASC->HasMatchingGameplayTag(InTag))
	{
		ASC->AddLooseGameplayTag(InTag);
	}
}

void URPGFunctionLibrary::RemoveGameplayTagIfFound(AActor* InActor, FGameplayTag InTag)
{
	URPGAbilitySystemComponent* ASC = NativeGetASCFromActor(InActor);
	if (ASC->HasMatchingGameplayTag(InTag))
	{
		ASC->RemoveLooseGameplayTag(InTag);
	}
}

bool URPGFunctionLibrary::NativeDoesActorHaveTag(AActor* InActor, FGameplayTag InTag)
{
	URPGAbilitySystemComponent* ASC = NativeGetASCFromActor(InActor);
	return ASC->HasMatchingGameplayTag(InTag);
}

void URPGFunctionLibrary::BP_DoesActorHaveTag(AActor* InActor, FGameplayTag InTag, EConfirmType& ConfirmType)
{
	 ConfirmType = NativeDoesActorHaveTag(InActor, InTag)? EConfirmType::Yes : EConfirmType::No;
}

UPawnCombatComponent* URPGFunctionLibrary::NativeGetPawnCombatComponentFromActor(AActor* InActor)
{
	check(InActor);
	if (IPawnCombatInterface* PCInterface = Cast<IPawnCombatInterface>(InActor))
	{
		return PCInterface->GetPawnCombatComponent();
	}
	return nullptr;
}

UPawnCombatComponent* URPGFunctionLibrary::BP_GetPawnCombatComponentFromActor(AActor* InActor,
	EIRPGValidType& ValidType)
{
	UPawnCombatComponent* CombatComponent = NativeGetPawnCombatComponentFromActor(InActor);
	ValidType = CombatComponent? EIRPGValidType::Valid : EIRPGValidType::Invalid;
	return CombatComponent;
}
