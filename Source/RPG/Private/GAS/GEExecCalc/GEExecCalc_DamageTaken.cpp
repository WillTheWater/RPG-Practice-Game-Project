// WillTheWater All Rights Reserved


#include "GAS/GEExecCalc/GEExecCalc_DamageTaken.h"
#include "RPGGameplayTags.h"
#include "GAS/RPGAttributeSet.h"
#include "DebugHelpers.h"

struct FRPGDamageCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DefensePower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageTaken)

	FRPGDamageCapture()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, AttackPower, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, DefensePower, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, DamageTaken, Target, false);
	}
};

static const FRPGDamageCapture& GetRPGDamageCapture()
{
	static FRPGDamageCapture RPGDamageCapture;
	return RPGDamageCapture;
}

UGEExecCalc_DamageTaken::UGEExecCalc_DamageTaken()
{
	RelevantAttributesToCapture.Add(GetRPGDamageCapture().AttackPowerDef);
	RelevantAttributesToCapture.Add(GetRPGDamageCapture().DefensePowerDef);
	RelevantAttributesToCapture.Add(GetRPGDamageCapture().DamageTakenDef);
}

void UGEExecCalc_DamageTaken::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	EvaluationParameters.TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	float SourceAttackPower = 0.f;
	DebugPrint::Print(TEXT("SourceAttackPower"), SourceAttackPower);
	float TargetDefensePower = 0.f;
	DebugPrint::Print(TEXT("TargetDefensePower"), TargetDefensePower);
	float BaseDamage = 0.f;
	int32 UsedLightAttackComboCount = 0;
	int32 UsedHeavyAttackComboCount = 0;
	for (const TPair<FGameplayTag, float>& TagMagnitude : Spec.SetByCallerTagMagnitudes)
	{
		if (TagMagnitude.Key.MatchesTagExact(RPGGameplayTags::Shared_SetByCaller_BaseDamage))
		{
			BaseDamage = TagMagnitude.Value;
			DebugPrint::Print(TEXT("BaseDamage"), BaseDamage);

		}
		if (TagMagnitude.Key.MatchesTagExact(RPGGameplayTags::Player_SetByCaller_AttackType_Light))
		{
			UsedLightAttackComboCount = TagMagnitude.Value;
			DebugPrint::Print(TEXT("UsedLightAttackComboCount"), UsedLightAttackComboCount);
		}
		if (TagMagnitude.Key.MatchesTagExact(RPGGameplayTags::Player_SetByCaller_AttackType_Heavy))
		{
			UsedHeavyAttackComboCount = TagMagnitude.Value;
			DebugPrint::Print(TEXT("UsedHeavyAttackComboCount"), UsedHeavyAttackComboCount);
		}
	}
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetRPGDamageCapture().AttackPowerDef, EvaluationParameters, SourceAttackPower);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetRPGDamageCapture().DefensePowerDef, EvaluationParameters, TargetDefensePower);

	if (UsedLightAttackComboCount != 0)
	{
		const float DamageIncreasePerCombo = (UsedLightAttackComboCount - 1) * 0.05f + 1.f;
		BaseDamage *= DamageIncreasePerCombo;
		DebugPrint::Print(TEXT("BaseDamageLight"), BaseDamage);

	}
	if (UsedHeavyAttackComboCount != 0)
	{
		const float DamageIncreasePerCombo = UsedHeavyAttackComboCount * 0.15f + 1.f;
		BaseDamage *= DamageIncreasePerCombo;
		DebugPrint::Print(TEXT("BaseDamageHeavy"), BaseDamage);
	}
	const float FinalDamage = BaseDamage * SourceAttackPower / TargetDefensePower;
	DebugPrint::Print(TEXT("FinalDamage"), FinalDamage);
	if (FinalDamage > 0.f)
	{
		const FGameplayModifierEvaluatedData EvaluatedData(
			GetRPGDamageCapture().DamageTakenProperty,
			EGameplayModOp::Override,
			FinalDamage
		);
		OutExecutionOutput.AddOutputModifier(EvaluatedData);
	}
}
