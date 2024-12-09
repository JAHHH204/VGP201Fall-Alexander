#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BP_HUDWidget.generated.h"

/**
 * HUD Widget class with health and ammo updates
 */
UCLASS()
class VGP201FPSSTARTER_API UBP_HUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// Function to update health bar
	UFUNCTION(BlueprintCallable, Category = "HUD")
	void UpdateHealthBar(float HealthPercentage);

	// Function to update ammo text
	UFUNCTION(BlueprintCallable, Category = "HUD")
	void UpdateAmmoText(int32 CurrentAmmo);

protected:
	// References to widgets
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HealthBar;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* AmmoNumberText;
};
