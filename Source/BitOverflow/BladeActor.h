// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "BladeActor.generated.h"

class AProjectile;

UCLASS()
class BITOVERFLOW_API ABladeActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABladeActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

public:

	/** The pickup to spawn */
	UPROPERTY(EditAnywhere, Category = Blade)
		const UClass* Projectile;

	// Right Socket to hold the blade
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Blade)
		FString RightSocketName;

	// If blade is in the player's arm
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Blade)
		bool isUnsheathed;

	// If the blade is ready to be unsheathed
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Blade)
		bool isReady;

	// Cooldown between blade launches reset to ready
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Blade)
		float MaxCooldownTime;

	// Maximum launch velocity of blade
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Blade)
		float launchSpeed;

	// Direction the blade launches
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Blade)
		FVector launchDirection;

	// Pulls out the blade from the player
	UFUNCTION(BlueprintCallable, Category = Blade)
		virtual void UnsheathBlade();

	// Launches the blade from the arm
	UFUNCTION(BlueprintCallable, Category = Blade)
		virtual void LaunchBlade();

private:

	// PlayerPawn
	APawn* PlayerPawn;

	// Player's character
	ACharacter* PlayerCharacter;

	// Player's skeletal mesh
	USkeletalMeshComponent* PlayerMesh;

	// Sheathed projectile that was spawned
	AProjectile* SpawnedProjectile;

	// The starting scale of the blade
	FVector StartScale;

	// The ending scale of the blade
	FVector EndScale;

	// Check for a valid world:
	UWorld* World;

	float CurCooldownTime;

	// Left Socket to hold the blade
	FName SocketName;
};
