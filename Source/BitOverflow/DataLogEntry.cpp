// Fill out your copyright notice in the Description page of Project Settings.

#include "BitOverflow.h"
#include "DataLogEntry.h"
#include "DataLogContainer.h"
#include "Kismet/KismetTextLibrary.h"

// Sets default values
ADataLogEntry::ADataLogEntry()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create our root component
	BaseCollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BaseCollisionComponent"));
	RootComponent = BaseCollisionComponent;

	// Create our title
	TitleTextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TitleTextRenderComponent"));
	TitleTextRenderComponent->AttachTo(RootComponent);

	// Create our selection component
	SelectionColliderComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("SelectionColliderComponent"));
	SelectionColliderComponent->AttachTo(TitleTextRenderComponent);

	// Create our index
	IndexTextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("IndexTextRenderComponent"));
	IndexTextRenderComponent->AttachTo(RootComponent);

}

// Called when the game starts or when spawned
void ADataLogEntry::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADataLogEntry::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ADataLogEntry::Initialize(FText title, FText subtitle, FText body, FText note, int32 i) {
	TitleText = title;
	SubTitleText = subtitle;
	BodyText = body;
	NoteText = note;
	Index = i;

	TitleTextRenderComponent->SetText(TitleText);

	if (Index < 0) {
		IndexTextRenderComponent->SetText(FText::GetEmpty());
	}
	else {
		IndexTextRenderComponent->SetText(UKismetTextLibrary::Conv_IntToText(i));
	}
}

void ADataLogEntry::InitializeEmpty(int32 ei, ADataLogContainer* parent) {
	check(ei >= 0 && parent != nullptr)
		FString message = " entry index: " + FString::FromInt(ei) + " parent: " + parent->GetName();
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, message);
	EntryIndex = ei;
	ParentContainer = parent;
	FText empty = FText::GetEmpty();
	Initialize(empty, empty, empty, empty, -1);
}


void ADataLogEntry::GetDataLogInfo(FText& title, FText& subTitle, FText& body, FText& note, int32 &index) {
	title = TitleText;
	subTitle = SubTitleText;
	body = BodyText;
	note = NoteText;
	index = Index;
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "From title: " + TitleText.ToString() + " to title: " + title.ToString());

}

void ADataLogEntry::ShowText() {
	TitleTextRenderComponent->SetVisibility(true);
	IndexTextRenderComponent->SetVisibility(true);
}

void ADataLogEntry::HideText() {
	TitleTextRenderComponent->SetVisibility(false);
	IndexTextRenderComponent->SetVisibility(false);
}