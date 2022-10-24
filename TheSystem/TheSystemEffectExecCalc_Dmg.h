// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "TheSystemEffectExecCalc_Dmg.generated.h"

/**
 * 
 */
UCLASS()
class THESYSTEM_API UTheSystemEffectExecCalc_Dmg : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	UTheSystemEffectExecCalc_Dmg();

	// override the implementation of the execution so we can provide some additional info
	void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
	
};
