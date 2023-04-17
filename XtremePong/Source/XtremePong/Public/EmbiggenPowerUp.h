#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PowerUp.h"
#include "EmbiggenPowerUp.generated.h"

UCLASS()
class XTREMEPONG_API AEmbiggenPowerUp : public APowerUp
{
	GENERATED_BODY()

	
public:	
	// Sets default values for this actor's properties
	AEmbiggenPowerUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void ActivatePower(AActor* Paddle) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
