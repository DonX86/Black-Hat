// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class BITOVERFLOW_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AProjectile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Extra Collider
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = Blade)
		UBoxComponent* boxCollisionComponent;

	// Static mesh of the projectile
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = Blade)
		UStaticMeshComponent* staticMesh;

	// The time a projectile can live if it never hits an object
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Blade)
		float timeToLive;

	// Set the projectile to be launched so that we remember to destroy it
	UFUNCTION(BlueprintCallable, Category = Blade)
		void Launch(FVector direction, float speed);

private:

	// Is the projectile launched
	bool isLaunched;

	// Time at the start of launch 
	float timeLaunched;

	// Time at the which projectile will be destroyed
	float timeDestroy;

	FVector launchDirection;

	float launchSpeed;

};
