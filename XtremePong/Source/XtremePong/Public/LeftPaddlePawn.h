// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PaddleMovementComponent.h"
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

	// Sends relevant input to right paddle
	virtual void SendRightPaddleMove(float Value) override;

	// Move left paddle based on input
	void LeftPaddleMove(float AxisValue);

	// Override GetMovementComponent so other classes can access the paddles' custom PaddleMovementComponent
	virtual UPawnMovementComponent* GetMovementComponent() const override;

	// Makes component visible in editor to access and change settings without needing recompile
	UPROPERTY(VisibleAnywhere)
		class UPaddleMovementComponent* PaddleMovementComponent;
};
