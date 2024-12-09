#include "BP_UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"  // Include this for UTextBlock
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GM_MainMenu.h"  // Include your main menu game mode class for accessing ShowSettings

bool UBP_UserWidget::Initialize()
{
    Super::Initialize();

    // Check for the buttons and bind actions
    if (StartGameButton)
    {
        StartGameButton->OnClicked.AddDynamic(this, &UBP_UserWidget::OnStartGameClicked);
    }
    if (SettingsButton)
    {
        SettingsButton->OnClicked.AddDynamic(this, &UBP_UserWidget::OnSettingsClicked);
    }
    if (ExitButton)
    {
        ExitButton->OnClicked.AddDynamic(this, &UBP_UserWidget::OnExitClicked);
    }

    // Set the game title text
    if (GameTitleText)
    {
        GameTitleText->SetText(FText::FromString(TEXT("Tome Of Terror"))); // Set your game title here
    }

    return true;
}

void UBP_UserWidget::OnStartGameClicked()
{
    UGameplayStatics::OpenLevel(this, FName("MainGameLevel"));
}

void UBP_UserWidget::OnSettingsClicked()
{
    UE_LOG(LogTemp, Warning, TEXT("Settings Clicked"));

    // Check if the main menu game mode is valid and call ShowSettings
    AGameModeBase* GameMode = UGameplayStatics::GetGameMode(this);
    AGM_MainMenu* MainMenuGameMode = Cast<AGM_MainMenu>(GameMode);
    if (MainMenuGameMode)
    {
        MainMenuGameMode->ShowSettings();
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to cast to AGM_MainMenu"));
    }
}

void UBP_UserWidget::OnExitClicked()
{
    UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);
}
