#include "BP_TomeAltar.h"
#include "Components/BoxComponent.h"
#include "BP_TomeBook.h"
#include "PlayerCharacter.h"
#include "Kismet/KismetSystemLibrary.h"

ABP_TomeAltar::ABP_TomeAltar()
{
    PrimaryActorTick.bCanEverTick = false;

    AltarCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("AltarCollision"));
    RootComponent = AltarCollision;

    AltarCollision->SetGenerateOverlapEvents(true);
    AltarCollision->OnComponentBeginOverlap.AddDynamic(this, &ABP_TomeAltar::PlaceTome);
}

void ABP_TomeAltar::BeginPlay()
{
    Super::BeginPlay();
}

void ABP_TomeAltar::PlaceTome(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);
    if (!Player || !Player->EquippedTome)
    {
        UE_LOG(LogTemp, Warning, TEXT("No player or equipped tome detected."));
        return;
    }

    ABP_TomeBook* TomeBook = Cast<ABP_TomeBook>(Player->EquippedTome);
    if (!TomeBook)
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid tome detected."));
        return;
    }

    // Place the tome
    TomeBook->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
    FVector PlacementLocation = GetActorLocation() + FVector(0, PlacedTomes.Num() * 50, 0); // Adjust Y-offset for stacking
    TomeBook->SetActorLocation(PlacementLocation);
    TomeBook->SetActorEnableCollision(false);

    // Update state
    PlacedTomes.Add(TomeBook);
    Player->EquippedTome = nullptr;

    UE_LOG(LogTemp, Warning, TEXT("Tome placed. Total tomes: %d"), PlacedTomes.Num());

    // Check if altar is complete
    if (PlacedTomes.Num() >= MaxTomes)
    {
        OnAllTomesPlaced();
        UE_LOG(LogTemp, Warning, TEXT("All tomes placed!"));
    }
}
