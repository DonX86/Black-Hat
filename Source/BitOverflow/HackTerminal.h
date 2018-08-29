// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "HackTerminal.generated.h"

class ATextRenderActor;
class AKeyboardKey;
class AKeyboardContainer;

UCLASS()
class BITOVERFLOW_API AHackTerminal : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHackTerminal();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	/** Text the player must type in to gain access */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Terminal)
		FText AnswerText;

	/** Letters to be used for the keyboard */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Terminal)
		FText KeyboardLetters;

	/** Keys to be shown per row */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Terminal)
		int32 KeysPerRow;

	/** Horizontal offset of keys */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Terminal)
		float KeyH_Offset;

	/** Vertical offset of keys */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Terminal)
		float KeyV_Offset;

	/** Array to store our key objects */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Terminal)
		TArray<AKeyboardKey*> keyList;

	/** The key type to spawn */
	UPROPERTY(EditAnywhere, Category = Terminal)
		const UClass* KeyClass;

	/** Simple collision primitive to use as the root component, collision of the object */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Terminal)
		UBoxComponent* BaseCollisionComponent;

	/** Simple collision to define the user interaction zone */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Terminal)
		UCapsuleComponent* InteractCollisionComponent;

	/** StaticMeshComponent to represent the terminal in the level */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Terminal)
		UStaticMeshComponent* TerminalMesh;

	/** A text render to display our information */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Terminal)
		UTextRenderComponent* TextRenderComponent;

	/** Subtext for auxilary info, like "Access Denied" */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Terminal)
		UTextRenderComponent* SubTextComponent;

	/** Location where the keyboard spawns */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Terminal)
		UBoxComponent* KeyboardTransformComponent;

	/** The keyboard container actor where we spawn the keys */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Terminal)
		AKeyboardContainer* KeyboardContainer;

	/** Spawn the keys with the letters */
	UFUNCTION(BlueprintCallable, Category = Terminal)
		void SpawnKeys(FText letters, AActor* SpawnActor);

private:
	/** Given the index of a character, returns the location of where the key should be */
	FVector GetKeyLocation(int index, FVector keyboardLocation);
};
