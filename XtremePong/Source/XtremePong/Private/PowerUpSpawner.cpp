// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUpSpawner.h"
#include "Components/BoxComponent.h"
#include "PowerUp.h"
#include <Kismet/KismetMathLibrary.h>

// Sets default values
APowerUpSpawner::APowerUpSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolume"));
	SpawnVolume->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	SpawnVolume->InitBoxExtent(BoxExtent);
}

// Called when the game starts or when spawned
void APowerUpSpawner::BeginPlay()
{
	Super::BeginPlay();

	// Call SpawnPowerUp every SpawnRate seconds
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &APowerUpSpawner::SpawnPowerUp, SpawnRate, true);
}

// Called every frame
void APowerUpSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APowerUpSpawner::SpawnPowerUp() {
	FVector SpawnLocation = UKismetMathLibrary::RandomPointInBoundingBox(GetActorLocation(), BoxExtent);
	FRotator SpawnRotation = GetActorRotation();

	GetWorld()->SpawnActor<APowerUp>(SpawnLocation, SpawnRotation);
}

float APowerUpSpawner::GetSpawnRate() {
	return SpawnRate;
}

FTimerHandle APowerUpSpawner::GetTimerHandle() {
	return SpawnTimerHandle;
}