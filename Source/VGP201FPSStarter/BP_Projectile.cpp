#include "BP_Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABP_Projectile::ABP_Projectile()
{
    // Set this actor to call Tick() every frame.
    PrimaryActorTick.bCanEverTick = true;

    // Create the static mesh component for the projectile
    ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
    ProjectileMesh->SetNotifyRigidBodyCollision(true); // Enable hit events
    RootComponent = ProjectileMesh;

    // Create the projectile movement component
    ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
    ProjectileMovementComponent->UpdatedComponent = ProjectileMesh; // Set which component is being moved
    ProjectileMovementComponent->InitialSpeed = ProjectileSpeed; // Set the initial speed of the projectile
    ProjectileMovementComponent->MaxSpeed = ProjectileSpeed; // Ensure the projectile doesn’t exceed the initial speed
    ProjectileMovementComponent->bRotationFollowsVelocity = true; // Make the projectile rotate with its velocity
    ProjectileMovementComponent->bShouldBounce = true; // Optional: makes the projectile bounce off surfaces

    // Enable physics on the projectile mesh
    ProjectileMesh->SetSimulatePhysics(true);

    ProjectileMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    ProjectileMesh->SetCollisionResponseToAllChannels(ECR_Ignore);  // Ignore all by default
    ProjectileMesh->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block); // Block dynamic objects

}

// Called when the game starts or when spawned
void ABP_Projectile::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void ABP_Projectile::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Fire the projectile in the given direction
void ABP_Projectile::FireInDirection(const FVector& ShootDirection)
{
    if (ProjectileMovementComponent)
    {
        ProjectileMovementComponent->Velocity = ShootDirection.GetSafeNormal() * ProjectileSpeed;

        FVector LookAtDirection = ShootDirection.GetSafeNormal();
        FRotator NewRotation = LookAtDirection.Rotation();
        SetActorRotation(NewRotation);
    }
}
