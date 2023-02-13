// Fill out your copyright notice in the Description page of Project Settings.


#include "RightPaddlePawn.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/BoxComponent.h"

// Sets default values
ARightPaddlePawn::ARightPaddlePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Make root component a box that reacts to physics
	UBoxComponent* BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("RootComponent"));
	RootComponent = BoxComponent;
	BoxComponent->InitBoxExtent(FVector(200.0f, 900.0f, 900.0f));
	BoxComponent->SetCollisionProfileName(TEXT("BlockAllDynamic"));

	// Create instance of movement component and tell it to update the root
	PaddleMovementComponent = CreateDefaultSubobject<UPaddleMovementComponent>(TEXT("PaddleMovementComponent"));
	PaddleMovementComponent->UpdatedComponent = RootComponent;

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

}

// Called to bind functionality to input
void ARightPaddlePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// Set current velocity of paddle
void ARightPaddlePawn::SendRightPaddleMove(float Value) {

	// Gives the movement component a vector to act upon
	if (PaddleMovementComponent && (PaddleMovementComponent->UpdatedComponent == RootComponent)) {
		PaddleMovementComponent->AddInputVector(GetActorRightVector() * Value);
	}
}

UPawnMovementComponent* ARightPaddlePawn::GetMovementComponent() const {
	return PaddleMovementComponent;
}