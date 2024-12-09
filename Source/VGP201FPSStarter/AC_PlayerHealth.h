#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Blueprint/UserWidget.h"
#include "BP_LoseGameWidget.h"  // Include the header for your lose widget

#include "AC_PlayerHealth.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class VGP201FPSSTARTER_API UAC_PlayerHealth : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAC_PlayerHealth();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Health variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth = 100.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	float CurrentHealth;

	// Reference to the Lose Game Widget
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> LoseGameWidgetClass;

	// Method to handle taking damage
	void TakeDamage(float DamageAmount);

	// Method to check if the player is dead
	bool IsDead() const;


private:


	// A reference to the widget instance
	UUserWidget* LoseGameWidgetInstance;
};
