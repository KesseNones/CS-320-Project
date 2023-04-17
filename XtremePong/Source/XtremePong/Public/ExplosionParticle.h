//Jesse A. Jones
//13 Apr, 2023
//Explosion Particle Class

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h" //SUSSY
#include "UObject/ConstructorHelpers.h"
#include "Engine/Classes/Components/PrimitiveComponent.h"

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
	
	//Used to track particle location and velocity.
	FVector particleVelocity;
	FVector originalParticleLocation;

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

	//Sets the velocity of the particle to the velocity passed in.
	void setParticleVelocity(FVector newVelocity);

};
