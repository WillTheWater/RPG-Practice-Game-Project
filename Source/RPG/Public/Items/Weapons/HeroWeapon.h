// WillTheWater All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Items/Weapons/WeaponBase.h"
#include "RPGTypes/RPGStructTypes.h"
#include "GameplayAbilitySpecHandle.h"
#include "HeroWeapon.generated.h"

UCLASS()
class RPG_API AHeroWeapon : public AWeaponBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponData")
	FRPGHeroWeaponData HeroWeaponData;

	UFUNCTION(BlueprintCallable)
	void AssignedGrantedAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& InSpecHandles);
	
	UFUNCTION(BlueprintPure)
	TArray<FGameplayAbilitySpecHandle> GetGrantedAbilitySpechandles() const;

private:
	TArray<FGameplayAbilitySpecHandle> GrantedAbilitySpecHandles;
};
