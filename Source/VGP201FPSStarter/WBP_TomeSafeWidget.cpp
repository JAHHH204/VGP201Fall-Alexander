#include "WBP_TomeSafeWidget.h"
#include "Components/TextBlock.h"
#include "BP_TomeSafe.h"

void UWBP_TomeSafeWidget::SubmitCode()
{
    if (SafeActorReference)
    {
        SafeActorReference->CheckCode(InputCode);
    }
}

void UWBP_TomeSafeWidget::AppendCode(FString Digit)
{
    InputCode += Digit; // Append the digit to the current code
    if (CodeDisplayText)
    {
        CodeDisplayText->SetText(FText::FromString(InputCode)); // Update the displayed code
    }
}
