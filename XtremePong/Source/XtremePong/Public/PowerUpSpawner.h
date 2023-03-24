// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PowerUpSpawner.generated.h"

UCLASS()
class XTREMEPONG_API APowerUpSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APowerUpSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		class UBoxComponent* SpawnVolume;

	UPROPERTY(EditAnywhere)
		FVector BoxExtent = FVector(1000.0f, 1000.0f, 1000.0f);

	FTimerHandle SpawnTimerHandle;

	// How many seconds between power up spawns
	UPROPERTY(EditAnywhere)
		float SpawnRate = 5.0f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SpawnPowerUp();

	float GetSpawnRate();

	FTimerHandle GetTimerHandle();

};
