// WillTheWater All Rights Reserved


#include "Characters/RPGEnemyCharacter.h"

#include "Components/Combat/EnemyCombatComponent.h"
#include "DataAssets/StartupData/DataAsset_StartupBase.h"
#include "Engine/AssetManager.h"
#include "GameFramework/CharacterMovementComponent.h"

ARPGEnemyCharacter::ARPGEnemyCharacter()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, 180.f, 0);
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 1000.f;

	EnemyCombatComponent = CreateDefaultSubobject<UEnemyCombatComponent>("EnemyCombatComponent");
}

void ARPGEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitEnemyStartupData();
}

void ARPGEnemyCharacter::InitEnemyStartupData()
{
	if (CharacterStartupData.IsNull()){return;}
	UAssetManager::GetStreamableManager().RequestAsyncLoad(
		CharacterStartupData.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda(
			[this]()
			{
				if (UDataAsset_StartupBase* LoadedData = CharacterStartupData.Get())
				{
					LoadedData->GiveToASC(RPGAbilitySystemComponent);
					GEngine->AddOnScreenDebugMessage(1, 5, FColor::Red, "Data Loaded");
				}
			}
		)
	);
}
