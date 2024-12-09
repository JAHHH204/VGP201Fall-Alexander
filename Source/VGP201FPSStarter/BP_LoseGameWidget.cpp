#include "BP_LoseGameWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UBP_LoseGameWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // Bind the button click events
    if (TryAgainButton)
    {
        TryAgainButton->OnClicked.AddDynamic(this, &UBP_LoseGameWidget::OnTryAgainClicked);
    }

    if (MainMenuButton)
    {
        MainMenuButton->OnClicked.AddDynamic(this, &UBP_LoseGameWidget::OnMainMenuClicked);
    }

    // Enable the cursor and set the input mode to UI
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
    if (PlayerController)
    {
        // Show the mouse cursor
        PlayerController->bShowMouseCursor = true;

        // Set the input mode to UI, meaning player can interact with the UI
        FInputModeUIOnly InputMode;
        InputMode.SetWidgetToFocus(this->TakeWidget()); // Focus on this widget
        PlayerController->SetInputMode(InputMode);
    }
}

void UBP_LoseGameWidget::OnTryAgainClicked()
{
    // Remove the LoseGameWidget from the viewport
    RemoveFromViewport();

    // Reload the current level (i.e., try again)
    UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetMapName()));

    // Reset input mode and hide the mouse cursor
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
    if (PlayerController)
    {
        PlayerController->bShowMouseCursor = false;

        // Set input mode to Game Only
        FInputModeGameOnly InputMode;
        PlayerController->SetInputMode(InputMode);
    }
}

void UBP_LoseGameWidget::OnMainMenuClicked()
{
    // Remove the LoseGameWidget from the viewport
    RemoveFromViewport();

    // Load the main menu level
    UGameplayStatics::OpenLevel(this, FName("Map_MainMenu"));

    // Reset input mode and hide the mouse cursor
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
    if (PlayerController)
    {
        PlayerController->bShowMouseCursor = false;

        // Set input mode to Game Only
        FInputModeGameOnly InputMode;
        PlayerController->SetInputMode(InputMode);
    }
}
