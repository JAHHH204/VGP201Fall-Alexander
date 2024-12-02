#include "PuzzleBlockCover.h"
#include "BP_Projectile.h"
#include "Components/BoxComponent.h"

// Sets default values
APuzzleBlockCover::APuzzleBlockCover()
{
    // Set this actor to not call Tick() every frame to improve performance
    PrimaryActorTick.bCanEverTick = false;

    // Create and configure BoxComponent
    BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
    RootComponent = BoxComponent;
    BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    BoxComponent->SetCollisionResponseToAllChannels(ECR_Ignore);  // Ignore all channels by default
    BoxComponent->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block); // Block dynamic objects (like projectiles)

    // Bind collision event
    BoxComponent->OnComponentHit.AddDynamic(this, &APuzzleBlockCover::OnProjectileHit);
}

void APuzzleBlockCover::BeginPlay()
{
    Super::BeginPlay();
}

void APuzzleBlockCover::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    // Debugging log to check if the event is triggered
    if (OtherActor)
    {
        UE_LOG(LogTemp, Log, TEXT("Hit detected with actor: %s"), *OtherActor->GetName());
    }

    if (OtherActor && OtherActor->IsA(ABP_Projectile::StaticClass()))
    {
        UE_LOG(LogTemp, Log, TEXT("Puzzle block hit by a projectile. Destroying..."));

        // Optionally trigger effects before destroying
        // PlayEffects();

        Destroy();  // Destroy the puzzle block cover
    }
}
