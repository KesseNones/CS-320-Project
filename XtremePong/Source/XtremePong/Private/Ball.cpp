// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Ball.h"
#include "Engine/StaticMesh.h"
#include "Engine/EngineTypes.h"
#include "Components/StaticMeshComponent.h"



// Sets default values
ABall::ABall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//Make a collision range instance
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionSphere->SetupAttachment(RootComponent);
	CollisionSphere->InitSphereRadius(5.0f);

	//this will make the mesh for the ball and initalize it as default
	ballMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ball"));
	ballMesh->SetupAttachment(CollisionSphere);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshAsset(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
	if (StaticMeshAsset.Succeeded())
	{
		ballMesh->SetStaticMesh(StaticMeshAsset.Object);
	}

	//seting properties for ball static mesh
	ballMesh->SetRelativeLocation(FVector(-830.0f, -120.0f, 230.0f));
	ballMesh->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	ballMesh->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));

	//setting collision stuff
	ballMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ballMesh->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	ballMesh->SetSimulatePhysics(true);
	ballMesh->SetEnableGravity(false);
	
	
	//StaticMesh->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();

	PrimaryActorTick.bCanEverTick = true;
	

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
	FVector Start = GetActorLocation();
	FVector End = Start + GetActorForwardVector() + 100.0f;

	SetActorLocation(Start + Velocity * DeltaTime);


	/* Setting up collision parameters and checking */
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	FHitResult HitResult;

	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams))
			Velocity = FVector(-Speed * BounceFactor, Velocity.Y, Velocity.Z);



	/*
	*		Some junk code that stops actor from going too far
	*/
	//if (GetActorLocation().X > 1000.0f || GetActorLocation().X < -1000.0f) 
	//{
	//	Velocity = FVector(-Velocity.X * BounceFactor, Velocity.Y, Velocity.Z);
	//}
	/*
	if (GetActorLocation().Y > 1000.0f || GetActorLocation().Y < -1000.0f)
	{
		Velocity = FVector(Velocity.X, -Velocity.Y * BounceFactor, Velocity.Z);
	}
	*/
}


