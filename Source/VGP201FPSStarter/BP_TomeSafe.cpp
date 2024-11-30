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
    // Trigger the UI widget
    UE_LOG(LogTemp, Warning, TEXT("Player interacted with the safe."));
    // Add code to create and display the widget
    // Example:
    // UUserWidget* SafeWidget = CreateWidget<UUserWidget>(GetWorld(), SafeWidgetClass);
    // SafeWidget->AddToViewport();
}

void ABP_TomeSafe::CheckCode(const FString& InputCode)
{
    if (InputCode == CorrectCode)
    {
        UE_LOG(LogTemp, Warning, TEXT("Correct Code! Safe is now open."));
        Destroy(); // Temporarily destroy the safe
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Incorrect Code."));
    }
}
