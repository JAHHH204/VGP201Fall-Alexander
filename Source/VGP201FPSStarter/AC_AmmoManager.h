#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BP_HUDWidget.h" // Include HUD widget header
#include "AC_AmmoManager.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class VGP201FPSSTARTER_API UAC_AmmoManager : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAC_AmmoManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:


	// Function to set the HUD widget
	UFUNCTION(BlueprintCallable, Category = "HUD")
	void SetHUDWidget(UBP_HUDWidget* InHUDWidget);

	// Refill ammo by a certain amount
	UFUNCTION(BlueprintCallable, Category = "Ammo")
	void RefillAmmo(int32 Amount);

	// Decrease ammo by a certain amount
	UFUNCTION(BlueprintCallable, Category = "Ammo")
	void DecreaseAmmo(int32 Amount);

	// Check if player has ammo
	UFUNCTION(BlueprintCallable, Category = "Ammo")
	bool HasAmmo() const;

private:
	// Current and Max Ammo
	int32 CurrentAmmo;
	int32 MaxAmmo;

	// Reference to the HUD widget
	UPROPERTY()
	UBP_HUDWidget* HUDWidget;
};
