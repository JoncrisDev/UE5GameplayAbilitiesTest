// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
// #include "GameplayAbilityTargetTypes"
#include "Abilities/GameplayAbilityTargetTypes.h"
#include "GameplayEffect.h"
#include "UTheSystemAbilityTypes.generated.h"

class UTheSystemTargetType;

// Struct defining a list of gameplay effects, an associated tag and targeting info.
USTRUCT(BlueprintType)
struct FTheSystemGameplayEffectContainer
{
	GENERATED_BODY()

public:
	
	FTheSystemGameplayEffectContainer() {}

	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GameplayEffectContainer)
	// TSubclassOf<UTheSystemTargetType> TargetType; // we do not have this yet.

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GameplayEffectContainer)
	TArray<TSubclassOf<UGameplayEffect>> TargetGameplayEffectClasses;
};

/** A "processed" version of UTheSystemEffectContainer that can be passed around and eventually applied */
USTRUCT(BlueprintType)
struct FTheSystemGameplayEffectContainerSpec
{
	GENERATED_BODY()

public:
	FTheSystemGameplayEffectContainerSpec() {}

	/** Computed target data */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GameplayEffectContainer)
	FGameplayAbilityTargetDataHandle TargetData;

	/** List of gameplay effects to apply to the targets */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GameplayEffectContainer)
	TArray<FGameplayEffectSpecHandle> TargetGameplayEffectSpecs;

	/** Returns true if this has any valid effect specs */
	bool HasValidEffects() const;

	/** Returns true if this has any valid targets */
	bool HasValidTargets() const;

	/** Adds new targets to target data */
	void AddTargets(const TArray<FHitResult>& HitResults, const TArray<AActor*>& TargetActors);
};