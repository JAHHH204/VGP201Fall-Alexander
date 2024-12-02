#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Blueprint/UserWidget.h"
#include "BP_PlayerHUD.generated.h"

/**
 * Player HUD class to display in-game UI elements such as crosshairs, health bars, etc.
 */
UCLASS()
class VGP201FPSSTARTER_API ABP_PlayerHUD : public AHUD
{
	GENERATED_BODY()

public:
	// Constructor to set default values
	ABP_PlayerHUD();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	// Widget class to be displayed
	UPROPERTY(EditAnywhere, Category = "HUD")
	TSubclassOf<UUserWidget> HUDWidgetClass;

	// The actual widget instance
	UUserWidget* HUDWidgetInstance;
};
