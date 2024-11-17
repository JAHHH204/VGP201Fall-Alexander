#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BP_BookEnemy.generated.h"

// Enum to define enemy states
UENUM(BlueprintType)
enum class EEnemyState : uint8
{
    Idle,
    Patrolling,
    Tracking
};

UCLASS()
class VGP201FPSSTARTER_API ABP_BookEnemy : public ACharacter
{
    GENERATED_BODY()

public:
    // Sets default values for this character's properties
    ABP_BookEnemy();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    // Speed at which the enemy moves
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float MoveSpeed = 300.0f;

    // Detection range for tracking the player
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tracking")
    float DetectionRange = 1000.0f;

    // Patrol waypoints for the enemy
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol")
    TArray<AActor*> PatrolWaypoints;

private:
    // Reference to the player character
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tracking", meta = (AllowPrivateAccess = "true"))
    ACharacter* PlayerCharacter;

    // Current waypoint being targeted
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Patrol", meta = (AllowPrivateAccess = "true"))
    AActor* CurrentWaypoint;

    // Current state of the enemy
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = "true"))
    EEnemyState CurrentState = EEnemyState::Idle;

    // Function to track and move toward the player
    void TrackPlayer();

    // Function to patrol between waypoints
    void Patrol();

    // Check if the enemy has a clear line of sight to the player
    bool HasLineOfSightToPlayer();
};
