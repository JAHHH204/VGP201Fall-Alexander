#include "GM_MainMenu.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "BP_SettingWidget.h"

AGM_MainMenu::AGM_MainMenu()
{
	// Set default values
	PrimaryActorTick.bCanEverTick = false;
}

void AGM_MainMenu::BeginPlay()
{
	Super::BeginPlay();

	// Create the Main Menu Widget and add it to the viewport (if not already done in BP)
	if (MainMenuWidgetClass)
	{
		MainMenuWidget = CreateWidget<UBP_UserWidget>(GetWorld(), MainMenuWidgetClass);
		if (MainMenuWidget)
		{
			MainMenuWidget->AddToViewport();


		}
	}
}

void AGM_MainMenu::StartGame()
{
	// Start the game (replace with actual game start functionality)
	UE_LOG(LogTemp, Warning, TEXT("Starting the game!"));
}

void AGM_MainMenu::ShowSettings()
{
    UE_LOG(LogTemp, Warning, TEXT("ShowSettings function called"));

    if (BP_SettingWidgetClass)
    {
        UBP_SettingWidget* SettingWidget = CreateWidget<UBP_SettingWidget>(GetWorld(), BP_SettingWidgetClass);

        if (SettingWidget)
        {
            UE_LOG(LogTemp, Warning, TEXT("Setting Widget Created"));
            SettingWidget->DisplayWidget();
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to create setting widget"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("BP_SettingWidgetClass is not assigned"));
    }
}




void AGM_MainMenu::ExitGame()
{
	// Exit the game (or quit to desktop)
	UE_LOG(LogTemp, Warning, TEXT("Exiting game."));
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}
