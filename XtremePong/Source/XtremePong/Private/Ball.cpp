// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"


// Sets default values
ABall::ABall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	//CollisionSphere->SetupAttachment(RootComponent);
	RootComponent = CollisionSphere;

	CollisionSphere->SetSimulatePhysics(true);
	CollisionSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionSphere->SetSphereRadius(BallSize);
	CollisionSphere->SetEnableGravity(false);

	CollisionSphere->SetCollisionProfileName(TEXT("BlockAllDynamic"));

	//Make the mesh texture
	UStaticMeshComponent* texture = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	texture->SetupAttachment(CollisionSphere);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> SphereMaterial(TEXT("Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));

	if (SphereMesh.Succeeded()) texture->SetStaticMesh(SphereMesh.Object);
	if (SphereMaterial.Succeeded()) texture->SetMaterial(0, SphereMaterial.Object);

	texture->SetWorldScale3D(FVector(0.2f));
	
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();

	//This is the initial velocity
	Velocity = FVector(Speed, 0.0f, 0.0f);

}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*
		This section sets ball vector direction at a constant speed per tick
	*/
	
	FVector NewLocation = GetActorLocation() + Velocity * DeltaTime;
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%f"), DeltaTime));

	SetActorLocation(NewLocation);

	// Define the origin and direction of the line trace
	FVector TraceStart = GetActorLocation();
	FVector TraceEnd = TraceStart + Velocity * DeltaTime*5;

	// Define the parameters of the line trace
	FCollisionQueryParams TraceParams;
	TraceParams.AddIgnoredActor(this);
	// Perform the line trace
	FHitResult TraceResult;
	bool bDidHit = GetWorld()->LineTraceSingleByChannel(TraceResult, TraceStart, TraceEnd, ECC_Visibility, TraceParams);

	FVector surface_normal = TraceResult.ImpactNormal;
	FVector Reflection = UKismetMathLibrary::GetReflectionVector(Velocity, surface_normal);

	//Check if the line trace hit an Actor
	if (bDidHit) {

		Reflection.Z = Velocity.Z; //Z doesn't change since we're in 2D only
		Velocity = Reflection;
	}
		
}

