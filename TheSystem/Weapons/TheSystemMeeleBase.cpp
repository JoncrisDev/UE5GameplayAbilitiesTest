// Fill out your copyright notice in the Description page of Project Settings.


#include "TheSystemMeeleBase.h"

#include "NavigationSystemTypes.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ATheSystemMeeleBase::ATheSystemMeeleBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeleeMeshCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision Component"));
	RootComponent = MeleeMeshCollision;	
	MeleeMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Meele Mesh"));
	MeleeMesh->SetupAttachment(RootComponent);
}

// Initialize the mesh component into the actor
void ATheSystemMeeleBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

// Called when the game starts or when spawned
void ATheSystemMeeleBase::BeginPlay()
{
	Super::BeginPlay();
}

FVector ATheSystemMeeleBase::GetMeleeMidPoint() const
{
	check(AttachPoint.IsValid() &&  MeleeEndPoint.IsValid());
	const FVector WeaponStartLocation = MeleeMesh->GetSocketLocation(AttachPoint);
	const FVector WeaponEndLocation = MeleeMesh->GetSocketLocation(MeleeEndPoint);
	return WeaponEndLocation - WeaponStartLocation;
}

// Called every frame
void ATheSystemMeeleBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

