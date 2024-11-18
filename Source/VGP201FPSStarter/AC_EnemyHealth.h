#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AC_EnemyHealth.generated.h"

// Forward declaration for the enemy actor class
class ABP_BookEnemy;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class VGP201FPSSTARTER_API UAC_EnemyHealth : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UAC_EnemyHealth();

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    // Health properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
    float MaxHealth;

    UPROPERTY(BlueprintReadOnly, Category = "Health")
    float CurrentHealth;

    // Function to handle damage
    void TakeDamage(float DamageAmount);

    // Check if the enemy is alive
    bool IsAlive() const;

private:
    ABP_BookEnemy* OwnerEnemy; // Reference to the enemy owner of this health component
};
