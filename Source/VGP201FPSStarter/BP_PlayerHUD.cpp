#include "BP_PlayerHUD.h"
#include "Blueprint/UserWidget.h"

ABP_PlayerHUD::ABP_PlayerHUD()
{
	// Set the widget class to null initially (can be assigned in the editor)
	HUDWidgetClass = nullptr;
	HUDWidgetInstance = nullptr;
}

void ABP_PlayerHUD::BeginPlay()
{
	Super::BeginPlay();

	// Check if the widget class is set
	if (HUDWidgetClass)
	{
		// Create the widget and add it to the viewport
		HUDWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
		if (HUDWidgetInstance)
		{
			HUDWidgetInstance->AddToViewport();
		}
	}
}
