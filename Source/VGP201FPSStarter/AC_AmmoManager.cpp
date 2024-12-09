#include "AC_AmmoManager.h"
#include "BP_HUDWidget.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
UAC_AmmoManager::UAC_AmmoManager()
{
	PrimaryComponentTick.bCanEverTick = true;
	MaxAmmo = 100;  // Example
	CurrentAmmo = MaxAmmo;
}

// Called when the game starts
void UAC_AmmoManager::BeginPlay()
{
	Super::BeginPlay();

	// Find HUD widget in the game and set it (Optional: can be done manually in the editor if needed)
	// For example, if you have the widget already added to the viewport:
	// HUDWidget = Cast<UBP_HUDWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());
}

// Update HUD widget with current ammo
void UAC_AmmoManager::SetHUDWidget(UBP_HUDWidget* InHUDWidget)
{
	if (InHUDWidget)
	{
		HUDWidget = InHUDWidget;
		// Initialize HUD with current ammo
		HUDWidget->UpdateAmmoText(CurrentAmmo);
	}
}

// Refill ammo
void UAC_AmmoManager::RefillAmmo(int32 Amount)
{
	CurrentAmmo = FMath::Clamp(CurrentAmmo + Amount, 0, MaxAmmo);

	if (HUDWidget)
	{
		HUDWidget->UpdateAmmoText(CurrentAmmo);  // Update HUD with new ammo count
	}
}

// Decrease ammo
void UAC_AmmoManager::DecreaseAmmo(int32 Amount)
{
	CurrentAmmo = FMath::Clamp(CurrentAmmo - Amount, 0, MaxAmmo);

	if (HUDWidget)
	{
		HUDWidget->UpdateAmmoText(CurrentAmmo);  // Update HUD with new ammo count
	}
}

// Check if the player has ammo
bool UAC_AmmoManager::HasAmmo() const
{
	return CurrentAmmo > 0;
}
