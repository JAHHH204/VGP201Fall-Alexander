#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BP_LoseGameWidget.generated.h"

/**
 *
 */
UCLASS()
class VGP201FPSSTARTER_API UBP_LoseGameWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	// Declare the buttons as UPROPERTY so they are accessible in the editor
	UPROPERTY(meta = (BindWidget))
	class UButton* TryAgainButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* MainMenuButton;

	// Functions to handle button clicks
	UFUNCTION()
	void OnTryAgainClicked();

	UFUNCTION()
	void OnMainMenuClicked();

public:
	virtual void NativeConstruct() override;
};
