// WillTheWater All Rights Reserved


#include "Components/Combat/PawnCombatComponent.h"
#include "Items/Weapons/WeaponBase.h"

#include "DebugHelpers.h"

void UPawnCombatComponent::RegisterSpawnedWeapon(FGameplayTag InWeaponTag, AWeaponBase* InWeaponRegister, bool bEquippedWeapon)
{
    checkf(!CharacterCarriedWeaponMap.Contains(InWeaponTag), TEXT("Weapon %s Already Registered"), *InWeaponTag.ToString());
    check(InWeaponRegister)

        CharacterCarriedWeaponMap.Emplace(InWeaponTag, InWeaponRegister);

    if (bEquippedWeapon)
    {
        EquippedWeaponTag = InWeaponTag;
    }
    
    const FString WeapStr = FString::Printf(TEXT("Weapon %s Registered"), *InWeaponRegister->GetName());
    DebugPrint::Print(WeapStr);
}

AWeaponBase* UPawnCombatComponent::GetWeaponTag(FGameplayTag InWeaponTag) const
{
    if (CharacterCarriedWeaponMap.Contains(InWeaponTag))
    {
        if (AWeaponBase* const* FoundWeapon = CharacterCarriedWeaponMap.Find(InWeaponTag))
        {
            return *FoundWeapon;
        }
    }
    return nullptr;
}

AWeaponBase* UPawnCombatComponent::GetEquippedWeapon() const
{
    if (!EquippedWeaponTag.IsValid())
    {
        return nullptr;
    }
    return GetWeaponTag(EquippedWeaponTag);
}
