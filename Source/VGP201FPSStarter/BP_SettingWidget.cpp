#include "BP_SettingWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UBP_SettingWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Bind the close button click event
	if (CloseButton)
	{
		CloseButton->OnClicked.AddDynamic(this, &UBP_SettingWidget::OnCloseButtonClicked);
	}
}

void UBP_SettingWidget::OnCloseButtonClicked()
{
	// Remove the widget from the viewport
	RemoveFromParent();

	// Optionally, reset the input mode
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		FInputModeGameOnly InputMode;
		PlayerController->SetInputMode(InputMode);
		PlayerController->bShowMouseCursor = true;
	}
}

void UBP_SettingWidget::DisplayWidget()
{
    UE_LOG(LogTemp, Warning, TEXT("DisplayWidget function called"));

    // Add the widget to the viewport
    AddToViewport();
    UE_LOG(LogTemp, Warning, TEXT("Widget added to viewport"));

    // Set the input mode to UI-only for interaction
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if (PlayerController)
    {
        FInputModeUIOnly InputMode;
        InputMode.SetWidgetToFocus(TakeWidget()); // Focus this widget
        PlayerController->SetInputMode(InputMode);
        PlayerController->bShowMouseCursor = true;
        UE_LOG(LogTemp, Warning, TEXT("Input mode set to UI only and mouse cursor enabled"));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("PlayerController is invalid"));
    }
}

