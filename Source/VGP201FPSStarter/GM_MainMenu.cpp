#include "GM_MainMenu.h"
#include "Blueprint/UserWidget.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "BP_UserWidget.h"

AGM_MainMenu::AGM_MainMenu()
{
	// Set this GameMode to use the default Pawn class and other settings if needed
}

void AGM_MainMenu::BeginPlay()
{
	Super::BeginPlay();

	// Check if the widget class is assigned in the editor
	if (MainMenuWidgetClass)
	{
		// Create and add the main menu widget to the viewport
		MainMenuWidget = CreateWidget<UBP_UserWidget>(GetWorld(), MainMenuWidgetClass);
		if (MainMenuWidget)
		{
			MainMenuWidget->AddToViewport();
		}
	}

	// Optional: Set the mouse cursor to be visible
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		PlayerController->bShowMouseCursor = true;
	}

	if (MainMenuMusic)
	{
		UGameplayStatics::PlaySound2D(this, MainMenuMusic);
	}
}

void AGM_MainMenu::StartGame()
{
	// Transition to the main game level
	UGameplayStatics::OpenLevel(this, FName("TestLevel"));
}

void AGM_MainMenu::ShowSettings()
{
	// Show settings screen or implement settings menu logic
	UE_LOG(LogTemp, Warning, TEXT("Settings Button Clicked"));
}

void AGM_MainMenu::ExitGame()
{
	// Quit the game
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);
}
