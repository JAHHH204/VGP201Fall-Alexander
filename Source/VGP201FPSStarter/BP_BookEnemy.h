#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AC_EnemyHealth.h" // Include the health component
#include "BP_BookEnemy.generated.h"

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

    // Reference to the player character
    ACharacter* PlayerCharacter;

    // Enemy health component
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
    UAC_EnemyHealth* EnemyHealthComponent;

    // Movement and detection
    float MoveSpeed;
    float DetectionRange;

    // Patrol and tracking behavior
    TArray<AActor*> PatrolWaypoints;
    AActor* CurrentWaypoint;
    enum class EEnemyState { Idle, Patrolling, Tracking };
    EEnemyState CurrentState;

    // Functions for movement and behavior
    void TrackPlayer();
    void Patrol();
    bool HasLineOfSightToPlayer();

    // Function to handle projectile hits
    UFUNCTION()
    void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

    UFUNCTION(BlueprintCallable, Category = "Enemy")
    void OnDeath();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
    float AttackRange = 200.0f; // The range at which the enemy can attack

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
    float AttackDamage = 25.0f; // Damage dealt by the enemy when attacking

    // Timer to prevent rapid attacks
    FTimerHandle AttackTimerHandle;

    void AttackPlayer();
    void ResetAttack();

    UPROPERTY(EditAnywhere, Category = "Attack")
    bool IsAttacking;
};
