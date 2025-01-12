// WillTheWater All Rights Reserved

#include "AnimInstances/Hero/RPGLinkedAnimInstance.h"
#include "AnimInstances/Hero/RPGHeroAnimInstance.h"

URPGHeroAnimInstance* URPGLinkedAnimInstance::GetHeroAnimInstance() const
{
    return Cast<URPGHeroAnimInstance>(GetOwningComponent()->GetAnimInstance());
}
