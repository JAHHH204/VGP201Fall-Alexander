#include "BP_TomeGateLever.h"
#include "Components/BoxComponent.h"

// Sets default values
ABP_TomeGateLever::ABP_TomeGateLever()
{
    PrimaryActorTick.bCanEverTick = true;

    BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
    BoxCollider->SetupAttachment(RootComponent);
    BoxCollider->SetGenerateOverlapEvents(true);
    BoxCollider->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
}

// Called when the game starts or when spawned
void ABP_TomeGateLever::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void ABP_TomeGateLever::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Interact function to lift the linked gate
void ABP_TomeGateLever::Interact()
{
    if (TomeGate)
    {
        TomeGate->LiftGate();
        UE_LOG(LogTemp, Warning, TEXT("Lever activated, gate lifting!"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No gate linked to this lever."));
    }
}
