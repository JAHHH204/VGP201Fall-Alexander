#include "BP_TomeGate.h"

// Sets default values
ABP_TomeGate::ABP_TomeGate()
{
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABP_TomeGate::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void ABP_TomeGate::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Lifts the gate by moving it up
void ABP_TomeGate::LiftGate()
{
    FVector NewLocation = GetActorLocation();
    NewLocation.Z += 500.0f; // Adjust height as needed
    SetActorLocation(NewLocation);

    UE_LOG(LogTemp, Warning, TEXT("Tome Gate is lifting!"));
}
