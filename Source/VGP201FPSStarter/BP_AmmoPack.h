#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BP_AmmoPack.generated.h"

// Forward declaration of the player character and ammo manager
class APlayerCharacter;
class UAmmoManager;

UCLASS()
class VGP201FPSSTARTER_API ABP_AmmoPack : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABP_AmmoPack();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Collision component to detect player overlap
	UPROPERTY(VisibleAnywhere)
	class UCapsuleComponent* AmmoPackCollision;

	// Amount of ammo this pack refills
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	int32 AmmoPackAmount = 50;

	// Function to handle overlap logic
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
