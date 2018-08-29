// Fill out your copyright notice in the Description page of Project Settings.

#include "BitOverflow.h"
#include "BladeActor.h"
#include "Projectile.h"

// Sets default values
ABladeActor::ABladeActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//PlayerSkeletalMesh = PlayerPawn->GetComponentByClass<USkeletalMesh>();
	//Socket = GetPawnSkeletalComp(SocketName);
	isReady = true;
	isUnsheathed = false;
}

// Called when the game starts or when spawned
void ABladeActor::BeginPlay()
{
	Super::BeginPlay();

	World = GetWorld();

	PlayerPawn = UGameplayStatics::GetPlayerPawn(World, 0);
	PlayerCharacter = UGameplayStatics::GetPlayerCharacter(World, 0);

	PlayerMesh = PlayerCharacter->GetMesh();

	// Set the correct sockets to spawn the projectiles
	SocketName = FName(*(RightSocketName));

}

// Called every frame
void ABladeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!isReady) {
		CurCooldownTime -= DeltaTime;
		if (CurCooldownTime <= 0) {
			// Set is ready
			isReady = true;
		}
	}

}

void ABladeActor::UnsheathBlade() {
	//World = GetWorld();
	// If Projectile is set and world
	if (Projectile && PlayerMesh && World)
		// If projectile is ready and not already unsheathed (the variable should be null)
		if (isReady && !isUnsheathed && !SpawnedProjectile) {
			// Set is unsheathed to true
			isUnsheathed = true;

			// Set Projectile location, rotation and parameters
			FVector SpawnLocation = this->GetTransform().GetLocation();
			FRotator SpawnRotation = this->GetActorRotation();
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;

			// Spawn the projectile
			SpawnedProjectile = World->SpawnActor<AProjectile>(Projectile->GetOwnerClass(), SpawnLocation, SpawnRotation, SpawnParams);

			// Attach projectile to socket
			// SpawnedProjectile
			check(PlayerMesh != nullptr);
			SpawnedProjectile->AttachRootComponentTo(PlayerMesh, SocketName, EAttachLocation::SnapToTarget);

		}
}

void ABladeActor::LaunchBlade() {
	// DEBUGGING RETURN
	//return;
	if (isReady && isUnsheathed && SpawnedProjectile) {
		// Blade is now unsheathed and not ready
		isReady = false;
		isUnsheathed = false;

		// Set the cooldown time
		CurCooldownTime = MaxCooldownTime;

		// Get direction of socket
		FVector SocketDirection = (PlayerMesh->GetSocketRotation(SocketName).Vector());

		// Launch the projectile by detaching it from our socket
		SpawnedProjectile->DetachRootComponentFromParent();

		// Set the projectile to launch
		SpawnedProjectile->Launch(SocketDirection, launchSpeed);

		SpawnedProjectile = NULL;
	}
}