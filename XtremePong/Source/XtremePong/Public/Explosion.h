//Jesse A. Jones
//14 Apr, 2023
//Explosion Class

#pragma once

#include "CoreMinimal.h"
#include "ExplosionParticle.h"
#include "GameFramework/Actor.h"
#include "Engine/EngineTypes.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include <cmath>
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"

#include "Explosion.generated.h"

#define PARTICLE_COUNT 72

UCLASS()
class XTREMEPONG_API AExplosion : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExplosion();

	AExplosionParticle *particleArr[PARTICLE_COUNT];
	int localExplosionTickCount;
	bool isExploding;

	USoundBase* explosionSound;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Generates an explosion at the desired coordiantes.
	void explode(FVector explosionCoordinates);

};
