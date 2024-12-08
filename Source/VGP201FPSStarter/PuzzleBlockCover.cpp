#include "PuzzleBlockCover.h"
#include "BP_Projectile.h"
#include "Components/BoxComponent.h"

// Sets default values
APuzzleBlockCover::APuzzleBlockCover()
{
    PrimaryActorTick.bCanEverTick = false;

    BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
    RootComponent = BoxComponent;
    BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    BoxComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
    BoxComponent->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block); // Block dynamic objects like projectiles

    BoxComponent->OnComponentHit.AddDynamic(this, &APuzzleBlockCover::OnProjectileHit);
}

void APuzzleBlockCover::BeginPlay()
{
    Super::BeginPlay();
}

void APuzzleBlockCover::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if (OtherActor)
    {
        UE_LOG(LogTemp, Log, TEXT("Hit detected with actor: %s"), *OtherActor->GetName());
    }

    if (OtherActor && OtherActor->IsA(ABP_Projectile::StaticClass()))
    {
        UE_LOG(LogTemp, Log, TEXT("Puzzle block hit by a projectile. Destroying..."));

        // Optionally, disable physics and collision before destroying
        BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        BoxComponent->SetSimulatePhysics(false);  // Disable physics if enabled

        // Destroy the puzzle block cover
        Destroy();

        // Log to ensure destruction happens
        UE_LOG(LogTemp, Log, TEXT("Puzzle block destroyed"));
    }
}
