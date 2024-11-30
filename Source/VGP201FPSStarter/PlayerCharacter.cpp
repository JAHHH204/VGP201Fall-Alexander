// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BP_Gun.h"
#include "BP_TomeBook.h"
#include "BP_TomeAltar.h"



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
	AmmoManager = CreateDefaultSubobject<UAC_AmmoManager>(TEXT("PlayerAmmoManager"));


}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	EquippedTome = nullptr;

	AmmoManager = FindComponentByClass<UAC_AmmoManager>();
	if (AmmoManager == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("AmmoManager not found on Player!"));

		AmmoManager = NewObject<UAC_AmmoManager>(this);
	}

	
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

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &APlayerCharacter::Interact);
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
		// Check ammo before shooting
		if (AmmoManager && AmmoManager->HasAmmo())
		{
			EquippedGun->BPShoot();
			AmmoManager->DecreaseAmmo(1);  // Decrease ammo by 1 after a shot
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Out of Ammo!"));
		}
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

void APlayerCharacter::CheckForNearbyBook()
{
	FVector Start = GetActorLocation();
	FVector End = Start + GetActorForwardVector() * 200.0f; // Adjust range

	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);  

	// line trace to detect the book
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, Params);

	if (bHit && HitResult.GetActor() && HitResult.GetActor()->IsA(ABP_TomeBook::StaticClass()))
	{
		NearbyBook = Cast<ABP_TomeBook>(HitResult.GetActor());
		UE_LOG(LogTemp, Warning, TEXT("Book Detected!"));
	}
	else
	{
		NearbyBook = nullptr; 
	}
}

// Pickup the book (hides or destroys it)
void APlayerCharacter::PickupBook()
{
	if (NearbyBook)
	{
		// Hide the book 
		NearbyBook->SetActorHiddenInGame(true);
		NearbyBook->SetActorEnableCollision(false);

		//  add the book to inventory here

		UE_LOG(LogTemp, Warning, TEXT("Picked up a book!"));
	}
}


void APlayerCharacter::PickUpTome(ABP_TomeBook* Tome)
{
    if (!Tome)
    {
        UE_LOG(LogTemp, Warning, TEXT("No tome to pick up!"));
        return;
    }

    if (EquippedTome)
    {
        UE_LOG(LogTemp, Warning, TEXT("Already holding a tome! Drop the current one first."));
        return;
    }

    EquippedTome = Tome;
    EquippedTome->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("RightHandSocket"));
    EquippedTome->SetActorEnableCollision(false);
    UE_LOG(LogTemp, Warning, TEXT("Picked up tome: %s"), *Tome->GetName());

    
}

void APlayerCharacter::Interact()
{
	if (!EquippedTome)
	{
		UE_LOG(LogTemp, Warning, TEXT("No tome equipped to place."));
		return;
	}

	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors, ABP_TomeAltar::StaticClass());

	for (AActor* Actor : OverlappingActors)
	{
		ABP_TomeAltar* Altar = Cast<ABP_TomeAltar>(Actor);
		if (Altar)
		{
			Altar->PlaceTome(nullptr, this, nullptr, 0, false, FHitResult());
			EquippedTome = nullptr; // Clear the equipped tome after placing it
			return;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("No altar found for interaction."));
}

bool APlayerCharacter::IsHoldingTome() const
{
	return EquippedTome != nullptr;
}