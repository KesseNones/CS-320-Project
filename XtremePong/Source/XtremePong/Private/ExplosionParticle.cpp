//Jesse A. Jones
//13 Apr, 2023
//Explosion Particle Class

#include "ExplosionParticle.h"

// Sets default values
AExplosionParticle::AExplosionParticle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	particleVelocity = FVector(0.0f, 0.0f, 0.0f);
	particleTickCount = 0;
	particleBody = CreateDefaultSubobject<USphereComponent>(TEXT("PARTICLE"));
	particleBody->SetEnableGravity(false);
	RootComponent = particleBody;

	particleTexture = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Meshy"));
	particleTexture->SetupAttachment(particleBody);

	UPrimitiveComponent* PrimitiveComponent = this->FindComponentByClass<UPrimitiveComponent>();							//POTENTIALLY USEFUL (DOESNT SEEM TO WORK)

	if (PrimitiveComponent){
		PrimitiveComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> SphereMaterial(TEXT("Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));

	if (SphereMesh.Succeeded()) particleTexture->SetStaticMesh(SphereMesh.Object);
	if (SphereMaterial.Succeeded()) particleTexture->SetMaterial(0, SphereMaterial.Object);

	particleTexture->SetWorldScale3D(FVector(2.0f));

}

// Called when the game starts or when spawned
void AExplosionParticle::BeginPlay()
{
	Super::BeginPlay();
	originalParticleLocation = GetActorLocation();
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("COORDINATES SET TO: %f %f %f"), originalParticleLocation[0], originalParticleLocation[1], originalParticleLocation[2]));
	
}

// Called every frame
void AExplosionParticle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Original LOC: %f %f %f %d"), originalParticleLocation[0], originalParticleLocation[1], originalParticleLocation[2], particleTickCount));

	FVector newParticleLocation;

	newParticleLocation = FVector(
		(originalParticleLocation[0] + (particleVelocity[0] * particleTickCount)), 
		(originalParticleLocation[1] + (particleVelocity[1] * particleTickCount)), 
		(originalParticleLocation[2] + (particleVelocity[2] * particleTickCount)) );

	SetActorLocation(newParticleLocation);

	particleTickCount++;

}

void AExplosionParticle::setParticleVelocity(FVector newVelocity){
	particleVelocity = newVelocity;
}

