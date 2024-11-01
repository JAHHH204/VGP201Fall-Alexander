// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BP_Gun.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class VGP201FPSSTARTER_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
	class USceneComponent* GunOffsetTransformComponent;

protected:
	UPROPERTY(EditAnywhere)
	class UCameraComponent* CameraComponent;


	//UPROPERTY(EditAnywhere)
	//class UCameraComponent* CameraComponent;

	void MoveForward(float InputVector); //input for forward vector
	void MoveRight(float InputVector);	//input for right vector

	void LookRight(float InputVector);	//input for looking up/down
	void LookUp(float InputVector);	//input for looking left/right

	void Shoot();
	void Crouch();
	void ReadyWeapon();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float DefaultWalkSpeed = 600.0f; // Normal walking speed

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float SprintSpeed = 1200.0f; // Sprinting speed

	UPROPERTY(EditAnywhere, Category = "Weapon")
	ABP_Gun* EquippedGun;
	
	void SprintStart();
	void SprintStop();
};
