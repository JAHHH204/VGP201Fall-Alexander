#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WMP_PauseWidget.generated.h"

/**
 * Pause widget that handles pausing, resuming, and exiting to the main menu.
 */
UCLASS()
class VGP201FPSSTARTER_API UWMP_PauseWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    // Function to resume the game
    UFUNCTION(BlueprintCallable, Category = "Pause Menu")
    void ResumeGame();

    // Function to quit to the main menu
    UFUNCTION(BlueprintCallable, Category = "Pause Menu")
    void QuitToMainMenu();
};
