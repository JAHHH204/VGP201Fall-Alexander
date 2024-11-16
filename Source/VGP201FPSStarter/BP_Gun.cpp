// Fill out your copyright notice in the Description page of Project Settings.


#include "BP_Gun.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"
//#include "Engine/World.h"
//#include "GameFramework/Actor.h"

// Sets default values
ABP_Gun::ABP_Gun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    staticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("staticMeshComponent"));
	RootComponent = staticMeshComponent;

	boxColliderComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxColliderComponent"));
	boxColliderComponent->SetupAttachment(staticMeshComponent);
	boxColliderComponent->SetCollisionProfileName(TEXT("Trigger"));
	boxColliderComponent->OnComponentBeginOverlap.AddDynamic(this, &ABP_Gun::pickupWeapon);

	bulletOffsetTransformComponent = CreateDefaultSubobject<USceneComponent>(TEXT("BulletOffsetTransformComponent"));
	bulletOffsetTransformComponent->SetupAttachment(staticMeshComponent);

}

// Called when the game starts or when spawned
void ABP_Gun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABP_Gun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

}

//void ABP_Gun::pickupWeapon(AActor* OtherActor)
//{
//	APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);
//	if (Player && Player->gunOffsetTransformComponent)
//	{
//		// Attach the gun to the player's gun offset component
//		AttachToComponent(Player->gunOffsetTransformComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
//
//		// Optional: Disable collision once the gun is picked up
//		boxColliderComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
//	}
//}

void ABP_Gun::pickupWeapon(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    UE_LOG(LogTemp, Warning, TEXT("pickupWeapon function triggered!"));

    APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);
    if (Player && Player->GunOffsetTransformComponent)
    {
        // Attach the gun to the player's gun offset component
        AttachToComponent(Player->GunOffsetTransformComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

        // Optionally, update the player's equipped gun
        Player->EquippedGun = this; // Assuming EquippedGun is a pointer to ABP_Gun in the player class

        // Disable collision once the gun is picked up
        boxColliderComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

        // Optionally, make the gun visible or change its state (if required)
        SetActorHiddenInGame(false);

        UE_LOG(LogTemp, Warning, TEXT("Gun attached to player"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to attach gun: Player or Gun Offset Transform Component is invalid"));
    }
}


void ABP_Gun::BPShoot()
{
    // Check if a projectile class is set
    if (ProjectileClass)
    {
        // Get the spawn location and rotation from the bullet offset component
        FVector SpawnLocation = bulletOffsetTransformComponent->GetComponentLocation();
        FRotator SpawnRotation = bulletOffsetTransformComponent->GetComponentRotation();

        // Set up spawn parameters
        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this; // Set the gun as the owner
        SpawnParams.Instigator = GetInstigator(); // Set the instigator (optional, for identifying the actor firing the projectile)

        // Spawn the projectile actor
        ABP_Projectile* Projectile = GetWorld()->SpawnActor<ABP_Projectile>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);
        if (Projectile)
        {
            // Apply initial velocity to the projectile in the direction the gun is facing
            FVector ShootDirection = GetActorForwardVector(); // Get the gun's forward direction
            UProjectileMovementComponent* ProjectileMovement = Projectile->FindComponentByClass<UProjectileMovementComponent>();
            if (ProjectileMovement)
            {
                // Set the velocity of the projectile
                ProjectileMovement->SetVelocityInLocalSpace(ShootDirection * BulletSpeed);
                ProjectileMovement->Activate();
            }
        }
    }
}



;

