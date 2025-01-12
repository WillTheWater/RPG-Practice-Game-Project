// WillTheWater All Rights Reserved


#include "Components/Combat/HeroCombatComponent.h"
#include "Items/Weapons/HeroWeapon.h"

AHeroWeapon* UHeroCombatComponent::GetHeroEquippedWeaponByTag(FGameplayTag WeaponTag) const
{
    return Cast<AHeroWeapon>(GetWeaponTag(WeaponTag));
}