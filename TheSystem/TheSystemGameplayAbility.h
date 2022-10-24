// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "TheSystemGameplayAbility.generated.h"

/**
 *  Subclass of the the ability blueprint type.
 *  Containers a list of the gameplay effects to trigger based on a tag.
 */
UCLASS()
class THESYSTEM_API UTheSystemGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:

	UTheSystemGameplayAbility();

	/* Map of the gameplay tags to gameplay effect containers */
	/*
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayEffects)
	TMap<FGameplayTag, UTheSystemGameplayEffectContainer> EffectContainerMap;
	*/
	

	
	
};
