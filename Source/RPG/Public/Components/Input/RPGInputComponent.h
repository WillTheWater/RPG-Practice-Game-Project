// WillTheWater All Rights Reserved

#pragma once
#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "RPGInputComponent.generated.h"

UCLASS()
class RPG_API URPGInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
	
public:
	template<class UserObject, typename CallbackFunction>
	void BindNativeInputAction(const UDataAsset_InputConfig* InInputConfig, const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunction CBFunction);

	template<class UserObject, typename CallbackFunction>
	void BindAbilityInputAction(const UDataAsset_InputConfig* InInputConfig, UserObject* ContextObject, CallbackFunction InputPressed, CallbackFunction InputReleased);
};

template<class UserObject, typename CallbackFunction>
inline void URPGInputComponent::BindNativeInputAction(const UDataAsset_InputConfig* InInputConfig, const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunction CBFunction)
{
	checkf(InInputConfig, TEXT("Iput config data asset is null, can not proceed with binding"));

	if (UInputAction* FoundAction = InInputConfig->FindNativeInputActionByTag(InInputTag))
	{
		BindAction(FoundAction, TriggerEvent, ContextObject, CBFunction);
	}
}

template<class UserObject, typename CallbackFunction>
inline void URPGInputComponent::BindAbilityInputAction(const UDataAsset_InputConfig* InInputConfig, UserObject* ContextObject, CallbackFunction InputPressed, CallbackFunction InputReleased)
{
	checkf(InInputConfig, TEXT("Iput config data asset is null, can not proceed with binding"));

	for (const FRPGInputActionConfig& AIAConfig : InInputConfig->AbilityInputActions)
	{
		if (!AIAConfig.IsValid()) { continue; }
		BindAction(AIAConfig.InputAction, ETriggerEvent::Started, ContextObject, InputPressed, AIAConfig.InputTag);
		BindAction(AIAConfig.InputAction, ETriggerEvent::Completed, ContextObject, InputReleased, AIAConfig.InputTag);
	}
}
