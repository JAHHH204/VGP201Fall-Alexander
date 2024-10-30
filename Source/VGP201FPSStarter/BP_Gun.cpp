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

	staticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
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
	APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);
	if (Player && Player->GunOffsetTransformComponent)
	{
		// Attach the gun to the player's gun offset component
		AttachToComponent(Player->GunOffsetTransformComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

		// Disable collision once the gun is picked up
		boxColliderComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
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

		// Spawn the projectile actor
		AActor* Projectile = GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnLocation, SpawnRotation);
		if (Projectile)
		{
			// Apply initial velocity to the projectile if it has a ProjectileMovementComponent
			UProjectileMovementComponent* ProjectileMovement = Projectile->FindComponentByClass<UProjectileMovementComponent>();
			if (ProjectileMovement)
			{
				ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * BulletSpeed);
				ProjectileMovement->Activate();
			}
		}
	}
}

;

