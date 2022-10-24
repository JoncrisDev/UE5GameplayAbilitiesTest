// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "TheSystemAttributeSet.generated.h"

// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class THESYSTEM_API UTheSystemAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:

	// See the UAtttributeSet header for a fancy way to set values by spreadsheet.
	UTheSystemAttributeSet();

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	// called after a gameplay effect has finished.
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& Props) const override;
	virtual void AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData MaxAttribute, float NewValue, const FGameplayAttribute& AffectedAttributeProperty);

	// Store health as an attribute and define a rep function.
	UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UTheSystemAttributeSet, Health);

	// Store Maxhealth as an attribute and define a rep function.
	UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UTheSystemAttributeSet, MaxHealth);

	// Shield Provides defense power against incoming attacks
	UPROPERTY(BlueprintReadOnly, Category = "Health", Replicated = OnRep_Shield)
	FGameplayAttributeData Shield;
	ATTRIBUTE_ACCESSORS(UTheSystemAttributeSet, Shield);
	
	// Max Shield 
	UPROPERTY(BlueprintReadOnly, Category = "Health", Replicated = OnRep_MaxShield)
	FGameplayAttributeData MaxShield;
	ATTRIBUTE_ACCESSORS(UTheSystemAttributeSet, MaxShield);
	
	// Explosion Damage effecting amount  
	UPROPERTY(BlueprintReadOnly, Category = "Health", Replicated = OnRep_ExplosionDamage)
	FGameplayAttributeData ExplosionDamageHurt;
	ATTRIBUTE_ACCESSORS(UTheSystemAttributeSet, ExplosionDamageHurt);
	

protected:

	UFUNCTION()
		virtual void OnRep_Health(const FGameplayAttributeData& OldValue);

	UFUNCTION()
		virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldValue);
	
	UFUNCTION()
		virtual void OnRep_Shield(const FGameplayAttributeData& OldValue);
	
	UFUNCTION()
		virtual void OnRep_MaxShield(const FGameplayAttributeData& OldValue);
	
	UFUNCTION()
		virtual void OnRep_ExplosionDamageHurt(const FGameplayAttributeData& OldValue);
};
