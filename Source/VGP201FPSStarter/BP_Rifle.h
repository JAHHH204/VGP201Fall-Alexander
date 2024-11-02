// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BP_Gun.h"
#include "BP_Rifle.generated.h"

UCLASS()
class VGP201FPSSTARTER_API ABP_Rifle : public ABP_Gun
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABP_Rifle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};