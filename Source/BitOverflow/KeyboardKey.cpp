// Fill out your copyright notice in the Description page of Project Settings.

#include "BitOverflow.h"
#include "KeyboardKey.h"



// Sets default values
AKeyboardKey::AKeyboardKey()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BaseCollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BaseCollisionComponent"));
	RootComponent = BaseCollisionComponent;

	// Create the base static mesh for our key
	KeyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KeyMesh"));
	KeyMesh->AttachTo(RootComponent);

	// Create our text render to display info to player
	TextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRenderComponent"));
	TextRenderComponent->AttachTo(RootComponent);
}

// Called when the game starts or when spawned
void AKeyboardKey::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AKeyboardKey::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AKeyboardKey::CreateKey(FText key, AHackTerminal* parent) {

	check(parent != nullptr);
	Letter = key;
	// TODO implement functionaity
	TextRenderComponent->SetText(key);
	ParentTerminal = parent;

}
