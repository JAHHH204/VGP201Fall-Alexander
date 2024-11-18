#include "AC_PlayerHealth.h"

// Sets default values for this component's properties
UAC_PlayerHealth::UAC_PlayerHealth()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame. You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	CurrentHealth = MaxHealth;
}

// Called when the game starts
void UAC_PlayerHealth::BeginPlay()
{
	Super::BeginPlay();

	// Initialize any other necessary things when the game starts, such as setting health to max
}

// Called every frame
void UAC_PlayerHealth::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Optionally, check if health is zero or update health-related logic
}

// Method to handle taking damage
void UAC_PlayerHealth::TakeDamage(float DamageAmount)
{
	CurrentHealth -= DamageAmount;

	if (CurrentHealth <= 0.0f)
	{
		// Handle player death (e.g., play death animation, trigger respawn, etc.)
		UE_LOG(LogTemp, Warning, TEXT("Player has died!"));
	}
}

// Method to check if the player is dead
bool UAC_PlayerHealth::IsDead() const
{
	return CurrentHealth <= 0.0f;
}
