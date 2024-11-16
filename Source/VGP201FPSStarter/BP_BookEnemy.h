#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BP_BookEnemy.generated.h"

UCLASS()
class VGP201FPSSTARTER_API ABP_BookEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABP_BookEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;



	// Speed at which the enemy moves
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MoveSpeed = 200.0f;

	// Range for wandering (in Unreal units)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float Range = 300.0f;

	// Target location to wander towards
	FVector TargetLocation;

	// Function to set a new random target location
	void SetNewTargetLocation();
};
