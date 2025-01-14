// WillTheWater All Rights Reserved

#include "RPGTypes/RPGStructTypes.h"
#include "GAS/Abilities/RPGGameplayAbility.h"

bool FRPGAbilitySet::IsValid() const
{
	return InputTag.IsValid() && AbilityToGrant;
}
