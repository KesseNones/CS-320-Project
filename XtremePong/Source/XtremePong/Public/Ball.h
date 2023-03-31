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

#include "LeftPaddlePawn.h"
#include "RightPaddlePawn.h"

#include "Ball.generated.h"

UCLASS()
class XTREMEPONG_API ABall : public AActor
{
	GENERATED_BODY()
	
private:	
	FVector Velocity;
	FVector Reflection;
	FVector surface_normal;
	float initSpeed = 5000.0f;

	bool bDidHit, enableRandom, isIncreasingSpeed;
	FHitResult TraceResult;
	FCollisionQueryParams TraceParams;
	AActor* paddleActor;

	/*	Other Actor Variables */
	FString LeftPaddle = "LeftPaddlePawn_2";	
	FString RightPaddle = "RightPaddlePawn_2";
	//AActor* paddleActor;							//Storing the information of the actor that was hit
	FString otherActorName;						//Storing the name of the actor hit by the ball

public:
	// Sets default values for this actor's properties
	ABall();

	virtual void Tick(float DeltaTime) override;

	//ball component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMeshComponent* ballMesh;

	UPROPERTY(VisibleAnywhere, Category = "Collision")
		USphereComponent* CollisionSphere;


	/*	Velocity Variables */
	UPROPERTY(EditAnywhere, Category = "BallSize")
		float BallSize = 10.0f;
	UPROPERTY(EditAnywhere)
		float BounceFactor = 1.1f;

	FVector onPaddleHit(FVector Reflection, FVector paddle_velocity);
	FVector setBallVelocityMultiplier(FVector curr_velocity,float speedMultiplier);
	void setBallVelocity(FVector newVelocity);
	FVector getBallVelocity();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

};
