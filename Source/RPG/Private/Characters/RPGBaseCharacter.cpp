// WillTheWater All Rights Reserved

#include "Characters/RPGBaseCharacter.h"
#include "GAS/RPGAbilitySystemComponent.h"
#include "GAS/RPGAttributeSet.h"

ARPGBaseCharacter::ARPGBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetMesh()->bReceivesDecals = false;

	RPGAbilitySystemComponent = CreateDefaultSubobject<URPGAbilitySystemComponent>(TEXT("RPGAbilitySystemComponent"));
	RPGAttributeSet = CreateDefaultSubobject<URPGAttributeSet>(TEXT("RPGAttributeSet"));
}

UAbilitySystemComponent* ARPGBaseCharacter::GetAbilitySystemComponent() const
{
	return GetASComponent();
}

URPGAbilitySystemComponent* ARPGBaseCharacter::GetASComponent() const
{
	return RPGAbilitySystemComponent;
}

URPGAttributeSet* ARPGBaseCharacter::GetAttributeSet() const
{
	return RPGAttributeSet;
}

void ARPGBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (RPGAbilitySystemComponent)
	{
		RPGAbilitySystemComponent->InitAbilityActorInfo(this, this);

		//ensureMsgf(!CharacterStartupData.IsNull(), TEXT("No Assigned Startup Data to %s"), *GetName());
	}
}

