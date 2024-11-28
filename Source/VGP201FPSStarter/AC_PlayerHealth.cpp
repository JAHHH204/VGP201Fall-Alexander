#include "AC_PlayerHealth.h"

// Sets default values for this component's properties
UAC_PlayerHealth::UAC_PlayerHealth()
{

	PrimaryComponentTick.bCanEverTick = true;
	CurrentHealth = MaxHealth;
}

// Called when the game starts
void UAC_PlayerHealth::BeginPlay()
{
	Super::BeginPlay();


}

// Called every frame
void UAC_PlayerHealth::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}

// Method to handle taking damage
void UAC_PlayerHealth::TakeDamage(float DamageAmount)
{
	CurrentHealth -= DamageAmount;

	if (CurrentHealth <= 0.0f)
	{
		// Handle player death ( play death animation, trigger respawn, etc.)
		UE_LOG(LogTemp, Warning, TEXT("Player has died!"));
	}
}

// Method to check if the player is dead
bool UAC_PlayerHealth::IsDead() const
{
	return CurrentHealth <= 0.0f;
}
