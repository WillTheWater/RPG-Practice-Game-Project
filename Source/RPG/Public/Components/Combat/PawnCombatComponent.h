// WillTheWater All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnExtComponentBase.h"
#include "GameplayTagContainer.h"
#include "PawnCombatComponent.generated.h"

class AWeaponBase;

UENUM(BlueprintType)
enum class EToggleDamageType : uint8
{
	CurrentEquippedWeapon,
	LeftHand,
	RightHand	
};

UCLASS()
class RPG_API UPawnCombatComponent : public UPawnExtComponentBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "RPG|Combat")
	void RegisterSpawnedWeapon(FGameplayTag InWeaponTag, AWeaponBase* InWeaponRegister, bool bEquippedWeapon = false);

	UFUNCTION(BlueprintCallable, Category = "RPG|Combat")
	AWeaponBase* GetWeaponTag(FGameplayTag InWeaponTag) const;

	UFUNCTION(BlueprintCallable, Category = "RPG|Combat")
	AWeaponBase* GetEquippedWeapon() const;

	UPROPERTY(BlueprintReadWrite, Category = "RPG|Combat")
	FGameplayTag EquippedWeaponTag;
	
	UFUNCTION(BlueprintCallable, Category = "RPG|Combat")
	void ToggleWeaponCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType = EToggleDamageType::CurrentEquippedWeapon); 

	virtual void OnHitTargetActor(AActor* HitActor);
	virtual void OnWeaponPulledFromTargetActor(AActor* OtherActor);
private:
	TMap<FGameplayTag, AWeaponBase*> CharacterCarriedWeaponMap;
};
