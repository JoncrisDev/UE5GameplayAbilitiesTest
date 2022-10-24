// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TheSystem.h"
#include "AbilitySystemComponent.h"
#include "TheSystemAbilitySystemComponent.generated.h"

class UTheSystemGameplayAbility;

/**
 * 
 */
UCLASS()
class THESYSTEM_API UTheSystemAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:

	/** Returns a list of currently active ability instances that match the tags */
	void GetActiveAbilitiesWithTags(const FGameplayTagContainer& GameplayTagContainer, TArray<UTheSystemGameplayAbility*>& ActiveAbilities);

	/** Returns the default level used for ability activations, derived from the character */
	// not implemented here used for illustation purposes only.
	int32 GetDefaultAbilityLevel() const;

	/** Version of function in AbilitySystemGlobals that returns correct type */
	static UTheSystemAbilitySystemComponent* GetAbilitySystemComponentFromActor(const AActor* Actor, bool LookForComponent = false);
};
