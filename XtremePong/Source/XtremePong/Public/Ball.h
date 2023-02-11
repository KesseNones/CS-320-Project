// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/EngineTypes.h"
#include "Ball.generated.h"


UCLASS()
class XTREMEPONG_API ABall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABall();

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Mesh")
	//initialize static mesh component
	
		//UStaticMeshComponent* StaticMesh;

	//ball component
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ballMesh;

	UPROPERTY(VisibleAnywhere, Category = "Collision")
		class USphereComponent* CollisionSphere;

	UPROPERTY(EditAnywhere)
		float Speed = 500.0f;

	UPROPERTY(EditAnywhere)
		float BounceFactor = 1.2f;

	FVector Velocity;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	

};
