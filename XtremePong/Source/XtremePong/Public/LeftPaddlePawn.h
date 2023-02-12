// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PaddleControlInterface.h"
#include "Kismet/GameplayStatics.h"
#include "RightPaddlePawn.h"
#include "LeftPaddlePawn.generated.h"

UCLASS()
class XTREMEPONG_API ALeftPaddlePawn : public APawn, public IPaddleControlInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ALeftPaddlePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	virtual void SendRightPaddleMove(float Value) override;

	void LeftPaddleMove(float AxisValue);

	FVector CurrentVelocity;

	UPROPERTY(EditAnywhere)
		float velocityMultiplier = 500.0f;

};
