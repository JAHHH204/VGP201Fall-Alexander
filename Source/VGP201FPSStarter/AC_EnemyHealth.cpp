#include "AC_EnemyHealth.h"
#include "BP_BookEnemy.h"  // Include the header of your enemy class to get access to it

// Sets default values for this component's properties
UAC_EnemyHealth::UAC_EnemyHealth()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame
    PrimaryComponentTick.bCanEverTick = false;  // Health doesn't need to be updated every frame

    MaxHealth = 100.0f;  // Default maximum health value
    CurrentHealth = MaxHealth;
}

// Called when the game starts
void UAC_EnemyHealth::BeginPlay()
{
    Super::BeginPlay();

    // Get the owner of this component, which should be the enemy character
    OwnerEnemy = Cast<ABP_BookEnemy>(GetOwner());
}

// Called every frame
void UAC_EnemyHealth::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // Update logic related to health can be placed here if needed
}

// Take damage function
void UAC_EnemyHealth::TakeDamage(float DamageAmount)
{
    if (DamageAmount <= 0.0f || !IsAlive()) return;

    // Reduce the current health by the damage amount
    CurrentHealth -= DamageAmount;

    // Ensure health doesn't go below zero
    if (CurrentHealth < 0.0f)
    {
        CurrentHealth = 0.0f;
    }

    // If health reaches zero, handle death
    if (!IsAlive())
    {
        // Handle enemy death, for example, triggering animations or notifying the game manager
        if (OwnerEnemy)
        {
            OwnerEnemy->OnDeath();  // Example: Call the death function in the enemy class (you need to implement this)
        }
    }
}

// Check if the enemy is alive
bool UAC_EnemyHealth::IsAlive() const
{
    return CurrentHealth > 0.0f;
}
