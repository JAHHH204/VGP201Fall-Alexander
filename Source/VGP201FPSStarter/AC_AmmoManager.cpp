#include "AC_AmmoManager.h"

// Sets default values for this component's properties
UAC_AmmoManager::UAC_AmmoManager()
{
	// Set this component to be initialized when the game starts, and to tick every frame if needed
	PrimaryComponentTick.bCanEverTick = true;

	// Initialize ammo variables
	MaxAmmo = 100;  // Set your default max ammo
	CurrentAmmo = MaxAmmo;  // Start with full ammo
}

// Called when the game starts
void UAC_AmmoManager::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UAC_AmmoManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

// Refill ammo by a certain amount
void UAC_AmmoManager::RefillAmmo(int32 Amount)
{
	// Add ammo and clamp it to not exceed MaxAmmo
	CurrentAmmo = FMath::Clamp(CurrentAmmo + Amount, 0, MaxAmmo);
	UE_LOG(LogTemp, Warning, TEXT("Refilled ammo by %d. Current ammo: %d"), Amount, CurrentAmmo);
}

// Decrease ammo by a certain amount
void UAC_AmmoManager::DecreaseAmmo(int32 Amount)
{
	// Decrease ammo and clamp it to not go below 0
	CurrentAmmo = FMath::Clamp(CurrentAmmo - Amount, 0, MaxAmmo);
	UE_LOG(LogTemp, Warning, TEXT("Decreased ammo by %d. Current ammo: %d"), Amount, CurrentAmmo);
}

// Check if the player has any ammo left
bool UAC_AmmoManager::HasAmmo() const
{
	return CurrentAmmo > 0;
}
