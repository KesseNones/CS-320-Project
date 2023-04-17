// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUp.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Ball.h"

// Sets default values
APowerUp::APowerUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Creating default components
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneComponent"));
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	ParticleComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));

	//Attaching components and setting physics
	SphereComp->SetupAttachment(RootComponent);
	SphereComp->SetSimulatePhysics(false);
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComp->SetEnableGravity(false);
	SphereComp->SetCollisionProfileName(TEXT("OverlapAll"));

	StaticMeshComp->AttachToComponent(SphereComp, FAttachmentTransformRules::KeepRelativeTransform);
	ParticleComp->AttachToComponent(StaticMeshComp, FAttachmentTransformRules::KeepRelativeTransform);

	// Set texture and scale of visual mesh
	ConstructorHelpers::FObjectFinder<UStaticMesh>SphereMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	StaticMeshComp->SetStaticMesh(SphereMeshAsset.Object);
	StaticMeshComp->SetRelativeScale3D(FVector(0.6f, 0.6f, 0.6f));

	SphereComp->SetRelativeScale3D(FVector(10.0f, 10.0f, 10.0f));
}

// Called when the game starts or when spawned
void APowerUp::BeginPlay()
{
	Super::BeginPlay();
	this->SetLifeSpan(10);	// Power up should despawn after so many seconds
}

// Called every frame
void APowerUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Get the ball that overlaps this power up, then get the last paddle it hit
	TArray<ABall*> Balls;
	this->GetOverlappingActors((TArray<AActor *> &) Balls, ABall::StaticClass());
	if (!Balls.IsEmpty()) {
		HitObject = Balls[0]->getPaddleHit();

		// If a paddle last hit the ball before it overlapped the PowerUp,
		// give that paddle the power.
		if (HitObject->GetClass() == ALeftPaddlePawn::StaticClass() || HitObject->GetClass() == ARightPaddlePawn::StaticClass()) {
			ActivatePower(HitObject);
		}
	}	
}

void APowerUp::ActivatePower(AActor* Paddle) {}