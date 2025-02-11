// WillTheWater All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Characters/RPGBaseCharacter.h"
#include "RPGEnemyCharacter.generated.h"

class UEnemyCombatComponent;

UCLASS()
class RPG_API ARPGEnemyCharacter : public ARPGBaseCharacter
{
	GENERATED_BODY()
public:
	ARPGEnemyCharacter();

	FORCEINLINE UEnemyCombatComponent* GetEnemyCombatComponent() const {return EnemyCombatComponent;}

	protected:

	virtual void PossessedBy(AController* NewController) override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	UEnemyCombatComponent* EnemyCombatComponent;

	private:
	void InitEnemyStartupData();
};
