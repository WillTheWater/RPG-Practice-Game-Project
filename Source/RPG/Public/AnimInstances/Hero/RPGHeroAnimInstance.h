// WillTheWater All Rights Reserved

#pragma once
#include "CoreMinimal.h"
#include "AnimInstances/RPGCharacterAnimInstance.h"
#include "RPGHeroAnimInstance.generated.h"

class ARPGHeroCharacter;

UCLASS()
class RPG_API URPGHeroAnimInstance : public URPGCharacterAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|References")
	ARPGHeroCharacter* OwningHeroCharacter;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	bool bShouldEnterRelaxState;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	float EnterRelaxedStateThreshold = 5.f;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	float ElapsedTime;

};
