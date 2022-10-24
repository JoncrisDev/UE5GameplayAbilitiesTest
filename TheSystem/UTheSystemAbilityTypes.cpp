// Fill out your copyright notice in the Description page of Project Settings.


#include "UTheSystemAbilityTypes.h"

// #include "Abilities/GameplayAbilityTargetTypes.h"

bool FTheSystemGameplayEffectContainerSpec::HasValidEffects() const
{
	return TargetGameplayEffectSpecs.Num() > 0;
}

bool FTheSystemGameplayEffectContainerSpec::HasValidTargets() const
{
	return TargetData.Num() > 0;
}

// Add a new target to this effect
void FTheSystemGameplayEffectContainerSpec::AddTargets(const TArray<FHitResult>& HitResults, const TArray<AActor*>& TargetActors)
{
	// Add the Hit results to this specification
	
	for (const FHitResult & HitResult : HitResults)
	{
		FGameplayAbilityTargetData_SingleTargetHit * NewData = new FGameplayAbilityTargetData_SingleTargetHit(HitResult);
		TargetData.Add(NewData);
		
	}
	
	// Add the Target Actors to this specification
	if (TargetActors.Num() > 0)
	{
		FGameplayAbilityTargetData_ActorArray * NewData = new FGameplayAbilityTargetData_ActorArray();
		NewData->TargetActorArray.Append(TargetActors);
		TargetData.Add(NewData);
	}

	
}
