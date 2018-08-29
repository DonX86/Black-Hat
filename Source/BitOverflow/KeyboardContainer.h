// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "KeyboardContainer.generated.h"

UCLASS()
class BITOVERFLOW_API AKeyboardContainer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKeyboardContainer();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	/** Simple collision primitive to use as the root component, collision of the object */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Terminal)
		UBoxComponent* BaseCollisionComponent;

	/** StaticMeshComponent to represent the object in the level */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Terminal)
		UStaticMeshComponent* StaticMesh;
	
};
