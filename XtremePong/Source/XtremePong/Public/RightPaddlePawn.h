// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PaddleMovementComponent.h"
#include "PaddleControlInterface.h"
#include "RightPaddlePawn.generated.h"

UCLASS()
class XTREMEPONG_API ARightPaddlePawn : public APawn, public IPaddleControlInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ARightPaddlePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Moves right paddle based on input received from left paddle
	virtual void SendRightPaddleMove(float Value) override;

	// Override GetMovementComponent to so other classes can access the paddles' custom PaddleMovementComponent
	virtual UPawnMovementComponent* GetMovementComponent() const override;

	// Makes component visible in editor
	UPROPERTY(VisibleAnywhere)
		class UPaddleMovementComponent* PaddleMovementComponent;

};
