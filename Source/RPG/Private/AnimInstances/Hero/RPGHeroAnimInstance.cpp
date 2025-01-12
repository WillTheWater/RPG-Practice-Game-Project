// WillTheWater All Rights Reserved

#include "AnimInstances/Hero/RPGHeroAnimInstance.h"
#include "Characters/RPGHeroCharacter.h"


void URPGHeroAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (OwningCharacter)
	{
		OwningHeroCharacter = Cast<ARPGHeroCharacter>(OwningCharacter); 
	}
}

void URPGHeroAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
	if (bHasAcceleration)
	{
		ElapsedTime = 0.f;
		bShouldEnterRelaxState = false;
	}
	else
	{
		ElapsedTime += DeltaSeconds;
		bShouldEnterRelaxState = (ElapsedTime >= EnterRelaxedStateThreshold);
	}
}
