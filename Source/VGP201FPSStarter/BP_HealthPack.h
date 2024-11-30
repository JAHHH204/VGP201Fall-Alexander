#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BP_HealthPack.generated.h"

class UBoxComponent;

UCLASS()
class VGP201FPSSTARTER_API ABP_HealthPack : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ABP_HealthPack();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // Function to handle overlap events
    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
    // Collision component
    UPROPERTY(VisibleAnywhere)
    UBoxComponent* CollisionComponent;
};
