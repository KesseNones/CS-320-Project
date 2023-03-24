// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UObject/ConstructorHelpers.h"
#include "PowerUp.generated.h"

UCLASS()
class XTREMEPONG_API APowerUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APowerUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		class USphereComponent* SphereComp;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditAnywhere)
		class UParticleSystemComponent* ParticleComp;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
