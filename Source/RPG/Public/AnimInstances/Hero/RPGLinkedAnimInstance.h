// WillTheWater All Rights Reserved

#pragma once
#include "CoreMinimal.h"
#include "AnimInstances/RPGBaseAnimInstance.h"
#include "RPGLinkedAnimInstance.generated.h"

class URPGHeroAnimInstance;

UCLASS()
class RPG_API URPGLinkedAnimInstance : public URPGBaseAnimInstance
{
	GENERATED_BODY()

	public:
	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	URPGHeroAnimInstance* GetHeroAnimInstance() const;
	
};
