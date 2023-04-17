/*
	Benjamin Brickner's Ball Code
	All Rights Reserved
*/


#include "Ball.h"
#include "PowerUp.h"


//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%f"), DeltaTime));
//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Your Message"));

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
	CollisionSphere->SetGenerateOverlapEvents(true);

	CollisionSphere->SetCollisionProfileName(TEXT("BlockAllDynamic"));

	CollisionSphere->SetCollisionObjectType(ECC_WorldDynamic);
	CollisionSphere->SetCollisionResponseToAllChannels(ECR_Ignore);

	//this detects overlap only with pawns
	CollisionSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	//Make the mesh texture
	texture = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	texture->SetupAttachment(CollisionSphere);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> SphereMaterial(TEXT("Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));

	if (SphereMesh.Succeeded()) texture->SetStaticMesh(SphereMesh.Object);
	if (SphereMaterial.Succeeded()) texture->SetMaterial(0, SphereMaterial.Object);

	texture->SetWorldScale3D(FVector(0.2f));

	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ABall::OnOverlapBegin);

	enableRandom = true;
	isIncreasingSpeed = false;
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();

	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ABall::OnOverlapBegin);

	//This is the initial velocity
	Velocity = FVector(initSpeed, 0.0f, 0.0f);

}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector TraceEnd, TraceTop, TraceBottom;

	/*
		This section sets ball vector direction at a constant speed per tick
	*/
	
	FVector NewLocation = GetActorLocation() + Velocity * DeltaTime;

	SetActorLocation(NewLocation);

	TraceEnd = GetActorLocation() + Velocity * DeltaTime;

	FVector up = UKismetMathLibrary::RotateAngleAxis(Velocity, -30.0f, FVector(0.0f, 0.0f, 1.0f));
	TraceTop = GetActorLocation() + up * DeltaTime * 2;

	FVector down = UKismetMathLibrary::RotateAngleAxis(Velocity, 30.0f, FVector(0.0f, 0.0f, 1.0f));
	TraceBottom = GetActorLocation() + down * DeltaTime * 2;

	TraceParams.AddIgnoredActor(this);

	bDidHit = GetWorld()->LineTraceSingleByChannel(TraceResult, GetActorLocation(), TraceEnd, ECC_Visibility, TraceParams);
	bDidHitTop = GetWorld()->LineTraceSingleByChannel(upResult, GetActorLocation(), TraceTop, ECC_Visibility, TraceParams);
	bDidHitBottom = GetWorld()->LineTraceSingleByChannel(downResult, GetActorLocation(), TraceBottom, ECC_Visibility, TraceParams);

	surface_normal = TraceResult.ImpactNormal;
	Reflection = UKismetMathLibrary::GetReflectionVector(Velocity, surface_normal);

	//Check if the line trace hit an Actor
	
	if (bDidHit || bDidHitTop || bDidHitBottom) {
		Reflection.Z = Velocity.Z; //Z doesn't change since we're in 2D only

		//checking angles and getting the actor from whichever 
		if (bDidHit) paddleActor = TraceResult.GetActor();
		else if (bDidHitTop) paddleActor = upResult.GetActor();
		else paddleActor = downResult.GetActor();

		otherActorName = paddleActor->GetName();
		
		if ((*otherActorName == LeftPaddle) || (*otherActorName == RightPaddle))
		{
			APawn* paddle = (APawn*)paddleActor;
			FVector paddle_vector = paddle->GetLastMovementInputVector();
			curving = paddle_vector.Y * curve_multiplier * -1;
			Velocity = onPaddleHit(Reflection, paddle_vector);
		}
		else
		{
			Velocity = Reflection; //Bouncing off any actor that's not the
			curving = curving / 2;		//reset curve
		}
	}
	/*
	*		Adding curve to the ball. 
	*	If the paddle curved the ball, the "curving" variable will be +- 1 
	*	If the ball was hit by the wall, the "curving" variable will reset to 0 
	*/
	Velocity.Y = Velocity.Y + curving;	
	
}

void ABall::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Collision detected"));
}


FVector ABall::setBallVelocityMultiplier(FVector curr_velocity,float speedMultiplier)
{
	FVector newVector = curr_velocity * abs(speedMultiplier);
	return newVector;
}


/*		setter and getter
*	gets the ball velocity and sets the ball velocity 
*	since ball velocity is private in the header file 
*/

void ABall::setBallVelocity(FVector newVelocity)
{
	Velocity = newVelocity;
}

FVector ABall::getBallVelocity()
{
	return Velocity;
}

FVector ABall::onPaddleHit(FVector curr_reflect, FVector paddle_vector)
{
	FVector increaseVector = FVector(0.0f, 0.0f, 0.0f);
	FVector newVector;
	float random_angle_hit = 2000.0f;
	//get the random float to hit at a random angle back
	if (enableRandom) random_angle_hit = UKismetMathLibrary::RandomFloatInRange(100.0f, 1000.0f);

	newVector.X = curr_reflect.X;

	if (paddle_vector.Y != 0.0f)
		//adjust new Y velocity if paddle was moving 
		newVector.Y = curr_reflect.Y + (paddle_vector.Y * random_angle_hit);
	else
		//ball straightens out if paddle was not moving
		newVector.Y = curr_reflect.Y / 1.5f;

	newVector.Z = curr_reflect.Z;

	//adjust the angle of the vector in respect to Y
	if (isIncreasingSpeed) {
		if (abs(curr_reflect.X) < 20000.0f)
		{
			increaseVector = setBallVelocityMultiplier(newVector, 1.2f);
			return increaseVector;
		}
	}
	return newVector;
}

// Returns the last paddle the ball hit
AActor* ABall::getPaddleHit() {
	return paddleActor;
}