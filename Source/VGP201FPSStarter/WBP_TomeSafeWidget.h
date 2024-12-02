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
    void OnButton0Clicked();
    void OnButton1Clicked();
    void OnButton2Clicked();
    void OnButton3Clicked();
    void OnButton4Clicked();
    void OnButton5Clicked();
    void OnButton6Clicked();
    void OnButton7Clicked();
    void OnButton8Clicked();
    void OnButton9Clicked();

    // The display area to show the entered code
    UPROPERTY(meta = (BindWidget))
    UTextBlock* CodeInputText;

protected:
    // Code input (stored as a string)
    FString InputCode;



    // Button references for digits 0-9
    UPROPERTY(meta = (BindWidget))
    class UButton* Button0;

    UPROPERTY(meta = (BindWidget))
    class UButton* Button1;

    UPROPERTY(meta = (BindWidget))
    class UButton* Button2;

    UPROPERTY(meta = (BindWidget))
    class UButton* Button3;

    UPROPERTY(meta = (BindWidget))
    class UButton* Button4;

    UPROPERTY(meta = (BindWidget))
    class UButton* Button5;

    UPROPERTY(meta = (BindWidget))
    class UButton* Button6;

    UPROPERTY(meta = (BindWidget))
    class UButton* Button7;

    UPROPERTY(meta = (BindWidget))
    class UButton* Button8;

    UPROPERTY(meta = (BindWidget))
    class UButton* Button9;

    virtual void NativeConstruct() override;
};
