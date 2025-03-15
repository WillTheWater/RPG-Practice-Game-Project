// WillTheWater All Rights Reserved


#include "Components/Combat/HeroCombatComponent.h"
#include "Items/Weapons/HeroWeapon.h"

AHeroWeapon* UHeroCombatComponent::GetHeroEquippedWeaponByTag(FGameplayTag WeaponTag) const
{
    return Cast<AHeroWeapon>(GetWeaponTag(WeaponTag));
}

void UHeroCombatComponent::OnHitTargetActor(AActor* HitActor)
{
   GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::MakeRandomColor(), "Hit Target");
}

void UHeroCombatComponent::OnWeaponPulledFromTargetActor(AActor* OtherActor)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::MakeRandomColor(), "Stopped Hitting Target");

}
