// WillTheWater All Rights Reserved


#include "Characters/RPGHeroCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "Components/Input/RPGInputComponent.h"
#include "RPGGameplayTags.h"
#include "GAS/RPGAbilitySystemComponent.h"
#include "DataAssets/StartupData/DataAsset_HeroStartup.h"
#include "Components/Combat/HeroCombatComponent.h"
#include "DebugHelpers.h"

ARPGHeroCharacter::ARPGHeroCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 200.f;
	CameraBoom->SocketOffset = FVector(0.f, 55.f, 65.f);
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	HeroCombatComponent = CreateDefaultSubobject<UHeroCombatComponent>(TEXT("HeroCombatComponent"));
}

UHeroCombatComponent* ARPGHeroCharacter::GetHeroCombatComponent() const
{
	return HeroCombatComponent;
}

void ARPGHeroCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!CharacterStartupData.IsNull())
	{
		if (UDataAsset_StartupBase* LoadedData = CharacterStartupData.LoadSynchronous())
		{
			LoadedData->GiveToASC(RPGAbilitySystemComponent);
		}
	}
}

void ARPGHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	checkf(InputConfigDataAsset, TEXT("Forgot to assign a valid data asset config"));
	ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
	check(Subsystem);
	Subsystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext, 0);
	URPGInputComponent* RPGInputComponent = CastChecked<URPGInputComponent>(PlayerInputComponent);

	RPGInputComponent->BindNativeInputAction(InputConfigDataAsset, RPGGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
	RPGInputComponent->BindNativeInputAction(InputConfigDataAsset, RPGGameplayTags::InputTag_Look, ETriggerEvent::Triggered, this, &ThisClass::Input_Look);
	RPGInputComponent->BindAbilityInputAction(InputConfigDataAsset, this, &ThisClass::Input_AbilityPressed, &ThisClass::Input_AbilityReleased);
}

void ARPGHeroCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ARPGHeroCharacter::Input_Move(const FInputActionValue& ActionValue)
{
	const FVector2D MovementVector = ActionValue.Get<FVector2D>();
	const FRotator MovementRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);

	if (MovementVector.Y != 0.f)
	{
		const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);
		AddMovementInput(ForwardDirection, MovementVector.Y);
	}

	if (MovementVector.X != 0.f)
	{
		const FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ARPGHeroCharacter::Input_Look(const FInputActionValue& ActionValue)
{
	const FVector2D LookAxisVector = ActionValue.Get<FVector2D>();

	if (LookAxisVector.X != 0.f)
	{
		AddControllerYawInput(LookAxisVector.X);
	}
	
	if (LookAxisVector.Y != 0.f)
	{
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ARPGHeroCharacter::Input_AbilityPressed(FGameplayTag InInputTag)
{
	RPGAbilitySystemComponent->OnAbilityInputPressed(InInputTag);
}

void ARPGHeroCharacter::Input_AbilityReleased(FGameplayTag InInputTag)
{
	RPGAbilitySystemComponent->OnAbilityInputReleased(InInputTag);

}
