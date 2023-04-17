/*
	Benjamin Brickner's Ball Header File
	Contains variables to modify the ball behavior 
	All Rights Reserved
*/

#pragma once

#include "UObject/ConstructorHelpers.h"
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
	float initSpeed = 6000.0f;
	float curving = 0.0f;
	float curve_multiplier = 40.0f;

	bool bDidHit, bDidHitTop, bDidHitBottom, enableRandom, isIncreasingSpeed;
	FHitResult TraceResult, upResult, downResult;
	FCollisionQueryParams TraceParams;
	AActor* paddleActor;
	TArray<AActor*> OverlappingComponents;
	UStaticMeshComponent* texture;

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

	AActor* getPaddleHit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
		

};
