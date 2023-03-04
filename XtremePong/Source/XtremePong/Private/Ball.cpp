// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"


// Sets default values
ABall::ABall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));

	RootComponent = CollisionSphere;

	CollisionSphere->SetSimulatePhysics(true);
	CollisionSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionSphere->SetSphereRadius(BallSize);
	CollisionSphere->SetEnableGravity(false);
	CollisionSphere->SetMassOverrideInKg(NAME_None, 30.0f, true);

	CollisionSphere->SetCollisionProfileName(TEXT("BlockAllDynamic"));

	//Make the mesh texture
	UStaticMeshComponent* texture = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	texture->SetupAttachment(CollisionSphere);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> SphereMaterial(TEXT("Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));

	if (SphereMesh.Succeeded()) texture->SetStaticMesh(SphereMesh.Object);
	//if (SphereMaterial.Succeeded()) texture->SetMaterial(0, SphereMaterial.Object);

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
	FVector TraceEnd;


	/*
		This section sets ball vector direction at a constant speed per tick
	*/
	
	FVector NewLocation = GetActorLocation() + Velocity * DeltaTime;
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%f"), DeltaTime));

	SetActorLocation(NewLocation);

	TraceEnd = GetActorLocation() + Velocity * DeltaTime * 5;
	
	TraceParams.AddIgnoredActor(this);
	// Perform the line trace

	bDidHit = GetWorld()->LineTraceSingleByChannel(TraceResult, GetActorLocation(), TraceEnd, ECC_Visibility, TraceParams);

	surface_normal = TraceResult.ImpactNormal;
	Reflection = UKismetMathLibrary::GetReflectionVector(Velocity, surface_normal);

	//Check if the line trace hit an Actor
	if (bDidHit) {
		AActor* paddleActor = TraceResult.GetActor();

		Reflection.Z = Velocity.Z; //Z doesn't change since we're in 2D only
		
		otherActorName = paddleActor->GetName();

		if ((*otherActorName == LeftPaddle) || (*otherActorName == RightPaddle)) 
			Velocity = onPaddleHit(Reflection,paddleActor);
		else
			Velocity = Reflection; //Bouncing off any actor that's not the
	}
}

FVector ABall::onPaddleHit(FVector curr_reflect, AActor* paddleActor)
{
	APawn* paddle = (APawn*) paddleActor;
	FVector paddle_vector = paddle->GetLastMovementInputVector();

	//get the random float to hit at a random angle back
	float random_angle_hit = UKismetMathLibrary::RandomFloatInRange(1000.0f, 4000.0f);

	//adjust the angle of the vector in respect to Y
	FVector newVector;
	newVector.X = curr_reflect.X;
	newVector.Y = curr_reflect.Y + (paddle_vector.Y * random_angle_hit);
	newVector.Z = curr_reflect.Z; 

	return newVector;
}
