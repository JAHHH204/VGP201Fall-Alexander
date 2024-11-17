#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BP_UserWidget.h"
#include "GM_MainMenu.generated.h"
class USoundCue;
/**
 * Main Menu Game Mode class
 */
UCLASS()
class VGP201FPSSTARTER_API AGM_MainMenu : public AGameModeBase
{
	GENERATED_BODY()

public:
	// Sets default values for this game's mode
	AGM_MainMenu();

	// Handle for starting the game
	UFUNCTION()
	void StartGame();

	// Handle for showing settings
	UFUNCTION()
	void ShowSettings();

	// Handle for exiting the game
	UFUNCTION()
	void ExitGame();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// The widget class for the main menu
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UBP_UserWidget> MainMenuWidgetClass;

	// The instance of the main menu widget
	UPROPERTY()
	UBP_UserWidget* MainMenuWidget;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Music")
	USoundCue* MainMenuMusic;

};
