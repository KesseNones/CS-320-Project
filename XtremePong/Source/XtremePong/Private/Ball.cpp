// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"
#include "Engine/StaticMesh.h"
#include "Components/StaticMeshComponent.h"



// Sets default values
ABall::ABall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//this will make the mesh for the ball and initalize it as default
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));

	StaticMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshAsset(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
	if (StaticMeshAsset.Succeeded())
	{
		StaticMesh->SetStaticMesh(StaticMeshAsset.Object);
	}

	//seting properties for mesh
	StaticMesh->SetRelativeLocation(FVector(0.0f, -650.0f, 170.0f));
	StaticMesh->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	StaticMesh->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));

	//setting collision to be true
	StaticMesh->SetGenerateOverlapEvents(true);
	StaticMesh->SetCollisionProfileName(UCollisionProfile::BlockAllDynamic_ProfileName);
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();



}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*
	*		This part makes the ball move at a constant velocity and probably bounces off the wall 
	*/

	//Moves ball at constant velocity
	FVector Movement = FVector(0.0f, 250.0f, 0.0f) * DeltaTime;
	AddActorWorldOffset(Movement, true);

	//Checks collisions with wall (but technically it avoids anything when it goes near it)
	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	if (GetWorld()->SweepSingleByChannel(HitResult, GetActorLocation(), GetActorLocation() + Movement, FQuat::Identity, ECC_Visibility, FCollisionShape::MakeSphere(50.0f), CollisionParams))
	{
		// Reflect the velocity about the normal of the hit surface
		FVector Reflect = FVector::VectorPlaneProject(Movement, HitResult.Normal);
		Reflect = Movement - 2.0f * Reflect;
		Movement = Reflect;

		// Update the Actor's location
		AddActorWorldOffset(-Movement, true);
	}
}

