#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "PuzzleBlockCover.generated.h"

UCLASS()
class VGP201FPSSTARTER_API APuzzleBlockCover : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    APuzzleBlockCover();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Collision detection
    UPROPERTY(VisibleAnywhere)
    UBoxComponent* BoxComponent;

    // Function to handle when the projectile hits the puzzle block
    UFUNCTION()
    void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
