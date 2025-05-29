// WillTheWater All Rights Reserved


#include "GAS/GEExecCalc/GEExecCalc_DamageTaken.h"
#include "GAS/RPGAttributeSet.h"

struct FRPGDamageCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DefensePower)

	FRPGDamageCapture()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, AttackPower, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, DefensePower, Target, false);
	}
};

static const FRPGDamageCapture& GetRPGDamageCapture()
{
	static FRPGDamageCapture RPGDamageCapture;
	return RPGDamageCapture;
}

UGEExecCalc_DamageTaken::UGEExecCalc_DamageTaken()
{
	// FProperty* AttackPowerProperty = FindFieldChecked<FProperty>(
	// URPGAttributeSet::StaticClass(),
	// GET_MEMBER_NAME_CHECKED(URPGAttributeSet, AttackPower)
	// );
	// FGameplayEffectAttributeCaptureDefinition AttackPowerDef(
	// 	AttackPowerProperty,
	// 	EGameplayEffectAttributeCaptureSource::Source,
	// 	false
	// 	);
	// RelevantAttributesToCapture.Add(AttackPowerDef);

	RelevantAttributesToCapture.Add(GetRPGDamageCapture().AttackPowerDef);
	RelevantAttributesToCapture.Add(GetRPGDamageCapture().DefensePowerDef);
}
