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
    UFUNCTION(BlueprintCallable, Category = "TomeSafe")
    void SetSafeActorReference(ABP_TomeSafe* SafeActor);

    // Function to handle code submission
    UFUNCTION(BlueprintCallable, Category = "TomeSafe")
    void SubmitCode();

    // Reference to the Tome Safe actor
    UPROPERTY(BlueprintReadWrite, Category = "TomeSafe", meta = (ExposeOnSpawn = true))
    ABP_TomeSafe* SafeActorReference;

    // Function to append digits to the input code
    UFUNCTION(BlueprintCallable, Category = "TomeSafe")
    void AppendCode(FString Digit);
    UFUNCTION(BlueprintCallable, Category = "TomeSafe")
    void OnButton0Clicked();
    UFUNCTION(BlueprintCallable, Category = "TomeSafe")
    void OnButton1Clicked();
    UFUNCTION(BlueprintCallable, Category = "TomeSafe")
    void OnButton2Clicked();
    UFUNCTION(BlueprintCallable, Category = "TomeSafe")
    void OnButton3Clicked();
    UFUNCTION(BlueprintCallable, Category = "TomeSafe")
    void OnButton4Clicked();
    UFUNCTION(BlueprintCallable, Category = "TomeSafe")
    void OnButton5Clicked();
    UFUNCTION(BlueprintCallable, Category = "TomeSafe")
    void OnButton6Clicked();
    UFUNCTION(BlueprintCallable, Category = "TomeSafe")
    void OnButton7Clicked();
    UFUNCTION(BlueprintCallable, Category = "TomeSafe")
    void OnButton8Clicked();
    UFUNCTION(BlueprintCallable, Category = "TomeSafe")
    void OnButton9Clicked();
    UFUNCTION(BlueprintCallable, Category = "TomeSafe")
    void OnButtonSubmitClicked();
    UFUNCTION(BlueprintCallable, Category = "TomeSafe")
    void OnButtonCancelClicked();


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

    UPROPERTY(meta = (BindWidget))
    class UButton* ButtonSubmit;

    UPROPERTY(meta = (BindWidget))
    class UButton* ButtonCancel;

    virtual void NativeConstruct() override;
};
