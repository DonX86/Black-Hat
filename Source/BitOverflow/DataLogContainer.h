// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DataLogContainer.generated.h"


/* Default class to store information of a message
 * Used to hold class information for the flyweight design pattern
 */
USTRUCT()
struct FDataLogStruct
{
	GENERATED_USTRUCT_BODY()

	FText LogTitle;
	FText LogSubTitle;
	FText LogBody;
	FText LogNote;
};

class ADataLogEntry;

/* This object displays the data that the player has collected so far
 * This should be attached to the player's skeletal mesh
 */
UCLASS()
class BITOVERFLOW_API ADataLogContainer : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ADataLogContainer();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	/** The data log entry class to spawn */
	UPROPERTY(EditAnywhere, Category = DataLog)
		const UClass* DataLogEntryClass;

	/** Maximum number of data log entries */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataLog)
		int32 MaxRows;

	/** the vertical offset of each entry */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DataLog)
		float EntryVerticalOffset;

	/** The current data log entry index */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DataLog)
		int32 CurrentIndex;


	/** Array to store our data log entries */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DataLog)
		TArray<ADataLogEntry*>  DataLogEntryArray;

	/** Array to store our data log messages */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DataLog)
		TArray<FDataLogStruct> DataLogArray;

	/** Simple collision primitive to use as the root component, collision of the object */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = DataLog)
		UBoxComponent* BaseCollisionComponent;

	/** StaticMeshComponent to represent the object in the level */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = DataLog)
		UStaticMeshComponent* StaticMesh;

	/** A text render to display our information */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = DataLog)
		UTextRenderComponent* TextRenderComponent;

	/** A text render to display new data log entry notification */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = DataLog)
		UTextRenderComponent* NotifyNewEntryTextRenderComponent;

	//////////////////////////////////
	// Data Log Functions
	//////////////////////////////////

	UFUNCTION(BlueprintCallable, Category = DataLog)
		void InstantiateEntries();

	UFUNCTION(BlueprintCallable, Category = DataLog)
		void AddDataLogStruct(FText title, FText subTitle, FText body, FText note);

	UFUNCTION(BlueprintCallable, Category = DataLog)
		void GetDataLogInfo(const int32 &index, FText& title, FText& subTitle, FText& body, FText& note);

	/** Close the container and turn off display of the entries */
	UFUNCTION(BlueprintCallable, Category = DataLog)
		void CloseContainer();

	UFUNCTION(BlueprintCallable, Category = DataLog)
		void OpenContainer();
	
	/** move the data log entries up to show the most recent one */
	UFUNCTION(BlueprintCallable, Category = DataLog)
		void MoveLogsUp();

	/** move the data log entries up to show the most recent one */
	UFUNCTION(BlueprintCallable, Category = DataLog)
		void AddDataLog(FText title, FText subtitle, FText body, FText note);

	/** notify the player that there is a new data log entry */
	UFUNCTION(BlueprintCallable, Category = DataLog)
		void NotifyNewEntry();

private:
	bool AtBottomOfList;
};
