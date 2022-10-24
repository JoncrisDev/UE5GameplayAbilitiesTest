// Fill out your copyright notice in the Description page of Project Settings.
#include "TheSystemAttributeSet.h"
#include "TheSystemCharacter.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"

UTheSystemAttributeSet::UTheSystemAttributeSet() : Health(0.5f) {}

// Should only be used for clamping attribute values.
void UTheSystemAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) {

	if (Attribute == GetMaxHealthAttribute()) {
		// Scale current Health to maintain the same ration between the Max value.
		AdjustAttributeForMaxChange(Health, MaxHealth, NewValue, GetHealthAttribute());
	}
}

void UTheSystemAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) {

	Super::PostGameplayEffectExecute(Data);

	// compute the data between the old and the new values
	float DeltaValue = 0;
	if(Data.EvaluatedData.ModifierOp == EGameplayModOp::Type::Additive)
	{
		DeltaValue = Data.EvaluatedData.Magnitude;
	}
	
	// Deal with the logic that occurs after a gameplay effect has finished.
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		// SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
	}

	if(Data.EvaluatedData.Attribute == GetShieldAttribute())
	{
		// SetShield(FMath::Clamp(GetShield(), 0.0f, GetMaxShield()));
	}
	
	if(Data.EvaluatedData.Attribute == GetExplosionDamageHurtAttribute())
	{
		// SetExplosionDamageHurt(FMath::Clamp(GetExplosionDamageHurt(), 0.0f, GetMaxHealth()));
	}
}

// Update on Health replication
void UTheSystemAttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue) {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTheSystemAttributeSet, Health, OldValue);
}

// Update on Max Health replication
void UTheSystemAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue) {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTheSystemAttributeSet, MaxHealth, OldValue);
}

// Update on Shield replication
void UTheSystemAttributeSet::OnRep_Shield(const FGameplayAttributeData& OldValue) {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTheSystemAttributeSet, Shield, OldValue);
}

// Update on Max Shield replication
void UTheSystemAttributeSet::OnRep_MaxShield(const FGameplayAttributeData& OldValue) {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTheSystemAttributeSet, MaxShield, OldValue);
}

// Update on Max Shield replication
void UTheSystemAttributeSet::OnRep_ExplosionDamageHurt(const FGameplayAttributeData& OldValue) {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTheSystemAttributeSet, ExplosionDamageHurt, OldValue);
}

void UTheSystemAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UTheSystemAttributeSet, Health);
	DOREPLIFETIME(UTheSystemAttributeSet, MaxHealth);
	DOREPLIFETIME(UTheSystemAttributeSet, Shield);
	DOREPLIFETIME(UTheSystemAttributeSet, MaxShield);
	DOREPLIFETIME(UTheSystemAttributeSet, ExplosionDamageHurt);
}

// adjust the ratios for a new Maximum value.
void UTheSystemAttributeSet::AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty) {

	UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
	const float CurrentMaxValue = MaxAttribute.GetCurrentValue();
	if (!FMath::IsNearlyZero(CurrentMaxValue, NewMaxValue) && AbilityComp) {
	
		const float CurrentValue = AffectedAttribute.GetCurrentValue();
		// This represents the change that should be added to the current value of the affected attribute.
		float NewDelta = (CurrentMaxValue > 0.0f) ? (CurrentValue * NewMaxValue / CurrentMaxValue) - CurrentValue : NewMaxValue;
		
		// apply this amount to the owners ability set
		// runs on client and server
		AbilityComp->ApplyModToAttributeUnsafe(AffectedAttributeProperty, EGameplayModOp::Additive, NewDelta);
	}

}
