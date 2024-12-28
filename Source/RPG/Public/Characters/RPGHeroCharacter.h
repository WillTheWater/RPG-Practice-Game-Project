// WillTheWater All Rights Reserved

#pragma once
#include "CoreMinimal.h"
#include "Characters/RPGBaseCharacter.h"
#include "RPGHeroCharacter.generated.h"

UCLASS()
class RPG_API ARPGHeroCharacter : public ARPGBaseCharacter
{
	GENERATED_BODY()
	
public:
	ARPGHeroCharacter();

protected:
	virtual void BeginPlay() override;

private:
#pragma region Components

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

#pragma endregion
};
