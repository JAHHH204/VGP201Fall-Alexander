// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "LevelGameMode.generated.h"

/**
 * 
 */
UCLASS()
class VGP201FPSSTARTER_API ALevelGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ALevelGameMode(); //constructor

	virtual void BeginPlay() override; //game start logic

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite,category = "Game Rules")
	int32 MaxPlayers;
};
