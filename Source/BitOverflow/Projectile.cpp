// Fill out your copyright notice in the Description page of Project Settings.

#include "BitOverflow.h"
#include "Projectile.h"


// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Initialize isLaunched to be false
	isLaunched = false;

	//Create the static mesh component
	staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	RootComponent = staticMesh;

	//Create the root SphereComponent to handle the pickup's collision
	boxCollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("boxCollisionComponent"));
	boxCollisionComponent->AttachTo(RootComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (isLaunched) {
		timeDestroy -= DeltaTime;
		if (timeDestroy <= 0)
			Destroy();
	}
}

// Set isLaunched to be true so that we remember to destroy the projectile
void AProjectile::Launch(FVector direction, float speed) {
	isLaunched = true;
	timeLaunched = GetWorld()->GetTimeSeconds();
	timeDestroy = timeToLive;

	// Set launch variables
	launchDirection = direction;
	launchSpeed = speed;

	// Launch the projectile in BluePrints
	check(staticMesh != nullptr);
	staticMesh->SetSimulatePhysics(true);
	staticMesh->AddImpulse(direction * speed);

}
