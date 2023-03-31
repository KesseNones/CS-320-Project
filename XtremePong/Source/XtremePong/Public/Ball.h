// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/EngineTypes.h"
#include "Engine/StaticMesh.h"
#include "Kismet/KismetMathLibrary.h"

#include "Ball.generated.h"


UCLASS()
class XTREMEPONG_API ABall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABall();

	virtual void Tick(float DeltaTime) override;

	//ball component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* ballMesh;

	UPROPERTY(VisibleAnywhere, Category = "Collision")
	USphereComponent* CollisionSphere;
	UPROPERTY(EditAnywhere, Category = "BallSize")
		float BallSize = 10.0f;
	

	UPROPERTY(EditAnywhere)
		float BounceFactor = 1.2f;

	FVector Velocity;
	float Speed = 5000.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

};
