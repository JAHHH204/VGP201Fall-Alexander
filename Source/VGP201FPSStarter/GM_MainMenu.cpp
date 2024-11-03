// Fill out your copyright notice in the Description page of Project Settings.


#include "GM_MainMenu.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "BP_UserWidget.h"

void AGM_MainMenu::BeginPlay()
{

    Super::BeginPlay();

    if (TSubclassOf<UBP_UserWidget> MainMenuClass = LoadClass<UBP_UserWidget>(nullptr, TEXT("/Game/UI/UBP_UserWidget.UBP_UserWidget_C")))
    {
        UBP_UserWidget* MainMenu = CreateWidget<UBP_UserWidget>(GetWorld(), MainMenuClass);
        if (MainMenu)
        {
            MainMenu->AddToViewport();
            GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
            GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeUIOnly());
        }
    }
}
