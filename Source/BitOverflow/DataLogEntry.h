// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DataLogEntry.generated.h"

class ADataLogContainer;

UCLASS()
class BITOVERFLOW_API ADataLogEntry : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADataLogEntry();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	/** Index of this entry in DataLogContainer's DataLogEntryArray */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataLog)
		int32 EntryIndex;

	/** A refernce to this entry's parent container */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataLog)
		ADataLogContainer* ParentContainer;

	/** Simple collision primitive to use as the root component, collision of the object */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = DataLog)
		UBoxComponent* BaseCollisionComponent;

	/** Simple collision for selecting entry */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = DataLog)
		UBoxComponent* SelectionColliderComponent;

	/** A text render to display our title */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = DataLog)
		UTextRenderComponent* TitleTextRenderComponent;

	/** A text render to display our index */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = DataLog)
		UTextRenderComponent* IndexTextRenderComponent;

	////////////////////////////////////////////////////////////////////////////////
	/// FUNCTIONS
	////////////////////////////////////////////////////////////////////////////////

	/* Initialize the entry by setting all the text and index
	 * If the entry is empty, set the index to be -1
	 */
	UFUNCTION(BlueprintCallable, Category = DataLog)
		void Initialize(FText title, FText subtitle, FText body, FText note, int32 i = -1);

	/** Initialize an empty entry */
	UFUNCTION(BlueprintCallable, Category = DataLog)
		void InitializeEmpty(int32 ei, ADataLogContainer* parent);

	UFUNCTION(BlueprintCallable, Category = DataLog)
		void GetDataLogInfo(FText& title, FText& subTitle, FText& body, FText& note, int32 &index);

	UFUNCTION(BlueprintCallable, Category = DataLog)
		void ShowText();

	UFUNCTION(BlueprintCallable, Category = DataLog)
		void HideText();

private:
	FText TitleText;
	FText SubTitleText;
	FText BodyText;
	FText NoteText;
	int32 Index;
};
