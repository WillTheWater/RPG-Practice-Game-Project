// WillTheWater All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RPGFunctionLibrary.generated.h"

struct FGameplayTag;
class URPGAbilitySystemComponent;

UENUM()
enum class EConfirmType : uint8
{
	Yes,
	No
};

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
};