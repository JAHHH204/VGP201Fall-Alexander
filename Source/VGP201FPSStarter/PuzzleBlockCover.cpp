#include "PuzzleBlockCover.h"
#include "BP_Projectile.h"
#include "Components/BoxComponent.h"

// Sets default values
APuzzleBlockCover::APuzzleBlockCover()
{
    // Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    // Create a BoxComponent for collision
    UBoxComponent* BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
    BoxComponent->SetupAttachment(RootComponent); // Attach it to the root component
    BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics); // Enable collision
    BoxComponent->SetCollisionResponseToAllChannels(ECR_Ignore); // Ignore all collisions by default
    BoxComponent->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block); // Block with dynamic objects (projectiles)

    RootComponent = BoxComponent; // Set the BoxComponent as the root

    // Bind the OnHit event to the function
    BoxComponent->OnComponentHit.AddDynamic(this, &APuzzleBlockCover::OnProjectileHit);
}

// Called when the game starts or when spawned
void APuzzleBlockCover::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void APuzzleBlockCover::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void APuzzleBlockCover::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    // Check if the actor that collided with this object is a projectile
    if (OtherActor && OtherActor->IsA(ABP_Projectile::StaticClass()))
    {
        UE_LOG(LogTemp, Warning, TEXT("Mirror hit by a projectile!"));

        // Destroy the PuzzleBlockCover on collision with a projectile
        Destroy();
    }
}
