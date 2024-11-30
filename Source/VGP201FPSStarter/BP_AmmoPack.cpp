#include "BP_AmmoPack.h"
#include "Components/CapsuleComponent.h"
#include "PlayerCharacter.h"
#include "AC_AmmoManager.h"

// Sets default values
ABP_AmmoPack::ABP_AmmoPack()
{
	// Set this actor to call Tick() every frame.
	PrimaryActorTick.bCanEverTick = true;

	// Create and set up a capsule component for collision detection
	AmmoPackCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("AmmoPackCollision"));
	AmmoPackCollision->SetupAttachment(RootComponent);
	AmmoPackCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	AmmoPackCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	AmmoPackCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap); // Only interact with players
}

// Called when the game starts or when spawned
void ABP_AmmoPack::BeginPlay()
{
	Super::BeginPlay();

	// Bind overlap event
	AmmoPackCollision->OnComponentBeginOverlap.AddDynamic(this, &ABP_AmmoPack::OnOverlapBegin);
}

// Called every frame
void ABP_AmmoPack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called when something overlaps with the AmmoPack
void ABP_AmmoPack::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	// Check if the overlapping actor is a player character
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
	if (PlayerCharacter)
	{
		// Get the player's AmmoManager
		UAC_AmmoManager* AmmoManager = PlayerCharacter->AmmoManager;
		if (AmmoManager)
		{
			// Refill ammo here. You can adjust the refill logic based on your game design.
			AmmoManager->RefillAmmo(AmmoPackAmount); // Assume AmmoPackAmount is a variable indicating the refill amount

			// Optionally, destroy the ammo pack after use
			Destroy();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Player does not have an AmmoManager component!"));
		}
	}
}
