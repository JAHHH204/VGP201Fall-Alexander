#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BP_TomeGate.h"
#include "Components/BoxComponent.h"
#include "BP_TomeGateLever.generated.h"

UCLASS()
class VGP201FPSSTARTER_API ABP_TomeGateLever : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ABP_TomeGateLever();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere,  Category = "Collider")
    UBoxComponent* BoxCollider;

    // Reference to the associated gate
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gate")
    ABP_TomeGate* TomeGate;

    // Function to interact with the lever
    UFUNCTION(BlueprintCallable, Category = "Interaction")
    void Interact();
};
