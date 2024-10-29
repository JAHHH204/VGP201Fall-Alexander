// Fill out your copyright notice in the Description page of Project Settings.


#include "BP_Gun.h"
#include "Components/StaticMeshComponent.h"
//#include "Engine/World.h"
//#include "GameFramework/Actor.h"

// Sets default values
ABP_Gun::ABP_Gun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	staticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = staticMeshComponent;

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

void BPShoot() 
{
	//if (ProjectileClass)
	//{
	//	// Get the location and rotation of the muzzle or the gun's end
	//	FVector MuzzleLocation = staticMeshComponent->GetSocketLocation(FName("Muzzle"));
	//	FRotator MuzzleRotation = staticMeshComponent->GetSocketRotation(FName("Muzzle"));

	//	// Spawn the projectile at the muzzle
	//	FActorSpawnParameters SpawnParams;
	//	SpawnParams.Owner = this;
	//	SpawnParams.Instigator = GetInstigator();

	//	// Spawn the projectile
	//	AActor* Projectile = GetWorld()->SpawnActor<AActor>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);

	//	if (Projectile)
	//	{
	//		// Set the projectile's initial velocity
	//		UStaticMeshComponent* ProjectileMesh = Cast<UStaticMeshComponent>(Projectile->GetComponentByClass(UStaticMeshComponent::StaticClass()));
	//		if (ProjectileMesh)
	//		{
	//			FVector LaunchDirection = MuzzleRotation.Vector();
	//			ProjectileMesh->SetPhysicsLinearVelocity(LaunchDirection * BulletSpeed);
	//		}
	//	}
	//}
}

