//Jesse A. Jones
//14 Apr, 2023
//Explosion Class

#include "Explosion.h"
#include "ExplosionParticle.h"

// Sets default values
AExplosion::AExplosion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	localExplosionTickCount = 0;

	isExploding = true;

	//Loads explosion sound.
	explosionSound = LoadObject<USoundBase>(nullptr, TEXT("/Game/GameSounds/ballExplosionVersion1"));

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
	localExplosionTickCount++;

	if (localExplosionTickCount % 360 == 0){

		//Destroys all explosion particles.
		for (int i = 0; i < PARTICLE_COUNT; i++){
			GetWorld()->DestroyActor(particleArr[i]);
		}
		GetWorld()->DestroyActor(this);
		isExploding = false;
	}

}

void AExplosion::explode(FVector explosionCoordinates){
	//Plays explosion sound when explosion occurs.
	UGameplayStatics::PlaySound2D(this, explosionSound);

	//Used for creating an explosion particle circle.
	float tau = 6.2831853f;
	float frac;
	float fracDenom = PARTICLE_COUNT;
	float velMult = 20.0f;

	FRotator splodeRot = FRotator(0.0f, 0.0f, 0.0f);

	//Creates all explosion particles.
	for (int i = 0; i < PARTICLE_COUNT; i++){
		frac = i / fracDenom;
		particleArr[i] = GetWorld()->SpawnActor<AExplosionParticle>(explosionCoordinates, splodeRot);
		particleArr[i]->setParticleVelocity(FVector((velMult * cos(frac * tau)), (velMult * sin(frac * tau)), 0.0f));
	}

}