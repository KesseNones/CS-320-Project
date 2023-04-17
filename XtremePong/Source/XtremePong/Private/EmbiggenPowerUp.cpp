// Fill out your copyright notice in the Description page of Project Settings.


#include "EmbiggenPowerUp.h"

// Sets default values
AEmbiggenPowerUp::AEmbiggenPowerUp()
{
}

// Called when the game starts or when spawned
void AEmbiggenPowerUp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEmbiggenPowerUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Make the given hit object twice as large for 30 seconds
void AEmbiggenPowerUp::ActivatePower(AActor* Paddle) {
	
	Paddle->SetActorRelativeScale3D(Paddle->GetActorRelativeScale3D() * 2);

}