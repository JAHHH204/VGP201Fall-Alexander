// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelGameMode.h"

ALevelGameMode::ALevelGameMode() {
	DefaultPawnClass = APawn::StaticClass();
}

void ALevelGameMode::BeginPlay() {
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Game Started with GameMode: %s"), *GetName());
}