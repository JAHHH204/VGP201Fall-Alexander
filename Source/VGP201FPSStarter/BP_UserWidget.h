// Fill out your copyright notice in the Description page of Project Settings.

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
    UPROPERTY(meta = (BindWidget))
    class UButton* StartGameButton;

    UPROPERTY(meta = (BindWidget))
    class UButton* SettingsButton;

    UPROPERTY(meta = (BindWidget))
    class UButton* ExitButton;

private:
    UFUNCTION()
    void OnStartGameClicked();

    UFUNCTION()
    void OnSettingsClicked();

    UFUNCTION()
    void OnExitClicked();
	
};
