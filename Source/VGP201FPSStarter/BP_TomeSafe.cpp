#include "BP_TomeSafe.h"
#include "Blueprint/UserWidget.h" // For widgets
#include "Components/BoxComponent.h"

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
    if (!BP_SafeWidgetClass)
    {
        UE_LOG(LogTemp, Error, TEXT("BP_SafeWidgetClass is not set."));
        return;
    }

    if (!SafeWidgetInstance)
    {
        SafeWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), BP_SafeWidgetClass);
        if (SafeWidgetInstance)
        {
            SafeWidgetInstance->AddToViewport(100); // Ensure it is on top
            UE_LOG(LogTemp, Warning, TEXT("Safe widget displayed."));

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
    if (InputCode == CorrectCode)
    {
        UE_LOG(LogTemp, Warning, TEXT("Correct Code! Safe is now open."));
        // Trigger animation or effect here before destroying the safe
        Destroy();  // Temporarily destroy the safe (replace with visual effects if needed)
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Incorrect Code."));
    }
}
