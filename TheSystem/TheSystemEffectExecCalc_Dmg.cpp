// Fill out your copyright notice in the Description page of Project Settings.
#include "TheSystemEffectExecCalc_Dmg.h"

#include "AbilitySystemComponent.h"
#include "TheSystemAttributeSet.h"

struct FExplosionDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Shield);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Health);

	// [NOTE TO SELF]
	// This is a fucking stupid thing, when this works look to see how you actually get the value?/mag whatever from the owning effect.
	DECLARE_ATTRIBUTE_CAPTUREDEF(ExplosionDamageHurt);
	
	FExplosionDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UTheSystemAttributeSet, Shield, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UTheSystemAttributeSet, Health, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UTheSystemAttributeSet, ExplosionDamageHurt, Source, true);
	}
	
};

static const FExplosionDamageStatics & ExplosionDamageStatics()
{
	static FExplosionDamageStatics ExpDmgStatics;
	return ExpDmgStatics;
}

// capture attributes as required
UTheSystemEffectExecCalc_Dmg::UTheSystemEffectExecCalc_Dmg()
{
	RelevantAttributesToCapture.Add(ExplosionDamageStatics().ShieldDef);
	RelevantAttributesToCapture.Add(ExplosionDamageStatics().HealthDef);
	RelevantAttributesToCapture.Add(ExplosionDamageStatics().ExplosionDamageHurtDef);
}


// Implement the damage execution
void UTheSystemEffectExecCalc_Dmg::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                                          FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();
	UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();

	AActor* TargetActor  = TargetASC ? TargetASC->GetAvatarActor() : NULL;
	AActor* SourceActor  = SourceASC ? SourceASC->GetAvatarActor() : NULL;

	// we do need to process  the tags as this can be passed along.
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	// some kind of little packing struct
	FAggregatorEvaluateParameters EvalParams;
	EvalParams.SourceTags = SourceTags;
	EvalParams.TargetTags = TargetTags;

	// Try to get the health attribute by using the static macro def
	float Health = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(ExplosionDamageStatics().HealthDef, EvalParams, Health);

	// Try gettings the shield
	float Shield = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(ExplosionDamageStatics().ShieldDef, EvalParams, Shield);

	// Try gettings from the amoount of damage an explosion should do.
	float ExplosionEffect = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(ExplosionDamageStatics().ExplosionDamageHurtDef, EvalParams, ExplosionEffect);

	float ShieldDmgNegationRatio = 0.5f;
	float DeltaShield =  -1 * (ExplosionEffect * ShieldDmgNegationRatio);
	float DeltaHealth =  -1 * (ExplosionEffect * ShieldDmgNegationRatio);

	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(ExplosionDamageStatics().HealthProperty, EGameplayModOp::Additive, DeltaHealth));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(ExplosionDamageStatics().ShieldProperty, EGameplayModOp::Additive, DeltaShield));
}
