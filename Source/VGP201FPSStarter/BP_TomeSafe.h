#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Blueprint/UserWidget.h" // For widgets
#include "Components/BoxComponent.h"
#include "BP_TomeSafe.generated.h"

UCLASS()
class VGP201FPSSTARTER_API ABP_TomeSafe : public AActor
{
    GENERATED_BODY()

public:
    ABP_TomeSafe();

    // Box Collider for interaction
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UBoxComponent* BoxCollider;

    // Correct code to unlock the safe
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TomeSafe")
    FString CorrectCode = "1234"; // Change this to your desired code

    // The widget class for the safe's interaction UI
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TomeSafe")
    TSubclassOf<UUserWidget> BP_SafeWidgetClass;

    // Instance of the widget
    UUserWidget* SafeWidgetInstance;

    // Interact function to open the widget
    UFUNCTION(BlueprintCallable, Category = "TomeSafe")
    void Interact();

    UFUNCTION(BlueprintCallable, Category = "TomeSafe")
    void ResetWidgetInstance();

    FString GetCorrectCode() const;

    // Check the entered code
    UFUNCTION(BlueprintCallable, Category = "TomeSafe")
    void CheckCode(const FString& InputCode);

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;
};
