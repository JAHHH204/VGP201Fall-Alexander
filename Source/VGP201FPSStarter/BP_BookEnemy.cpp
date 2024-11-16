#include "BP_BookEnemy.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"

// Sets default values
ABP_BookEnemy::ABP_BookEnemy()
{
	// Set this character to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set the enemy's speed (can be adjusted in the editor)
	MoveSpeed = 200.0f; // Set a default move speed
	Range = 300.0f;  // Set a default wandering range
}

// Called when the game starts or when spawned
void ABP_BookEnemy::BeginPlay()
{
	Super::BeginPlay();

	// Initially set the target location to a random spot
	SetNewTargetLocation();
}

// Called every frame
void ABP_BookEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// If the enemy has reached the target, choose a new one
	if (FVector::Dist(GetActorLocation(), TargetLocation) < Range)
	{
		SetNewTargetLocation();
	}

	// Move towards the target location
	FVector Direction = (TargetLocation - GetActorLocation()).GetSafeNormal();
	AddMovementInput(Direction, 1.0f); // Move towards the target with full speed
}

// Function to choose a new random target location
void ABP_BookEnemy::SetNewTargetLocation()
{
	// Choose a random location within a certain radius
	FVector CurrentLocation = GetActorLocation();
	float RandomX = FMath::RandRange(-Range, Range);
	float RandomY = FMath::RandRange(-Range, Range);
	TargetLocation = CurrentLocation + FVector(RandomX, RandomY, 0.0f); // Keep the enemy on the same Z level
}
