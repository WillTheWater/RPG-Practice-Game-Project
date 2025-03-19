// WillTheWater All Rights Reserved


#include "Components/Combat/HeroCombatComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "RPGGameplayTags.h"
#include "Items/Weapons/HeroWeapon.h"

AHeroWeapon* UHeroCombatComponent::GetHeroEquippedWeaponByTag(FGameplayTag WeaponTag) const
{
    return Cast<AHeroWeapon>(GetWeaponTag(WeaponTag));
}

void UHeroCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	if (OverlappedActors.Contains(HitActor))
	{
		return;
	}
	OverlappedActors.AddUnique(HitActor);
	FGameplayEventData Data;
	Data.Instigator = GetOwningPawn();
	Data.Target = HitActor;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(),RPGGameplayTags::Shared_Event_MeleeHit, Data);
}

void UHeroCombatComponent::OnWeaponPulledFromTargetActor(AActor* OtherActor)
{

}
