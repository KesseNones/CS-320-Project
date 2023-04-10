//Jesse A. Jones
//9 Apr, 2023
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

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> SphereMaterial(TEXT("Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));

	if (SphereMesh.Succeeded()) particleTexture->SetStaticMesh(SphereMesh.Object);
	if (SphereMaterial.Succeeded()) particleTexture->SetMaterial(0, SphereMaterial.Object);

	particleTexture->SetWorldScale3D(FVector(20.0f));

}

// Called when the game starts or when spawned
void AExplosionParticle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AExplosionParticle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	particleTickCount++;

}

