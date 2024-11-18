// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BP_Gun.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	CameraComponent->SetupAttachment(RootComponent);
	CameraComponent->bUsePawnControlRotation = true;

	GunOffsetTransformComponent = CreateDefaultSubobject<USceneComponent>(TEXT("GunOffsetTransformComponent"));
	GunOffsetTransformComponent->SetupAttachment(CameraComponent);

	// Initialize the health component
	PlayerHealthComponent = CreateDefaultSubobject<UAC_PlayerHealth>(TEXT("PlayerHealthComponent"));

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	PlayerInputComponent->BindAxis("LookRight", this, &APlayerCharacter::LookRight);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::LookUp);

	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &APlayerCharacter::Shoot);
	PlayerInputComponent->BindAction("ReadyWeapon", IE_Pressed, this, &APlayerCharacter::ReadyWeapon);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &APlayerCharacter::SprintStart);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &APlayerCharacter::SprintStop);
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &APlayerCharacter::Crouch);


}

void APlayerCharacter::MoveForward(float InputVector)
{
	FVector ForwardDirection = GetActorForwardVector();
	AddMovementInput(ForwardDirection, InputVector);
}

void APlayerCharacter::MoveRight(float InputVector)
{
	FVector RightDirection = GetActorRightVector();
	AddMovementInput(RightDirection, InputVector);
}

void APlayerCharacter::LookRight(float InputVector)
{
	AddControllerYawInput(InputVector);
}

void APlayerCharacter::LookUp(float InputVector)
{
	AddControllerPitchInput(InputVector);
}

void APlayerCharacter::Shoot()
{
	if (EquippedGun)
	{
		
		EquippedGun->BPShoot();
	}
	else
	{

		UE_LOG(LogTemp, Warning, TEXT("No weapon equipped!"));
	}
}

void APlayerCharacter::Crouch()
{


}

void APlayerCharacter::ReadyWeapon()
{


}

void APlayerCharacter::SprintStart()
{

	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	UE_LOG(LogTemp, Warning, TEXT("Sprint started"));
}

void APlayerCharacter::SprintStop()
{

	GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed;
	UE_LOG(LogTemp, Warning, TEXT("Sprint stopped"));
}

void APlayerCharacter::TakeDamage(float DamageAmount)
{
	if (PlayerHealthComponent)
	{
		PlayerHealthComponent->TakeDamage(DamageAmount);
		if (PlayerHealthComponent->IsDead())
		{
			// Handle death, e.g., trigger death animation or end the game
			//UE_LOG(LogTemp, Warning, TEXT("Player is dead!"));
		}
	}
}