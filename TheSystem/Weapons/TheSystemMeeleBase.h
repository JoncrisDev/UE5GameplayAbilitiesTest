// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/ActorComponent.h"
#include "TheSystemMeeleBase.generated.h"

class UCapsuleComponent;

UCLASS(Config=game)
class THESYSTEM_API ATheSystemMeeleBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATheSystemMeeleBase();

	UPROPERTY(Category=Character, VisibleAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent * MeleeMesh;
	
	UPROPERTY(Category=Character, VisibleAnywhere, BlueprintReadWrite)
	UCapsuleComponent * MeleeMeshCollision;

	// The Point at which to attach out mesh to the character
	UPROPERTY(Category=Character, VisibleAnywhere, BlueprintReadWrite)
	FName AttachPoint;

	// A point situated at the end of the meele item used in determining length.
	UPROPERTY(Category=Character, VisibleAnywhere, BlueprintReadWrite)
	FName MeleeEndPoint;

	virtual void PostInitializeComponents() override;

private:
	UPROPERTY(Category=Character, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> MeleeMeshClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Get the point in the middle of the item
	virtual FVector GetMeleeMidPoint() const;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
