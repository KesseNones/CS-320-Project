// Fill out your copyright notice in the Description page of Project Settings.


#include "RightPaddlePawn.h"

// Sets default values
ARightPaddlePawn::ARightPaddlePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARightPaddlePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARightPaddlePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Update position of paddle based on current velocity
	if (!CurrentVelocity.IsZero()) {
		FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
		SetActorLocation(NewLocation);
	}
}

// Called to bind functionality to input
void ARightPaddlePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// Set current velocity of paddle
void ARightPaddlePawn::SendRightPaddleMove(float Value) {
	CurrentVelocity.Y = FMath::Clamp(Value, -1.0f, 1.0f) * velocityMultiplier;
}