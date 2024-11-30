#include "BP_HealthPack.h"
#include "Components/BoxComponent.h" // For collision
#include "GameFramework/Actor.h"
#include "AC_PlayerHealth.h" // Custom health component
#include "GameFramework/Pawn.h"
#include "DrawDebugHelpers.h" // Optional, for debug visualization

// Sets default values
ABP_HealthPack::ABP_HealthPack()
{
    PrimaryActorTick.bCanEverTick = false; // No need to tick for a health pack

    // Create a collision component
    CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    CollisionComponent->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    CollisionComponent->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Overlap);
    CollisionComponent->SetupAttachment(RootComponent);

    // Bind the overlap event
    CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ABP_HealthPack::OnOverlapBegin);
}

// Called when the game starts or when spawned
void ABP_HealthPack::BeginPlay()
{
    Super::BeginPlay();

    // Optional: Debug box to visualize collision bounds
    DrawDebugBox(GetWorld(), GetActorLocation(), CollisionComponent->GetScaledBoxExtent(), FColor::Green, true, 5.0f);
}

// Overlap event
void ABP_HealthPack::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (!OtherActor)
        return;

    // Check if the overlapping actor is a player pawn
    APawn* PlayerPawn = Cast<APawn>(OtherActor);
    if (PlayerPawn)
    {
        // Find the player's health component
        UAC_PlayerHealth* PlayerHealth = PlayerPawn->FindComponentByClass<UAC_PlayerHealth>();
        if (PlayerHealth)
        {
            // Heal the player to full health
            PlayerHealth->CurrentHealth = PlayerHealth->MaxHealth;
            UE_LOG(LogTemp, Log, TEXT("Player healed to full health!"));

            // Destroy the health pack
            Destroy();
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Player does not have a health component!"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Non-player actor overlapped with the health pack."));
    }
}
