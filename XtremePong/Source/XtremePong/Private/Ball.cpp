// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"


// Sets default values
ABall::ABall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//this will make the mesh for the ball and initalize it as default
	ballMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ball"));
	ballMesh->SetupAttachment(RootComponent);

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionSphere->SetupAttachment(ballMesh);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshAsset(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
	if (StaticMeshAsset.Succeeded())
	{
		ballMesh->SetStaticMesh(StaticMeshAsset.Object);
	}

	//seting properties for ball static mesh
	ballMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	ballMesh->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	ballMesh->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));

	CollisionSphere->SetSimulatePhysics(true);
	CollisionSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionSphere->SetSphereRadius(10.0f);
	
	
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
	
	FVector NewLocation = GetActorLocation() + Velocity * DeltaTime;

	SetActorLocation(NewLocation);

	// Define the origin and direction of the line trace
	FVector TraceStart = GetActorLocation();
	FVector TraceEnd = TraceStart + FVector(Speed, 0.0f, 0.0f);


	// Define the parameters of the line trace
	FCollisionQueryParams TraceParams;
	TraceParams.AddIgnoredActor(this);

	// Perform the line trace
	bool bDidHit = GetWorld()->LineTraceSingleByChannel(TraceResult, TraceStart, TraceEnd, ECC_Visibility, TraceParams);

	// Check if the line trace hit an Actor
	if (bDidHit)
	{
		if (abs(Velocity.X) > maxSpeed) {
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Too fast!"));

			//bounce back but without the velocity increase
			Velocity = FVector(-Velocity.X, Velocity.Y, Velocity.Z);
		}
		else
		{
			//ball bounces but it goes faster
			Velocity = FVector(-Velocity.X * BounceFactor, Velocity.Y, Velocity.Z);
		}
		
	}
	else
	{
		//while it's not hitting
	}

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

