// WillTheWater All Rights Reserved


#include "AnimInstances/RPGCharacterAnimInstance.h"
#include "Characters/RPGBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void URPGCharacterAnimInstance::NativeInitializeAnimation()
{
	OwningCharacter = Cast<ARPGBaseCharacter>(TryGetPawnOwner());
	if (OwningCharacter)
	{
		OwningMovementComponent = OwningCharacter->GetCharacterMovement();
	}
}

void URPGCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if (!OwningCharacter || !OwningMovementComponent) { return; }

	GroundSpeed = OwningCharacter->GetVelocity().Size2D();
	bHasAcceleration = OwningMovementComponent->GetCurrentAcceleration().SizeSquared2D() > 0.f;
}
