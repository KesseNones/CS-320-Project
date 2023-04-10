//Jesse A. Jones
//9 Apr, 2023
//Explosion Particle Class

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

#include "Engine/EngineTypes.h"
#include "Engine/Engine.h"
#include "Engine/World.h"

#include "ExplosionParticle.generated.h"


UCLASS()
class XTREMEPONG_API AExplosionParticle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExplosionParticle();
	
	FVector particleVelocity;

	int particleTickCount;

	UPROPERTY(VisibleAnywhere, Category = "Body")
		USphereComponent* particleBody;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMeshComponent* particleTexture;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
