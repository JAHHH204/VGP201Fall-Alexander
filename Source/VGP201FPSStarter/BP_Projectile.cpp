#include "BP_Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABP_Projectile::ABP_Projectile()
{
	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
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
	ProjectileMovementComponent->bShouldBounce = true; // Optional: makes the projectile bounce off surfaces (if needed)

	// Enable physics on the projectile mesh
	ProjectileMesh->SetSimulatePhysics(true);
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
	// Ensure the projectile movement component is properly set
	if (ProjectileMovementComponent)
	{
		// Normalize the ShootDirection to ensure consistent speed, then set the velocity
		ProjectileMovementComponent->Velocity = ShootDirection.GetSafeNormal() * ProjectileSpeed;

		// Optional: Align the projectile's rotation to match the direction of travel
		FVector LookAtDirection = ShootDirection.GetSafeNormal();
		FRotator NewRotation = LookAtDirection.Rotation();  // Convert direction to rotation
		SetActorRotation(NewRotation);  // Apply the new rotation to the projectile
	}
}

