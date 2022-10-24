// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TheSystemCharacter.h"
#include "Weapons/TheSystemMeeleBase.h"
#include "TheSystemCharacter_Fancy.generated.h"

/**
 * 
 */
UCLASS()
class THESYSTEM_API ATheSystemCharacter_Fancy : public ATheSystemCharacter
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category= "Weapon")
	class TSubclassOf <ATheSystemMeeleBase> MeeleWeapon;
	
	
};
