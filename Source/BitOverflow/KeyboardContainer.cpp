// Fill out your copyright notice in the Description page of Project Settings.

#include "BitOverflow.h"
#include "KeyboardContainer.h"


// Sets default values
AKeyboardContainer::AKeyboardContainer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create our root component
	BaseCollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BaseCollisionComponent"));
	RootComponent = BaseCollisionComponent;

	// Create the static mesh component and attach the StaticMeshComponent to the root component
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->AttachTo(RootComponent);
}

// Called when the game starts or when spawned
void AKeyboardContainer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKeyboardContainer::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

