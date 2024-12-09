#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BP_SettingWidget.generated.h"

class UButton; // Forward declaration for the button

UCLASS()
class VGP201FPSSTARTER_API UBP_SettingWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	// Button for closing the widget
	UPROPERTY(meta = (BindWidget))
	UButton* CloseButton;

	// Function to handle button click
	UFUNCTION()
	void OnCloseButtonClicked();



public:
	// Function to display the widget
	void DisplayWidget();

	virtual void NativeConstruct() override;
};
