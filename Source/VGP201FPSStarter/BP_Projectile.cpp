// Fill out your copyright notice in the Description page of Project Settings.


#include "BP_Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABP_Projectile::ABP_Projectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	ProjectileMesh->SetSimulatePhysics(true); // Enable physics for movement
	ProjectileMesh->SetNotifyRigidBodyCollision(true); // Enable hit events
	RootComponent = ProjectileMesh;

}

// Called when the game starts or when spawned
void ABP_Projectile::BeginPlay()
{
	Super::BeginPlay();

	//ProjectileMesh->OnComponentHit.AddDynamic(this, &ABP_Projectile::OnHit);
	
}

// Called every frame
void ABP_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//void ABP_Projectile::FireInDirection(const FVector& ShootDirection)
//{
//	// Set the initial velocity of the projectile
//	ProjectileMesh->SetPhysicsLinearVelocity(ShootDirection * ProjectileSpeed);
//}
//
//void ABP_Projectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
//{
//	// Handle impact logic here, such as applying damage or spawning effects
//	// For example:
//	//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.Location);
//	//Destroy(); // Destroy the projectile after impact


