#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BP_TomeAltar.generated.h"

class ABP_TomeBook;

UCLASS()
class VGP201FPSSTARTER_API ABP_TomeAltar : public AActor
{
    GENERATED_BODY()

public:
    ABP_TomeAltar();

protected:
    virtual void BeginPlay() override;

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
    UBoxComponent* AltarCollision;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tome")
    int32 MaxTomes = 3;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tome")
    TArray<ABP_TomeBook*> PlacedTomes;

    UFUNCTION()
    void PlaceTome(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION(BlueprintImplementableEvent, Category = "Tome")
    void OnAllTomesPlaced();
};
