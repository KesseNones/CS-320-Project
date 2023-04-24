//Jesse A. Jones
//22 Apr, 2023
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

	//Explicitly disables collision of explosion particle.
	UPrimitiveComponent* PrimitiveComponent = this->FindComponentByClass<UPrimitiveComponent>();
	if (PrimitiveComponent){
		PrimitiveComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	//Fundamental material components.
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> SphereMaterial(TEXT("Material'Game/explosion'"));
	if (SphereMesh.Succeeded()) particleTexture->SetStaticMesh(SphereMesh.Object);
	if (SphereMaterial.Succeeded()) particleTexture->SetMaterial(0, SphereMaterial.Object);


	//Sets particle material and size.
	//Credit for making explosion material:
	// https://www.youtube.com/watch?v=rkVOkFFYvIs 
	// ("Make Objects Glow With Emissive Materials - Unreal Engine 5 UE5 Free Tutorial")
	UMaterial* splosionLight = LoadObject<UMaterial>(nullptr, TEXT("/Game/explosion"));
	particleTexture->SetMaterial(0, splosionLight);
	particleTexture->SetWorldScale3D(FVector(2.0f));

}

// Called when the game starts or when spawned
void AExplosionParticle::BeginPlay()
{
	Super::BeginPlay();
	originalParticleLocation = GetActorLocation();
	
}

// Called every frame
void AExplosionParticle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

