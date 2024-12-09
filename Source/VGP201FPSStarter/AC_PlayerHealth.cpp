#include "AC_PlayerHealth.h"
#include "Blueprint/UserWidget.h"  // For creating widgets
#include "BP_LoseGameWidget.h"  // Include the header for your LoseGameWidget
#include "Kismet/GameplayStatics.h"  // For pausing the game

// Sets default values for this component's properties
UAC_PlayerHealth::UAC_PlayerHealth()
{
	PrimaryComponentTick.bCanEverTick = true;
	CurrentHealth = MaxHealth;
}

// Called when the game starts
void UAC_PlayerHealth::BeginPlay()
{
	Super::BeginPlay();

	// Create the Lose Game widget if it is set
	if (LoseGameWidgetClass)
	{
		LoseGameWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), LoseGameWidgetClass);
	}
}

// Called every frame
void UAC_PlayerHealth::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

// Method to handle taking damage
void UAC_PlayerHealth::TakeDamage(float DamageAmount)
{
	CurrentHealth -= DamageAmount;

	if (CurrentHealth <= 0.0f)
	{
		// Player is dead, display the LoseGameWidget
		UE_LOG(LogTemp, Warning, TEXT("Player has died!"));


			LoseGameWidgetInstance->AddToViewport();  // Add widget to viewport

			// Pause the game (optional, based on your design)
			UGameplayStatics::SetGamePaused(GetWorld(), true);
		
	}
}

// Method to check if the player is dead
bool UAC_PlayerHealth::IsDead() const
{
	return CurrentHealth <= 0.0f;
}
