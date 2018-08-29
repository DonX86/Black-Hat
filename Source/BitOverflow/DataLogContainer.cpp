// Fill out your copyright notice in the Description page of Project Settings.

#include "BitOverflow.h"
#include "DataLogContainer.h"
#include "DataLogEntry.h"


// Sets default values
ADataLogContainer::ADataLogContainer()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create our root component
	BaseCollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BaseCollisionComponent"));
	RootComponent = BaseCollisionComponent;

	// Create the static mesh component and attach the StaticMeshComponent to the root component
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->AttachTo(RootComponent);

	// Create our text render to display info to player
	TextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRenderComponent"));
	TextRenderComponent->AttachTo(RootComponent);

	// Create our text render to notify the player about new entries
	NotifyNewEntryTextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("NotifyNewEntryTextRenderComponent"));
	NotifyNewEntryTextRenderComponent->AttachTo(RootComponent);

	CurrentIndex = -1;

}

// Called when the game starts or when spawned
void ADataLogContainer::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ADataLogContainer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADataLogContainer::AddDataLogStruct(FText title, FText subTitle, FText body, FText note) {
	FDataLogStruct DLS;
	DLS.LogTitle = title;
	DLS.LogSubTitle = subTitle;
	DLS.LogBody = body;
	DLS.LogNote = note;

	DataLogArray.Add(DLS);
}

void ADataLogContainer::GetDataLogInfo(const int32 &index, FText& title, FText& subTitle, FText& body, FText& note) {
	FDataLogStruct* DLS = &(DataLogArray[index]);
	title = DLS->LogTitle;
	subTitle = DLS->LogSubTitle;
	body = DLS->LogBody;
	note = DLS->LogNote;
}

void ADataLogContainer::InstantiateEntries() {
	FRotator BaseRotation = BaseCollisionComponent->GetComponentRotation();
	FVector BaseLocation = BaseCollisionComponent->GetComponentLocation();
	FTransform BaseTransform = this->GetTransform();
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = Instigator;	
	
	for (int i = 0; i < MaxRows; i++) {
		ADataLogEntry* NewEntry = GetWorld()->SpawnActor<ADataLogEntry>(DataLogEntryClass->GetOwnerClass(), BaseTransform, SpawnParams);

		float voffset = (i - 2) * EntryVerticalOffset;
		FVector EntryLocation = FVector(BaseLocation.X, BaseLocation.Y, BaseLocation.Z + voffset);

		NewEntry->AttachRootComponentTo(BaseCollisionComponent, NAME_None, EAttachLocation::SnapToTarget);
		NewEntry->SetActorLocationAndRotation(EntryLocation, BaseRotation);
		NewEntry->InitializeEmpty(i,this);
		DataLogEntryArray.Add(NewEntry);
	}
}

void ADataLogContainer::CloseContainer() {
	TextRenderComponent->SetVisibility(true);
	int DataLogEntryArraySize = DataLogEntryArray.Num();
	for (int i = 0; i < DataLogEntryArraySize; i++) {
		DataLogEntryArray[i]->HideText();
	}
}

void ADataLogContainer::OpenContainer() {
	TextRenderComponent->SetVisibility(false);
	NotifyNewEntryTextRenderComponent->SetVisibility(false);
	int DataLogEntryArraySize = DataLogEntryArray.Num();
	for (int i = 0; i < DataLogEntryArraySize; i++) {
		DataLogEntryArray[i]->ShowText();
	}
}

void ADataLogContainer::MoveLogsUp() {
	int lastIndex = DataLogArray.Num() - 1;
	if (CurrentIndex >= lastIndex || DataLogArray.Num() <= 0) {
		return;
	}
	check(lastIndex >= 0 && MaxRows > 0);
	FText fromTitle;
	FText fromSubTitle;
	FText fromBody;
	FText fromNote;
	int32 fromIndex;
	FString message = "Array count: " + FString::FromInt(DataLogArray.Num()) + " EntryArray count: " + FString::FromInt(DataLogEntryArray.Num())
		+ " CurrentIndex: " + FString::FromInt(CurrentIndex);
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Moving Logs up: " + message);

	// for each entry except the last one, swap them
	for (int i = 0; i < MaxRows - 1; i++) {
		DataLogEntryArray[MaxRows - 2 - i]->GetDataLogInfo(fromTitle,fromSubTitle, fromBody, fromNote, fromIndex);
		//FString infomsg = "t: " + fromTitle.ToString() + " s: " + fromSubTitle.ToString() + " b: " + fromBody.ToString();
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "Moving: " + FString::FromInt(MaxRows - 2 - i) + " to " + FString::FromInt(MaxRows-1-i) + " txt: " + infomsg);
		DataLogEntryArray[MaxRows - 1 - i]->Initialize(fromTitle, fromSubTitle, fromBody, fromNote, fromIndex);
	}
	// initialize the last one
	GetDataLogInfo(lastIndex, fromTitle, fromSubTitle, fromBody, fromNote);
	DataLogEntryArray[0]->Initialize(fromTitle, fromSubTitle, fromBody, fromNote, lastIndex);

	CurrentIndex++;
}

void ADataLogContainer::AddDataLog(FText title, FText subtitle, FText body, FText note) {
	if (DataLogArray.Num() - 1 == CurrentIndex)
		AtBottomOfList = true;
	else
		AtBottomOfList = false;
	AddDataLogStruct(title, subtitle, body, note);
	if (DataLogArray.Num() < MaxRows || AtBottomOfList) {
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "debug msg");
		MoveLogsUp();
	}
	NotifyNewEntry();
}

void ADataLogContainer::NotifyNewEntry() {
	NotifyNewEntryTextRenderComponent->SetVisibility(true);
}
