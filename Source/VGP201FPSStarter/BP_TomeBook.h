#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BP_TomeBook.generated.h"

class UBoxComponent;

UCLASS()
class VGP201FPSSTARTER_API ABP_TomeBook : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ABP_TomeBook();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Collision box for pickup
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UBoxComponent* BoxColliderComponent;

    // Static mesh for the book
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UStaticMeshComponent* BookMesh;

    // Function to handle pickup logic
    UFUNCTION()
    void OnPickup(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
