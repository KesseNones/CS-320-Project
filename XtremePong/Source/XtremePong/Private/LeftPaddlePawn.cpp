// Fill out your copyright notice in the Description page of Project Settings.


#include "LeftPaddlePawn.h"

// Sets default values
ALeftPaddlePawn::ALeftPaddlePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void ALeftPaddlePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALeftPaddlePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Set position of left paddle based on current velocity
	if (!CurrentVelocity.IsZero()) {
		FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
		SetActorLocation(NewLocation);
	}
}

// Called to bind functionality to input
void ALeftPaddlePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind inputs to move methods
	InputComponent->BindAxis("LeftPaddleMove", this, &ALeftPaddlePawn::LeftPaddleMove);
	InputComponent->BindAxis("RightPaddleMove", this, &ALeftPaddlePawn::SendRightPaddleMove);
}

// Set current velocity of the left paddle
void ALeftPaddlePawn::LeftPaddleMove(float AxisValue) {
	CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f) * velocityMultiplier;
}

// Send input to the right paddle
void ALeftPaddlePawn::SendRightPaddleMove(float Value) {
	TArray<ARightPaddlePawn*> RightPaddlePawns;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARightPaddlePawn::StaticClass(), (TArray<AActor*> &)RightPaddlePawns);
	for (ARightPaddlePawn* RightPaddle : RightPaddlePawns) {
		RightPaddle->SendRightPaddleMove(Value);
	}
}