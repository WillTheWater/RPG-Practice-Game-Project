// WillTheWater All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/RPGBaseAnimInstance.h"
#include "Characters/RPGBaseCharacter.h"
#include "RPGCharacterAnimInstance.generated.h"

class ARPGBaseCharacter;
class UCharacterMovementComponent;

UCLASS()
class RPG_API URPGCharacterAnimInstance : public URPGBaseAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds);

protected:
	UPROPERTY()
	ARPGBaseCharacter* OwningCharacter;
	
	UPROPERTY()
	UCharacterMovementComponent* OwningMovementComponent;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	float GroundSpeed;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	bool bHasAcceleration;
};
