// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BP_Projectile.generated.h"

UCLASS()
class VGP201FPSSTARTER_API ABP_Projectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABP_Projectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Function to initialize the projectile's velocity
	void FireInDirection(const FVector& ShootDirection);

	// Projectile movement component
	UPROPERTY(VisibleAnywhere, Category = "Movement")
	UStaticMeshComponent* ProjectileMesh;

	// Speed of the projectile
	UPROPERTY(EditAnywhere, Category = "Movement")
	float ProjectileSpeed = 3000.0f;

};
