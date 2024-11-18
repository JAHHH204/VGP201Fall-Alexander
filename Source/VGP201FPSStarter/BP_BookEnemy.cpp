#include "BP_BookEnemy.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Components/CapsuleComponent.h"
#include "BP_Projectile.h"
#include "AC_EnemyHealth.h"  // Include the health component
#include "AC_PlayerHealth.h"

// Sets default values
ABP_BookEnemy::ABP_BookEnemy()
{
    // Set this character to call Tick() every frame.
    PrimaryActorTick.bCanEverTick = true;

    // Initialize movement speed and detection range
    MoveSpeed = 300.0f; // Default movement speed
    DetectionRange = 1000.0f; // Default detection range

    // Configure the CharacterMovementComponent
    GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;

    // Initialize variables
    CurrentWaypoint = nullptr;
    CurrentState = EEnemyState::Idle;

    GetCapsuleComponent()->SetGenerateOverlapEvents(true);

    // Create and initialize health component
    EnemyHealthComponent = CreateDefaultSubobject<UAC_EnemyHealth>(TEXT("EnemyHealth"));
}

// Called when the game starts or when spawned
void ABP_BookEnemy::BeginPlay()
{
    Super::BeginPlay();

    // Find and store a reference to the player character
    PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

    UCapsuleComponent* LocalCapsuleComponent = GetCapsuleComponent();
    if (LocalCapsuleComponent)
    {
        LocalCapsuleComponent->OnComponentHit.AddDynamic(this, &ABP_BookEnemy::OnProjectileHit);
    }
}

// Called every frame
void ABP_BookEnemy::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Execute tracking or patrol behavior
    TrackPlayer();
}

// Called to bind functionality to input
void ABP_BookEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

// Function to check line of sight to the player
bool ABP_BookEnemy::HasLineOfSightToPlayer()
{
    if (!PlayerCharacter)
        return false;

    FHitResult HitResult;
    FVector Start = GetActorLocation();
    FVector End = PlayerCharacter->GetActorLocation();

    // Perform a line trace (raycast)
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(this); // Ignore the enemy itself
    QueryParams.AddIgnoredActor(PlayerCharacter); // Ignore the player for collision checks

    bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, QueryParams);

    // Optional: Visualize the trace during debugging
    DrawDebugLine(GetWorld(), Start, End, bHit ? FColor::Red : FColor::Green, false, 0.1f);

    // If the trace doesn't hit anything or hits the player, we have line of sight
    return !bHit || HitResult.GetActor() == PlayerCharacter;
}

// Function to patrol between waypoints
void ABP_BookEnemy::Patrol()
{
    if (PatrolWaypoints.Num() > 0)
    {
        if (!CurrentWaypoint || FVector::Dist(GetActorLocation(), CurrentWaypoint->GetActorLocation()) < 100.0f)
        {
            // Choose the next waypoint
            int32 NextIndex = FMath::RandRange(0, PatrolWaypoints.Num() - 1);
            CurrentWaypoint = PatrolWaypoints[NextIndex];
        }

        if (CurrentWaypoint)
        {
            FVector Direction = (CurrentWaypoint->GetActorLocation() - GetActorLocation()).GetSafeNormal();
            AddMovementInput(Direction, 0.5f); // Move slower when patrolling
        }
    }
    else
    {
        CurrentState = EEnemyState::Idle; // No waypoints, set state to idle
    }
}

// Function to track and move toward the player
// Function to track and move toward the player
void ABP_BookEnemy::TrackPlayer()
{
    if (!PlayerCharacter)
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerCharacter reference is null!"));
        return;
    }

    // Calculate the distance to the player
    float DistanceToPlayer = FVector::Dist(GetActorLocation(), PlayerCharacter->GetActorLocation());

    // Check if the player is within detection range and line of sight
    if (DistanceToPlayer <= DetectionRange && HasLineOfSightToPlayer())
    {
        FVector Direction = (PlayerCharacter->GetActorLocation() - GetActorLocation()).GetSafeNormal();
        AddMovementInput(Direction, 1.0f); // Move towards the player

        // Check if the player is within attack range
        if (DistanceToPlayer <= AttackRange && !IsAttacking)
        {
            AttackPlayer(); // Call the function to attack
        }

        CurrentState = EEnemyState::Tracking; // Update animation state
    }
    else
    {
        Patrol(); // Patrol when the player is out of range
        CurrentState = EEnemyState::Patrolling; // Update animation state
    }
}


// Function to handle projectile hits
void ABP_BookEnemy::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if (OtherActor && OtherActor->IsA(ABP_Projectile::StaticClass()))
    {
        // Handle the projectile hit: Apply damage
        UE_LOG(LogTemp, Warning, TEXT("Enemy hit by a projectile!"));

        if (EnemyHealthComponent)
        {
            EnemyHealthComponent->TakeDamage(10.0f);  // Reduce health by 10 (or any other value)
        }
    }
}

void ABP_BookEnemy::OnDeath()
{
    // Handle death logic here (e.g., play animation, disable movement, etc.)
    UE_LOG(LogTemp, Warning, TEXT("Enemy is dead!"));

    // Optionally, you can disable the enemy actor or play a death animation
    SetActorHiddenInGame(true); // Hide the enemy
    SetActorEnableCollision(false); // Disable collision
    // Or, you could destroy the enemy if it's dead
    // Destroy();
}

// Function to attack the player
void ABP_BookEnemy::AttackPlayer()
{
    // Prevent multiple attacks in a short time frame (add cooldown if needed)
    if (GetWorld()->GetTimerManager().IsTimerActive(AttackTimerHandle))
    {
        return; // Don't attack again if the cooldown is still active
    }

    // Start the attack (animation, etc.)
    IsAttacking = true;

    // Deal damage to the player (ensure the player has a health component)
    if (PlayerCharacter)
    {
        UAC_PlayerHealth* PlayerHealth = Cast<UAC_PlayerHealth>(PlayerCharacter->GetComponentByClass(UAC_PlayerHealth::StaticClass()));
        if (PlayerHealth)
        {
            PlayerHealth->TakeDamage(AttackDamage); // Apply damage to the player
            UE_LOG(LogTemp, Warning, TEXT("Enemy attacked the player! Damage: %f"), AttackDamage);
        }
    }

    // Set cooldown for attack (e.g., 1 second before the enemy can attack again)
    GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, this, &ABP_BookEnemy::ResetAttack, 1.0f, false); // 1 second cooldown
}

// Function to reset the attack state after cooldown
void ABP_BookEnemy::ResetAttack()
{
    IsAttacking = false;
}
