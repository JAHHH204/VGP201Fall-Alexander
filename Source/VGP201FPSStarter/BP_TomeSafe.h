#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "BP_TomeSafe.generated.h"

UCLASS()
class VGP201FPSSTARTER_API ABP_TomeSafe : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ABP_TomeSafe();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, Category = "Collider")
    UBoxComponent* BoxCollider;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Safe")
    FString CorrectCode = "1234"; // Set the correct code here

    UFUNCTION(BlueprintCallable, Category = "Safe")
    void Interact(); // Function called by the player to interact with the safe

    UFUNCTION(BlueprintCallable, Category = "Safe")
    void CheckCode(const FString& InputCode); // Function to verify the code
};
