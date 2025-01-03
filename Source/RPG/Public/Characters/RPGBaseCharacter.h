// WillTheWater All Rights Reserved

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "RPGBaseCharacter.generated.h"

class URPGAbilitySystemComponent;
class URPGAttributeSet;
class UDataAsset_StartupBase;

UCLASS()
class RPG_API ARPGBaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ARPGBaseCharacter();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	FORCEINLINE URPGAbilitySystemComponent* GetASComponent() const;
	FORCEINLINE URPGAttributeSet* GetAttributeSet() const;

protected:

	virtual void PossessedBy(AController* NewController) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	URPGAbilitySystemComponent* RPGAbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	URPGAttributeSet* RPGAttributeSet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData")
	TSoftObjectPtr<UDataAsset_StartupBase> CharacterStartupData;

};
