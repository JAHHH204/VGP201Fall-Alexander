#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BP_TomeGate.generated.h"

UCLASS()
class VGP201FPSSTARTER_API ABP_TomeGate : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ABP_TomeGate();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Function to lift the gate
    UFUNCTION(BlueprintCallable, Category = "Gate")
    void LiftGate();
};
