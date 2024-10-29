// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BP_Gun.generated.h"

UCLASS()
class VGP201FPSSTARTER_API ABP_Gun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABP_Gun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* staticMeshComponent;

	//// Projectile class to spawn
	//UPROPERTY(EditAnywhere, Category = "Shooting")
	//TSubclassOf<AActor> ProjectileClass;

	//// Bullet speed
	//UPROPERTY(EditAnywhere, Category = "Shooting")
	//float BulletSpeed = 3000.0f;


protected:


	void BPShoot();

};
