// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "KeyboardKey.generated.h"

class AHackTerminal;

UCLASS()
class BITOVERFLOW_API AKeyboardKey : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AKeyboardKey();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	/** A reference to the parent terminal */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Terminal)
		AHackTerminal* ParentTerminal;

	// is this key for backspace/delete?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Terminal)
		bool isDelete;

	// is this key for clearing the entire input	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Terminal)
		bool isClear;

	// Letter for this key	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = Terminal)
		FText Letter;

	/** Simple collision primitive to use as the root component, collision of the object */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Terminal)
		UBoxComponent* BaseCollisionComponent;

	/** StaticMeshComponent to represent the terminal in the level */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Terminal)
		UStaticMeshComponent* KeyMesh;

	/** Text component to show our letter/key */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Terminal)
		UTextRenderComponent* TextRenderComponent;

	/** Called to create this key */
	UFUNCTION(BlueprintCallable, Category = Terminal)
		void CreateKey(FText key, AHackTerminal* parent);
};

