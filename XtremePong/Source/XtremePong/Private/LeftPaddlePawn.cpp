// Fill out your copyright notice in the Description page of Project Settings.


#include "LeftPaddlePawn.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/BoxComponent.h"

// Sets default values
ALeftPaddlePawn::ALeftPaddlePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Make root component a box that reacts to physics
	UBoxComponent* BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("RootComponent"));
	RootComponent = BoxComponent;
	BoxComponent->InitBoxExtent(FVector(200.0f, 900.0f, 900.0f));	// Set bounds of box
	BoxComponent->SetCollisionProfileName(TEXT("BlockAllDynamic")); // Box can move (dynamic), and collides with everything

	// Create instance of movement component and tell it to update the root
	PaddleMovementComponent = CreateDefaultSubobject<UPaddleMovementComponent>(TEXT("PaddleMovementComponent"));
	PaddleMovementComponent->UpdatedComponent = RootComponent;
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

}

// Called to bind functionality to input
void ALeftPaddlePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind inputs to move functions
	InputComponent->BindAxis("LeftPaddleMove", this, &ALeftPaddlePawn::LeftPaddleMove);
	InputComponent->BindAxis("RightPaddleMove", this, &ALeftPaddlePawn::SendRightPaddleMove);
}


void ALeftPaddlePawn::LeftPaddleMove(float AxisValue) {

	// Gives the movement component a vector to act upon
	if (PaddleMovementComponent && (PaddleMovementComponent->UpdatedComponent == RootComponent)) {
		PaddleMovementComponent->AddInputVector(GetActorRightVector() * AxisValue);
	}
}

// Send input to the right paddle
void ALeftPaddlePawn::SendRightPaddleMove(float Value) {
	TArray<ARightPaddlePawn*> RightPaddlePawns;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARightPaddlePawn::StaticClass(), (TArray<AActor*> &)RightPaddlePawns);
	for (ARightPaddlePawn* RightPaddle : RightPaddlePawns) {
		RightPaddle->SendRightPaddleMove(Value);
	}
}

UPawnMovementComponent* ALeftPaddlePawn::GetMovementComponent() const {
	return PaddleMovementComponent;
}