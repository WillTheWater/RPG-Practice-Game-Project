// WillTheWater All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RPGTypes/RPGEnumTypes.h"
#include "RPGFunctionLibrary.generated.h"

class UPawnCombatComponent;
struct FGameplayTag;
class URPGAbilitySystemComponent;

UCLASS()
class RPG_API URPGFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static URPGAbilitySystemComponent* NativeGetASCFromActor(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category = "FunctionLibrary")
	static void AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag InTag);

	UFUNCTION(BlueprintCallable, Category = "FunctionLibrary")
	static void RemoveGameplayTagIfFound(AActor* InActor, FGameplayTag InTag);

	static bool NativeDoesActorHaveTag(AActor* InActor, FGameplayTag InTag);
	
	UFUNCTION(BlueprintCallable, Category = "FunctionLibrary", meta = (DisplayName = "DoesActorHaveTag", ExpandEnumAsExecs = "ConfirmType"))
	static void BP_DoesActorHaveTag(AActor* InActor, FGameplayTag InTag, EConfirmType& ConfirmType);

	static UPawnCombatComponent* NativeGetPawnCombatComponentFromActor(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category = "FunctionLibrary", meta = (DisplayName = "GetPawnCombatComponentFromActor", ExpandEnumAsExecs = "ValidType"))
	static UPawnCombatComponent* BP_GetPawnCombatComponentFromActor(AActor* InActor, EIRPGValidType& ValidType);
	
};