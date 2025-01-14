// WillTheWater All Rights Reserved

#include "Items/Weapons/HeroWeapon.h"

void AHeroWeapon::AssignedGrantedAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& InSpecHandles)
{
    GrantedAbilitySpecHandles = InSpecHandles;
}

TArray<FGameplayAbilitySpecHandle> AHeroWeapon::GetGrantedAbilitySpechandles() const
{
    return GrantedAbilitySpecHandles;
}
