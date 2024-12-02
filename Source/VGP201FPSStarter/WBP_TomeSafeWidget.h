#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WBP_TomeSafeWidget.generated.h"

class ABP_TomeSafe; // Forward declaration

/**
 * Widget for interacting with the Tome Safe
 */
UCLASS()
class VGP201FPSSTARTER_API UWBP_TomeSafeWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    // Function to handle code submission
    UFUNCTION(BlueprintCallable, Category = "TomeSafe")
    void SubmitCode();

    // Reference to the Tome Safe actor
    UPROPERTY(BlueprintReadWrite, Category = "TomeSafe", meta = (ExposeOnSpawn = true))
    ABP_TomeSafe* SafeActorReference;

    // Function to append digits to the input code
    UFUNCTION(BlueprintCallable, Category = "TomeSafe")
    void AppendCode(FString Digit);

protected:
    // Code input (stored as a string)
    FString InputCode;

    // The display area to show the entered code
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TomeSafe")
    class UTextBlock* CodeDisplayText;  // Display TextBlock (no BindWidget here)
};
