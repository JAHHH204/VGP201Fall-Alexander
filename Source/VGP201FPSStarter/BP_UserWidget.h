#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BP_UserWidget.generated.h"

/**
 *
 */
UCLASS()
class VGP201FPSSTARTER_API UBP_UserWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual bool Initialize() override;

protected:
    // Camera component (if you want to manipulate it or use it in the widget)
    UPROPERTY(EditAnywhere)
    class UCameraComponent* cameraComponent;

    // Buttons for the main menu
    UPROPERTY(meta = (BindWidget))
    class UButton* StartGameButton;

    UPROPERTY(meta = (BindWidget))
    class UButton* SettingsButton;

    UPROPERTY(meta = (BindWidget))
    class UButton* ExitButton;

    // Text block for the game title
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* GameTitleText;

private:
    UFUNCTION()
    void OnStartGameClicked();

    UFUNCTION()
    void OnSettingsClicked();

    UFUNCTION()
    void OnExitClicked();
};
