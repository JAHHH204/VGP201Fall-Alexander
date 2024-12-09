#include "WBP_TomeSafeWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "BP_TomeSafe.h"

void UWBP_TomeSafeWidget::NativeConstruct()
{
    Super::NativeConstruct();
    AppendCode("Enter Code");

    // Dynamically bind buttons to their respective click handlers
    if (Button0)
    {
        Button0->OnClicked.AddDynamic(this, &UWBP_TomeSafeWidget::OnButton0Clicked);
        UE_LOG(LogTemp, Warning, TEXT("Button 0 dynamically bound!"));
    }
    if (Button1)
    {
        Button1->OnClicked.AddDynamic(this, &UWBP_TomeSafeWidget::OnButton1Clicked);
        UE_LOG(LogTemp, Warning, TEXT("Button 1 dynamically bound!"));
    }
    if (Button2)
    {
        Button2->OnClicked.AddDynamic(this, &UWBP_TomeSafeWidget::OnButton2Clicked);
        UE_LOG(LogTemp, Warning, TEXT("Button 2 dynamically bound!"));
    }
    if (Button3)
    {
        Button3->OnClicked.AddDynamic(this, &UWBP_TomeSafeWidget::OnButton3Clicked);
        UE_LOG(LogTemp, Warning, TEXT("Button 3 dynamically bound!"));
    }
    if (Button4)
    {
        Button4->OnClicked.AddDynamic(this, &UWBP_TomeSafeWidget::OnButton4Clicked);
        UE_LOG(LogTemp, Warning, TEXT("Button 4 dynamically bound!"));
    }
    if (Button5)
    {
        Button5->OnClicked.AddDynamic(this, &UWBP_TomeSafeWidget::OnButton5Clicked);
        UE_LOG(LogTemp, Warning, TEXT("Button 5 dynamically bound!"));
    }
    if (Button6)
    {
        Button6->OnClicked.AddDynamic(this, &UWBP_TomeSafeWidget::OnButton6Clicked);
        UE_LOG(LogTemp, Warning, TEXT("Button 6 dynamically bound!"));
    }
    if (Button7)
    {
        Button7->OnClicked.AddDynamic(this, &UWBP_TomeSafeWidget::OnButton7Clicked);
        UE_LOG(LogTemp, Warning, TEXT("Button 7 dynamically bound!"));
    }
    if (Button8)
    {
        Button8->OnClicked.AddDynamic(this, &UWBP_TomeSafeWidget::OnButton8Clicked);
        UE_LOG(LogTemp, Warning, TEXT("Button 8 dynamically bound!"));
    }
    if (Button9)
    {
        Button9->OnClicked.AddDynamic(this, &UWBP_TomeSafeWidget::OnButton9Clicked);
        UE_LOG(LogTemp, Warning, TEXT("Button 9 dynamically bound!"));
    }



    // Set up the input mode for UI interaction
    if (Button0)
    {
        FInputModeUIOnly InputMode;
        APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

        // Focus on the Button0 widget
        if (PlayerController)
        {

            PlayerController->SetInputMode(InputMode);
            PlayerController->bShowMouseCursor = true;
        }
    }
}


void UWBP_TomeSafeWidget::OnButton0Clicked()
{
    AppendCode("0");
    UE_LOG(LogTemp, Warning, TEXT("Button 0 clicked"));
}

void UWBP_TomeSafeWidget::OnButton1Clicked()
{
    AppendCode("1");
    UE_LOG(LogTemp, Warning, TEXT("Button 1 clicked"));
}

void UWBP_TomeSafeWidget::OnButton2Clicked()
{
    AppendCode("2");
    UE_LOG(LogTemp, Warning, TEXT("Button 2 clicked"));
}

void UWBP_TomeSafeWidget::OnButton3Clicked()
{
    AppendCode("3");
    UE_LOG(LogTemp, Warning, TEXT("Button 3 clicked"));
}

void UWBP_TomeSafeWidget::OnButton4Clicked()
{
    AppendCode("4");
    UE_LOG(LogTemp, Warning, TEXT("Button 4 clicked"));
}

void UWBP_TomeSafeWidget::OnButton5Clicked()
{
    AppendCode("5");
    UE_LOG(LogTemp, Warning, TEXT("Button 5 clicked"));
}

void UWBP_TomeSafeWidget::OnButton6Clicked()
{
    AppendCode("6");
    UE_LOG(LogTemp, Warning, TEXT("Button 6 clicked"));
}

void UWBP_TomeSafeWidget::OnButton7Clicked()
{
    AppendCode("7");
    UE_LOG(LogTemp, Warning, TEXT("Button 7 clicked"));
}

void UWBP_TomeSafeWidget::OnButton8Clicked()
{
    AppendCode("8");
    UE_LOG(LogTemp, Warning, TEXT("Button 8 clicked"));
}

void UWBP_TomeSafeWidget::OnButton9Clicked()
{
    AppendCode("9");
    UE_LOG(LogTemp, Warning, TEXT("Button 9 clicked"));
}

void UWBP_TomeSafeWidget::AppendCode(FString Digit)
{
    UE_LOG(LogTemp, Warning, TEXT("Appending code: %s"), *Digit);  // Debug log for the digit
    InputCode += Digit; // Appending the digit to the input code

    // Check if CodeInputText is valid before setting text
    if (CodeInputText)
    {
        // Convert InputCode to FText and update the CodeInputText widget
        FText NewText = FText::FromString(InputCode);
        CodeInputText->SetText(NewText);

        // Debug log to confirm the updated text
        UE_LOG(LogTemp, Warning, TEXT("Updated CodeInputText: %s"), *InputCode);
    }
    else
    {
        // Log error if the CodeInputText widget reference is invalid
        UE_LOG(LogTemp, Error, TEXT("CodeInputText is NULL when trying to update!"));
    }
}


void UWBP_TomeSafeWidget::SubmitCode()
{
    if (SafeActorReference)
    {
        SafeActorReference->CheckCode(InputCode);
        InputCode.Empty(); // Reset the code after submission
        if (CodeInputText)
        {
            CodeInputText->SetText(FText::FromString(InputCode)); // Clear the displayed code
        }
    }
}
