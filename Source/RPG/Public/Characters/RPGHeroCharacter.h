// WillTheWater All Rights Reserved

#pragma once
#include "CoreMinimal.h"
#include "Characters/RPGBaseCharacter.h"
#include "GameplayTagContainer.h"
#include "RPGHeroCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UDataAsset_InputConfig;
struct FInputActionValue;
class UHeroCombatComponent;

UCLASS()
class RPG_API ARPGHeroCharacter : public ARPGBaseCharacter
{
	GENERATED_BODY()
	
public:
	ARPGHeroCharacter();

	FORCEINLINE UHeroCombatComponent* GetHeroCombatComponent() const;

protected:
	virtual void PossessedBy(AController* NewController) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;

private:
#pragma region Components

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	UHeroCombatComponent* HeroCombatComponent;

#pragma endregion

	

#pragma region Inputs

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData", meta = (AllowPrivateAccess = "true"))
	UDataAsset_InputConfig* InputConfigDataAsset;

	void Input_Move(const FInputActionValue& ActionValue);
	void Input_Look(const FInputActionValue& ActionValue);
	void Input_AbilityPressed(FGameplayTag InInputTag);
	void Input_AbilityReleased(FGameplayTag InInputTag);

#pragma endregion



};
