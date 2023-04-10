//Jesse A. Jones
//9 Apr, 2023
//Explosion Class

#include "Explosion.h"
#include "ExplosionParticle.h"

// Sets default values
AExplosion::AExplosion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	localExplosionTickCount = 0;

}

// Called when the game starts or when spawned
void AExplosion::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AExplosion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AExplosion::explode(FVector explosionCoordinates){
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("BALL EXPLODES AT: %f %f %f"), explosionCoordinates[0], explosionCoordinates[1], explosionCoordinates[2]));
	FVector SplodeCoords = FVector(explosionCoordinates[0], explosionCoordinates[1], explosionCoordinates[2]);
	FRotator splodeRot = FRotator(0.0f, 0.0f, 0.0f);
	particleArr[0] = GetWorld()->SpawnActor<AExplosionParticle>(SplodeCoords, splodeRot);
	GetWorld()->DestroyActor(particleArr[0]);

}