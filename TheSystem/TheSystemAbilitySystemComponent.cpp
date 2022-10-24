// Fill out your copyright notice in the Description page of Project Settings.


#include "TheSystemAbilitySystemComponent.h"
#include "TheSystemCharacter.h"
#include "TheSystemGameplayAbility.h" 
#include "AbilitySystemGlobals.h"

void UTheSystemAbilitySystemComponent::GetActiveAbilitiesWithTags(const FGameplayTagContainer& GameplayTagContainer, TArray<UTheSystemGameplayAbility*>& ActiveAbilities)
{
	TArray<FGameplayAbilitySpec*> AbilitiesToActivate;
	GetActivatableGameplayAbilitySpecsByAllMatchingTags(GameplayTagContainer, AbilitiesToActivate, false);

	// iterate through the list of activatable specifications
	for (FGameplayAbilitySpec* Spec : AbilitiesToActivate) {

		TArray<UGameplayAbility*> AbilityInstances = Spec->GetAbilityInstances();

		// Iterate through each instance of this specification
		for (UGameplayAbility* ActiveAbility : AbilityInstances) {
			ActiveAbilities.Add(Cast<UTheSystemGameplayAbility>(ActiveAbility));
		}
	}
}

// This should return the current progression value which we do not currently implement.
// [DO NOT CALL ME]
int32 UTheSystemAbilitySystemComponent::GetDefaultAbilityLevel() const
{
	return -1;
}

UTheSystemAbilitySystemComponent* UTheSystemAbilitySystemComponent::GetAbilitySystemComponentFromActor(const AActor* Actor, bool LookForComponent)
{
	return Cast<UTheSystemAbilitySystemComponent>(UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Actor, LookForComponent));
}
