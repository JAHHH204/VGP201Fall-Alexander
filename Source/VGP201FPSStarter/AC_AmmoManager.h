#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AC_AmmoManager.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class VGP201FPSSTARTER_API UAC_AmmoManager : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAC_AmmoManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Ammo properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	int32 MaxAmmo;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ammo")
	int32 CurrentAmmo;

	// Refill ammo to max
	UFUNCTION(BlueprintCallable, Category = "Ammo")
	void RefillAmmo(int32 Amount);

	// Decrease ammo by a certain amount
	UFUNCTION(BlueprintCallable, Category = "Ammo")
	void DecreaseAmmo(int32 Amount);

	// Check if the player has ammo
	UFUNCTION(BlueprintCallable, Category = "Ammo")
	bool HasAmmo() const;
};
