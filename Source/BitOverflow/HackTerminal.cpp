// Fill out your copyright notice in the Description page of Project Settings.

#include "BitOverflow.h"
#include "HackTerminal.h"
#include "KeyboardKey.h"
#include "KeyboardContainer.h"

// Sets default values
AHackTerminal::AHackTerminal()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create our root component
	BaseCollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BaseCollisionComponent"));
	RootComponent = BaseCollisionComponent;

	// Create the static mesh component and attach the StaticMeshComponent to the root component
	TerminalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TerminalMesh"));
	TerminalMesh->AttachTo(RootComponent);

	// Create a collision mesh to detect the player
	InteractCollisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("InteractCollisionComponent"));
	InteractCollisionComponent->AttachTo(RootComponent);

	// Create our text render to display info to player
	TextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRenderComponent"));
	TextRenderComponent->AttachTo(RootComponent);
	SubTextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("SubTextComponent"));
	SubTextComponent->AttachTo(RootComponent);

	// Create a component to store the location/rotation of the keyboard
	// Spawn the keyboard in the blueprint
	KeyboardTransformComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("KeyboardTransformComponent"));
	KeyboardTransformComponent->AttachTo(RootComponent);
}

// Called when the game starts or when spawned
void AHackTerminal::BeginPlay()
{
	Super::BeginPlay();
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = Instigator;
	FVector KeyboardContainerLocation = FVector(0.0f, 0.0f, -1500.0f);
	FRotator KeyboardContainerRotation = FRotator(0.0f, 0.0f, 0.0f);
	FVector KeyboardContainerScale = FVector(1.0f, 1.0f, 1.0f);
	KeyboardContainer = GetWorld()->SpawnActor<AKeyboardContainer>(KeyboardContainerLocation, KeyboardContainerRotation, SpawnParams);
	
	SpawnKeys(KeyboardLetters, KeyboardContainer);

}

// Called every frame
void AHackTerminal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHackTerminal::SpawnKeys(FText letters, AActor* SpawnActor) {
	check(KeyClass != nullptr);
	FString strLetters = letters.ToString();
	FVector SpawnLocation = SpawnActor->GetTransform().GetLocation();
	FRotator SpawnRotation = SpawnActor->GetActorRotation();
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = SpawnActor;
	SpawnParams.Instigator = Instigator;

	FName keyboardTransformName;
	FRotator keyboardRotation;
	FVector keyboardLocation;
	if (KeyboardTransformComponent) {
		keyboardTransformName = FName(*(KeyboardTransformComponent->GetName()));
		keyboardRotation = KeyboardTransformComponent->GetComponentRotation();
		keyboardLocation = KeyboardTransformComponent->GetComponentLocation();
	}
	for (int i = 0; i < strLetters.Len(); i++) {
		AKeyboardKey* key = GetWorld()->SpawnActor<AKeyboardKey>(KeyClass->GetOwnerClass(), SpawnLocation, SpawnRotation, SpawnParams);

		// Convert the character to FText
		TCHAR keyChar = strLetters[i];
		FString keyString;
		keyString.AppendChar(keyChar);
		FText keyText = FText::FromString(keyString);

		// Make sure key isn't delete or clear key
		key->isDelete = false;
		key->isClear = false;

		// Set the key text
		key->CreateKey(keyText, this);
		FVector keyLocation = GetKeyLocation(i, keyboardLocation);
		key->SetActorLocationAndRotation(keyLocation, keyboardRotation);

		// Add the key to our list
		keyList.Add(key);
		// Attach key to the keyboardTransformComponent location
		key->AttachRootComponentToActor(SpawnActor, NAME_None, EAttachLocation::KeepRelativeOffset);

	}
	int deleteKeyIndex = strLetters.Len();

	// Create the delete key
	AKeyboardKey* deleteKey = GetWorld()->SpawnActor<AKeyboardKey>(KeyClass->GetOwnerClass(), SpawnLocation, SpawnRotation, SpawnParams);
	// Set the key text
	FText keyText = FText::FromString("<");
	deleteKey->CreateKey(keyText, this);
	FVector keyLocation = GetKeyLocation(deleteKeyIndex, keyboardLocation);
	deleteKey->SetActorLocationAndRotation(keyLocation, keyboardRotation);
	// Set the delete key's function
	deleteKey->isDelete = true;
	deleteKey->isClear = false;
	// Change delete key's render
	FColor deleteKeyColor = FColor(255, 0, 0, 255);
	deleteKey->TextRenderComponent->SetTextRenderColor(deleteKeyColor);
	// Attach key to key terminal
	deleteKey->AttachRootComponentToActor(SpawnActor, NAME_None, EAttachLocation::KeepRelativeOffset);
	// Add the key to our list
	keyList.Add(deleteKey);


	//// Make sure KeyboardContainer is not null!!
	//// Set this in blueprint begin play!
	check(KeyboardContainer != nullptr);
	FVector KeyboardContainerLocation = KeyboardContainer->GetActorLocation();
	FRotator KeyboardContainerRotation = KeyboardContainer->GetActorRotation();

	// All our logic for spawning the keys
	int keyListLength = keyList.Num();
	for (int i = 0; i < keyListLength; i++) {
		float hoffset = KeyH_Offset * (float)(KeysPerRow / 2);
		hoffset = hoffset - KeyH_Offset / 2;
		float hoffsetmod = KeyH_Offset * (float)(i % KeysPerRow);
		float finalhoffset = hoffset - hoffsetmod;

		float FinalY = finalhoffset + KeyboardContainerLocation.Y;
		KeyboardContainer->GetActorRotation();


		float voffset = KeyV_Offset * (float)(i / KeysPerRow);
		float finalvoffset = KeyboardContainerLocation.Z - voffset;
		FVector FinalKeyLocation = FVector(KeyboardContainerLocation.X, finalhoffset, finalvoffset);
		
		(keyList[i])->SetActorLocationAndRotation(FinalKeyLocation, KeyboardContainerRotation);
	
		/////////
		//// Cast to BP_KeyboardKey 
		//// Set keyboard key parent terminal is done in CreateKey()
	
	}

}

FVector AHackTerminal::GetKeyLocation(int index, FVector keyboardLocation) {
	int kpr = KeysPerRow;
	if (kpr <= 0)
		return FVector();
	int Row = index / kpr;
	int Column = index % kpr;

	float X_Offset = KeyH_Offset;
	float Z_Offset = KeyV_Offset;
	X_Offset = X_Offset * Column;
	Z_Offset = Z_Offset * Row;

	FVector keyLocation(keyboardLocation.X, keyboardLocation.Y, keyboardLocation.Z);
	return keyLocation;
}
