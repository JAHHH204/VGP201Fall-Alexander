#include "WMP_PauseWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"

void UWMP_PauseWidget::ResumeGame()
{
    if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
    {
        // Unpause the game
        UGameplayStatics::SetGamePaused(GetWorld(), false);

        // Hide the pause menu
        RemoveFromParent();

        // Re-enable input for the player
        FInputModeGameOnly InputMode;
        PlayerController->SetInputMode(InputMode);
        PlayerController->bShowMouseCursor = false;
    }
}

void UWMP_PauseWidget::QuitToMainMenu()
{
    if (UWorld* World = GetWorld())
    {
        // Ensure the game is unpaused before changing levels
        UGameplayStatics::SetGamePaused(World, false);

        // Load the Main Menu level
        UGameplayStatics::OpenLevel(World, FName("MainMenu"));
    }
}
