// Fill out your copyright notice in the Description page of Project Settings.


#include "BP_UserWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"


bool UBP_UserWidget::Initialize()
{
	    Super::Initialize();

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

    return true;
}

void UBP_UserWidget::OnStartGameClicked()
{
    UGameplayStatics::OpenLevel(this, FName("MainGameLevel"));
}

void UBP_UserWidget::OnSettingsClicked()
{
    UE_LOG(LogTemp, Warning, TEXT("Settings Clicked"));
}

void UBP_UserWidget::OnExitClicked()
{
    UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);
}
