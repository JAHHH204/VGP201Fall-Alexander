#include "BP_TomeBook.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "PlayerCharacter.h"

ABP_TomeBook::ABP_TomeBook()
{
    PrimaryActorTick.bCanEverTick = true;

    // Create book mesh component
    BookMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BookMesh"));
    RootComponent = BookMesh;

    // Create box collider for pickup detection
    BoxColliderComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxColliderComponent"));
    BoxColliderComponent->SetupAttachment(BookMesh);
    BoxColliderComponent->SetCollisionProfileName(TEXT("Trigger"));
    BoxColliderComponent->OnComponentBeginOverlap.AddDynamic(this, &ABP_TomeBook::OnPickup);
}

void ABP_TomeBook::BeginPlay()
{
    Super::BeginPlay();
}

void ABP_TomeBook::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ABP_TomeBook::OnPickup(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    UE_LOG(LogTemp, Warning, TEXT("OnPickup triggered!"));

    APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);
    if (Player && Player->GunOffsetTransformComponent) // Ensure the player has a valid attachment point
    {
        // Attach the book to the player's designated attachment point
        AttachToComponent(Player->GunOffsetTransformComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

        // Disable collision and physics for the book
        BoxColliderComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        BookMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        BookMesh->SetSimulatePhysics(false);

        UE_LOG(LogTemp, Warning, TEXT("Book attached to player"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to attach book: Player or Book Offset Transform Component is invalid"));
    }
}
