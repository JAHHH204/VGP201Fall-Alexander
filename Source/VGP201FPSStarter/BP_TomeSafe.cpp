#include "BP_TomeSafe.h"
#include "Blueprint/UserWidget.h" // For widgets
#include "Components/BoxComponent.h"
#include "WBP_TomeSafeWidget.h"

ABP_TomeSafe::ABP_TomeSafe()
{
    PrimaryActorTick.bCanEverTick = true;

    BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
    BoxCollider->SetupAttachment(RootComponent);
    BoxCollider->SetGenerateOverlapEvents(true);
    BoxCollider->SetCollisionProfileName(TEXT("Interactable"));
}

void ABP_TomeSafe::BeginPlay()
{
    Super::BeginPlay();
}

void ABP_TomeSafe::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ABP_TomeSafe::Interact()
{
    if (SafeWidgetInstance == nullptr && BP_SafeWidgetClass)
    {
        SafeWidgetInstance = CreateWidget<UWBP_TomeSafeWidget>(GetWorld(), BP_SafeWidgetClass);
        if (SafeWidgetInstance)
        {
            SafeWidgetInstance->AddToViewport(100);
            UE_LOG(LogTemp, Warning, TEXT("Safe widget displayed."));

            // Set the reference to the safe actor
            UWBP_TomeSafeWidget* TomeSafeWidget = Cast<UWBP_TomeSafeWidget>(SafeWidgetInstance);
            if (TomeSafeWidget)
            {
                TomeSafeWidget->SetSafeActorReference(this);  // Set the safe actor reference
            }

            // Show the mouse cursor and set input mode
            APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
            if (PlayerController)
            {
                PlayerController->bShowMouseCursor = true;
                PlayerController->SetInputMode(FInputModeUIOnly().SetWidgetToFocus(SafeWidgetInstance->TakeWidget()));
            }
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to create SafeWidgetInstance!"));
        }
    }
}






void ABP_TomeSafe::CheckCode(const FString& InputCode)
{
    // Find the player controller
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if (!PlayerController)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to get PlayerController!"));
        return;
    }

    // Check if the code is correct
    if (InputCode == CorrectCode)
    {
        UE_LOG(LogTemp, Warning, TEXT("Correct Code! Safe is now open."));

        // Trigger any animation or effect here if needed
        // For example, play animation, or show an effect before destroying the safe

        // Remove the widget from the viewport
        if (SafeWidgetInstance)
        {
            SafeWidgetInstance->RemoveFromViewport();
            SafeWidgetInstance = nullptr;  // Clear the reference
        }

        // Set input mode back to game control
        PlayerController->bShowMouseCursor = false;  // Hide the mouse cursor
        PlayerController->SetInputMode(FInputModeGameOnly());  // Set input mode to game

        // Destroy the safe (replace with a visual effect if desired)
        Destroy();
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Incorrect Code."));
    }
}


void ABP_TomeSafe::ResetWidgetInstance()
{
    if (SafeWidgetInstance)
    {
        SafeWidgetInstance->RemoveFromParent();  // Remove it from the viewport
        SafeWidgetInstance = nullptr;            // Clear the reference
    }
}

FString ABP_TomeSafe::GetCorrectCode() const
{
    return CorrectCode;  // Return the correct code for comparison
}
