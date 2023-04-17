

#include "Tests/AutomationCommon.h"
#include "Tests/AutomationEditorCommon.h"
#include "Misc/AutomationTest.h"

#include "LeftPaddlePawn.h"
#include "RightPaddlePawn.h"
#include "PowerUp.h"
#include "PowerUpSpawner.h"
#include "PaddleMovementComponent.h"
#include "Math/BoxSphereBounds.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "UObject/Object.h"

#if WITH_DEV_AUTOMATION_TESTS

// Test 1 - Acceptance Test: Ensure LeftPaddlePawns spawn with the correct values/components
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FInitLeftPaddleTest, "InitLeftPaddle",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FInitLeftPaddleTest::RunTest(FString const& Parameters) {
	
	// Create a world and spawn a LeftPaddlePawn in it
	UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();
	ALeftPaddlePawn* LeftPaddlePawn = World->SpawnActor<ALeftPaddlePawn>();

	TestTrue("LeftPaddlePawn can tick", LeftPaddlePawn->PrimaryActorTick.bCanEverTick);

	// Check that root component is valid and is of correct type
	TestTrue("LeftPaddlePawn has valid root component", LeftPaddlePawn->HasValidRootComponent());
	USceneComponent* RootComp = LeftPaddlePawn->GetRootComponent();
	TestEqual("LeftPaddlePawn's root component is a BoxComponent", RootComp->GetClass()->GetName(), "BoxComponent");

	// Check collision box extents
	FVector RootExtent = RootComp->GetPlacementExtent().BoxExtent;
	TestEqual("LeftPaddlePawn's collision box extent is correct", RootExtent, FVector(200.0f, 900.0f, 900.0f));

	// Check collisions are set up correctly
	TestTrue("LeftPaddlePawn has collision enabled", RootComp->IsCollisionEnabled());
	TestEqual("LeftPaddlePawn is a WorldDynamic collision object", RootComp->GetCollisionObjectType(), ECC_WorldDynamic);

	FCollisionResponseContainer RootCollision = RootComp->GetCollisionResponseToChannels();
	TestEqual("LeftPaddlePawn blocks Cameras", RootCollision.GetResponse(ECC_Camera), ECR_Block);
	TestEqual("LeftPaddlePawn blocks Destructibles", RootCollision.GetResponse(ECC_Destructible), ECR_Block);
	TestEqual("LeftPaddlePawn blocks Pawns", RootCollision.GetResponse(ECC_Pawn), ECR_Block);
	TestEqual("LeftPaddlePawn blocks Physics Bodies", RootCollision.GetResponse(ECC_PhysicsBody), ECR_Block);
	TestEqual("LeftPaddlePawn blocks Vehicles", RootCollision.GetResponse(ECC_Vehicle), ECR_Block);
	TestEqual("LeftPaddlePawn blocks Visibility", RootCollision.GetResponse(ECC_Visibility), ECR_Block);
	TestEqual("LeftPaddlePawn blocks WorldDynamics", RootCollision.GetResponse(ECC_WorldDynamic), ECR_Block);
	TestEqual("LeftPaddlePawn blocks WorldStatics", RootCollision.GetResponse(ECC_WorldStatic), ECR_Block);

	// Check movement component is set up correctly
	UPawnMovementComponent* PaddleMovementComp = LeftPaddlePawn->GetMovementComponent();
	TestEqual("LeftPaddlePawn movement component is a PaddleMovement Component", PaddleMovementComp->GetName(), "PaddleMovementComponent");
	TestEqual("PaddleMovementComponent UpdatedComponent is LeftPaddlePawn root component", (USceneComponent*)PaddleMovementComp->UpdatedComponent, RootComp);
	
	LeftPaddlePawn->Destroy();
	return true;
}


//Test 2 - Acceptance Test: Ensure RightPaddlePawns spawn with the correct values/components
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FInitRightPaddleTest, "InitRightPaddle",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FInitRightPaddleTest::RunTest(FString const& Parameters) {
	
	// Create a world and spawn a RightPaddlePawn in it
	UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();
	ARightPaddlePawn* RightPaddlePawn = World->SpawnActor<ARightPaddlePawn>();
	
	// Check that root compoennt is valid and of the correct type
	TestTrue("RightPaddlePawn has valid root component", RightPaddlePawn->HasValidRootComponent());
	USceneComponent* RootComp = RightPaddlePawn->GetRootComponent();
	TestEqual("RightPaddlePawn's root component is a BoxComponent", RootComp->GetClass()->GetName(), "BoxComponent");
	UBoxComponent* BoxRootComp = (UBoxComponent*)RootComp;
	
	// Check collisions are set up correctly
	TestEqual("RightPaddlePawn's collision box extent is correct", BoxRootComp->GetUnscaledBoxExtent(), FVector(200.0f, 900.0f, 900.0f));
	TestTrue("RightPaddlePawn has collision enabled", BoxRootComp->IsCollisionEnabled());
	TestEqual("RightPaddlePawn is a WorldDynamic collision object", BoxRootComp->GetCollisionObjectType(), ECC_WorldDynamic);
	TestEqual("RightPaddlePawn blocks everything", BoxRootComp->GetCollisionProfileName(), FName(TEXT("BlockAllDynamic")));
	
	// Check movement component is set up correctly
	UPawnMovementComponent* PaddleMovementComp = RightPaddlePawn->GetMovementComponent();
	TestEqual("RightPaddlePawn movement component is a PaddleMovementComponent", PaddleMovementComp->GetName(), "PaddleMovementComponent");
	TestEqual("PaddleMovementComponent's UpdatedComponent is RightPaddlePawn's root component", (USceneComponent*)PaddleMovementComp->UpdatedComponent, RootComp);
	
	RightPaddlePawn->Destroy();
	return true;
}


// Test 3 - Acceptance Test: Ensure PowerUps spawn with the correct values/components
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FInitPowerUpTest, "InitPowerUp",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FInitPowerUpTest::RunTest(FString const& Parameters) {
	
	// Create a new world and spawn a PowerUp in it
	UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();
	APowerUp* PowerUp = World->SpawnActor<APowerUp>();

	TestTrue("PowerUp can tick", PowerUp->PrimaryActorTick.bCanEverTick);

	// Check for valid root and child components
	TestTrue("PowerUp has a valid root component", PowerUp->HasValidRootComponent());
	USceneComponent* RootComp = PowerUp->GetRootComponent();

	USceneComponent* FirstChild = RootComp->GetChildComponent(0);
	TestEqual("First child component is a Sphere", FirstChild->GetClass()->GetName(), "SphereComponent");
	USphereComponent* SphereComp = (USphereComponent*)FirstChild;

	USceneComponent* SecondChild = FirstChild->GetChildComponent(0);
	TestEqual("Second child component is a Static Mesh", SecondChild->GetClass()->GetName(), "StaticMeshComponent");
	UStaticMeshComponent* StaticMeshComp = (UStaticMeshComponent*)SecondChild;

	USceneComponent* ThirdChild = SecondChild->GetChildComponent(0);
	TestEqual("Third child component is a Particle System", ThirdChild->GetClass()->GetName(), "ParticleSystemComponent");

	// Check that the first child, Sphere, has correct values
	TestTrue("Sphere is simulating physics", SphereComp->IsSimulatingPhysics());
	TestTrue("Sphere has collisions", SphereComp->IsCollisionEnabled());
	TestFalse("Sphere does not have gravity", SphereComp->IsGravityEnabled());
	TestEqual("Sphere overlaps everything", SphereComp->GetCollisionProfileName(), FName(TEXT("OverlapAll")));
	TestEqual("Sphere is correctly scaled", SphereComp->GetRelativeScale3D(), FVector(10.0f, 10.0f, 10.0f));
	
	// Check that the Static Mesh uses the right mesh and scaling
	TestEqual("Static Mesh uses a sphere mesh", *StaticMeshComp->GetStaticMesh()->GetPathName(), "/Engine/BasicShapes/Sphere.Sphere");
	TestEqual("Static Mesh is correctly scaled", StaticMeshComp->GetRelativeScale3D(), FVector(0.6f, 0.6f, 0.6f));

	PowerUp->Destroy();
	return true;
}


// Test 4 - Acceptance Test: Ensure PowerUpSpawners spawn with the correct values/components
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FInitPowerUpSpawnerTest, "InitPowerUpSpawner",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FInitPowerUpSpawnerTest::RunTest(FString const& Parameters) {

	// Create new world and spawn a PowerUpSpawner in it
	UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();
	APowerUpSpawner* PowerUpSpawner = World->SpawnActor<APowerUpSpawner>();

	TestTrue("PowerUpSpawner has valid root component", PowerUpSpawner->HasValidRootComponent());
	USceneComponent* RootComp = PowerUpSpawner->GetRootComponent();
	USceneComponent* ChildComp = RootComp->GetChildComponent(0);

	TestEqual("PowerUpSpawner child component is a Box", ChildComp->GetClass()->GetName(), "BoxComponent");
	UBoxComponent* BoxComp = (UBoxComponent*)ChildComp;
	
	TestEqual("PowerUpSpawner box extent is correct", BoxComp->GetUnscaledBoxExtent(), FVector(1000.0f, 1000.0f, 1000.0f));
	TestEqual("PowerUpSpawner spawn rate is correct", PowerUpSpawner->GetSpawnRate(), 5.0f);

	PowerUpSpawner->Destroy();
	return true;
}


// Test 5 - Bottom-up Integration Test: Test PowerUpSpawner's ability to spawn multiple PowerUps in the right location
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSpawnPowerUpPositionTest, "SpawnPowerUpPosition",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FSpawnPowerUpPositionTest::RunTest(FString const& Parameters) {

	// Create new world and spawn a PowerUpSpawner in it
	UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();
	APowerUpSpawner* PowerUpSpawner = World->SpawnActor<APowerUpSpawner>();

	// Get PowerUpSpawner position, extent, and minimum/maximum extents
	FVector SpawnerOrigin, SpawnerExtent, SpawnerMaxExtent, SpawnerMinExtent;
	PowerUpSpawner->GetActorBounds(false, SpawnerOrigin, SpawnerExtent);
	SpawnerMaxExtent = SpawnerOrigin + SpawnerExtent;
	SpawnerMinExtent = SpawnerOrigin - SpawnerExtent;

	// Spawn 5 PowerUps, get them all, then test their positions
	for (int i = 0; i < 5; i++) { PowerUpSpawner->SpawnPowerUp(); }
	TArray<APowerUp*> PowerUps;
	UGameplayStatics::GetAllActorsOfClass(World, APowerUp::StaticClass(), (TArray<AActor*> &)PowerUps);
	
	for (int i = 0; i < 5; i++) {
		APowerUp* PowerUp = PowerUps[i];
		
		// Check that PowerUp's location is within the bounds of the PowerUpSpawner
		FVector PowerUpPos = PowerUp->GetActorLocation();
		TestTrue("PowerUp within PowerUpSpawner bounds", PowerUpPos.X < SpawnerMaxExtent.X
			&& PowerUpPos.Y < SpawnerMaxExtent.Y
			&& PowerUpPos.Z < SpawnerMaxExtent.Z
			&& PowerUpPos.X > SpawnerMinExtent.X
			&& PowerUpPos.Y > SpawnerMinExtent.Y
			&& PowerUpPos.Z > SpawnerMinExtent.Z);

		PowerUp->Destroy();
	}
	
	PowerUpSpawner->Destroy();
	return true;
}


// Tests 6, 7, 8, 9 - White-box Tests: Provide full branch-level coverage of PaddleMovementComponent's TickComponent method:
/*
void UPaddleMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Make sure everything is valid and the paddle is allowed to move
	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime)) {
		bIsValid = false;
		return;
	}

	bIsValid = true;

	// Get the movement vector set in paddles' Tick function
	FVector DesiredMovementThisFrame = ConsumeInputVector().GetClampedToMaxSize(1.0f) * DeltaTime * SpeedMultiplier;

	// Move the paddle, respecting solid barriers
	if (!DesiredMovementThisFrame.IsNearlyZero()) {
		bWouldMove = true;

		FHitResult Hit;
		SafeMoveUpdatedComponent(DesiredMovementThisFrame, UpdatedComponent->GetComponentRotation(), true, Hit);

		// If we hit something, try to slide along it rather than getting stuck
		if (Hit.IsValidBlockingHit()) {
			bIsHitting = true;
			SlideAlongSurface(DesiredMovementThisFrame, 1.f - Hit.Time, Hit.Normal, Hit);
			return;
		}

		bIsHitting = false;
		return;
	}

	bWouldMove = false;
}
*/

// Test 6 - White-box Test 1: PaddleMovementComponent doesn't have an owner or updated component, or should otherwise not try to move
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FInvalidPaddleMovementCompTest, "InvalidPaddleMovementComponent",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FInvalidPaddleMovementCompTest::RunTest(FString const& Parameters) {
	
	// LeftPaddlePawns are given PaddleMovementComponents upon construction, 
	// so create a new world and spawn a LeftPaddlePawn in it
	UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();
	ALeftPaddlePawn* Paddle = World->SpawnActor<ALeftPaddlePawn>();

	// Get the PaddleMovementComponent and invalidate it
	UPaddleMovementComponent* PaddleMovementComp = (UPaddleMovementComponent*)Paddle->GetMovementComponent();
	PaddleMovementComp->SetUpdatedComponent(NULL);
	PaddleMovementComp->TickComponent(0.01f, LEVELTICK_All, new FActorComponentTickFunction());

	TestFalse("PaddleMovementComponent is valid", PaddleMovementComp->bIsValid);

	Paddle->Destroy();
	return true;
}


// Test 7 - White-box Test 2: PaddleMovementComponent is valid, but its desired movement is practically zero
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FZeroInputPaddleMovementCompTest, "ZeroInputPaddleMovementComponent",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FZeroInputPaddleMovementCompTest::RunTest(FString const& Parameters) {

	UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();
	ALeftPaddlePawn* Paddle = World->SpawnActor<ALeftPaddlePawn>();

	// Get the PaddleMovementComponent and validate it
	UPaddleMovementComponent* PaddleMovementComp = (UPaddleMovementComponent*)Paddle->GetMovementComponent();
	PaddleMovementComp->TickComponent(0.01f, LEVELTICK_All, new FActorComponentTickFunction());

	TestTrue("PaddleMovementComponent is valid", PaddleMovementComp->bIsValid);

	// Give it a zero vector for input and make sure it wouldn't move
	PaddleMovementComp->AddInputVector(FVector().Zero());
	PaddleMovementComp->TickComponent(0.01f, LEVELTICK_All, new FActorComponentTickFunction());

	TestFalse("PaddleMovementComponent would move", PaddleMovementComp->bWouldMove);

	Paddle->Destroy();
	return true;
}


// Test 8 - White-box Test 3: PaddleMovementComponent is valid and moves, but does not hit anything
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FNoHitPaddleMovementCompTest, "NoHitPaddleMovementComponent",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FNoHitPaddleMovementCompTest::RunTest(FString const& Parameters) {

	UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();
	ALeftPaddlePawn* Paddle = World->SpawnActor<ALeftPaddlePawn>();
	UPaddleMovementComponent* PaddleMovementComp = (UPaddleMovementComponent*)Paddle->GetMovementComponent();

	// Give it a one vector for input, make sure it would move and not hit anything
	PaddleMovementComp->AddInputVector(FVector().One());
	PaddleMovementComp->TickComponent(0.01f, LEVELTICK_All, new FActorComponentTickFunction());

	TestTrue("PaddleMovementComponent would move", PaddleMovementComp->bWouldMove);
	TestFalse("PaddleMovementComponent is hitting something", PaddleMovementComp->bIsHitting);

	Paddle->Destroy();
	return true;
}

// Test 9 - White-box Test 4: PaddleMovementComponent is valid, would move, and hits something
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FHitPaddleMovementCompTest, "HitPaddleMovementComponent",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FHitPaddleMovementCompTest::RunTest(FString const& Parameters) {

	// Create a world and spawn a left paddle, then a right paddle for it to collide with
	UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();
	ALeftPaddlePawn* Paddle = World->SpawnActor<ALeftPaddlePawn>();
	ARightPaddlePawn* HitObject = World->SpawnActor<ARightPaddlePawn>(FVector().One(), FRotator().ZeroRotator);
	UPaddleMovementComponent* PaddleMovementComp = (UPaddleMovementComponent*)Paddle->GetMovementComponent();

	// Give it a one vector for input, make sure it moves and hits the right paddle
	PaddleMovementComp->AddInputVector(FVector().One());
	PaddleMovementComp->TickComponent(0.01f, LEVELTICK_All, new FActorComponentTickFunction());

	TestTrue("PaddleMovementComponent is hitting something", PaddleMovementComp->bIsHitting);

	Paddle->Destroy();
	HitObject->Destroy();
	return true;
}


// Test 10 - Acceptance Test: Test that LeftPaddlePawn moves up the correct amount
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLeftPaddleMoveUpInputTest, "LeftPaddleMoveUp",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FLeftPaddleMoveUpInputTest::RunTest(FString const& Parameters) {

	UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();
	ALeftPaddlePawn* Paddle = World->SpawnActor<ALeftPaddlePawn>();
	UPaddleMovementComponent* MoveComp = (UPaddleMovementComponent*)Paddle->GetMovementComponent();

	FVector InitPos = Paddle->GetActorLocation();

	float AxisValue = 1.0f;
	float DeltaTime = 0.01f;

	Paddle->LeftPaddleMove(AxisValue);
	MoveComp->TickComponent(DeltaTime, LEVELTICK_All, new FActorComponentTickFunction());

	// Expected position vector based on the intermediate calculations done by LeftPaddlePawn and PaddleMovementComponent
	FVector ExpectedFinalPos = (Paddle->GetActorRightVector() * AxisValue).GetClampedToMaxSize(1.0f) * DeltaTime * MoveComp->SpeedMultiplier;
	FVector FinalPos = Paddle->GetActorLocation();

	// Test correct direction and movement amount
	TestEqual("Left paddle X position", FinalPos.X, InitPos.X);
	TestEqual("Left paddle Z position", FinalPos.Z, InitPos.Z);
	TestTrue("Left paddle moved up (+Y direction)", FinalPos.Y > InitPos.Y);
	TestEqual("Final left paddle position", FinalPos, ExpectedFinalPos);

	Paddle->Destroy();
	return true;
}

// Test 11 - Acceptance Test: Test that LeftPaddlePawn moves down the correct amount
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLeftPaddleMoveDownInputTest, "LeftPaddleMoveDown",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FLeftPaddleMoveDownInputTest::RunTest(FString const& Parameters) {

	UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();
	ALeftPaddlePawn* Paddle = World->SpawnActor<ALeftPaddlePawn>();
	UPaddleMovementComponent* MoveComp = (UPaddleMovementComponent*)Paddle->GetMovementComponent();

	FVector InitPos = Paddle->GetActorLocation();

	float AxisValue = -1.0f;
	float DeltaTime = 0.01f;

	Paddle->LeftPaddleMove(AxisValue);
	MoveComp->TickComponent(DeltaTime, LEVELTICK_All, new FActorComponentTickFunction());

	// Expected position vector based on the intermediate calculations done by LeftPaddlePawn and PaddleMovementComponent
	FVector ExpectedFinalPos = (Paddle->GetActorRightVector() * AxisValue).GetClampedToMaxSize(1.0f) * DeltaTime * MoveComp->SpeedMultiplier;
	FVector FinalPos = Paddle->GetActorLocation();

	// Test correct direction and movement amount
	TestEqual("Left paddle X position", FinalPos.X, InitPos.X);
	TestEqual("Left paddle Z position", FinalPos.Z, InitPos.Z);
	TestTrue("Left paddle moved down (-Y direction)", FinalPos.Y < InitPos.Y);
	TestEqual("Final left paddle position", FinalPos, ExpectedFinalPos);

	Paddle->Destroy();
	return true;
}

// Test 12 - Acceptance Test: Test that LeftPaddlePawn moves down the correct amount
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLeftPaddleMoveZeroInputTest, "LeftPaddleNoMove",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FLeftPaddleMoveZeroInputTest::RunTest(FString const& Parameters) {

	UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();
	ALeftPaddlePawn* Paddle = World->SpawnActor<ALeftPaddlePawn>();
	UPaddleMovementComponent* MoveComp = (UPaddleMovementComponent*)Paddle->GetMovementComponent();

	FVector InitPos = Paddle->GetActorLocation();

	float AxisValue = 0.0f;
	float DeltaTime = 0.01f;

	Paddle->LeftPaddleMove(AxisValue);
	MoveComp->TickComponent(DeltaTime, LEVELTICK_All, new FActorComponentTickFunction());

	// Expected position vector based on the intermediate calculations done by LeftPaddlePawn and PaddleMovementComponent
	FVector ExpectedFinalPos = (Paddle->GetActorRightVector() * AxisValue).GetClampedToMaxSize(1.0f) * DeltaTime * MoveComp->SpeedMultiplier;
	FVector FinalPos = Paddle->GetActorLocation();

	// Test correct direction and movement amount
	TestEqual("Left paddle position", FinalPos, InitPos);
	TestEqual("Final left paddle position", FinalPos, ExpectedFinalPos);

	Paddle->Destroy();
	return true;
}

// Tests 13, 14, 15 - Bottom-up Integration Tests: Ensure LeftPaddlePawn sends correct input to RightPaddlePawn, 
//													and that RightPaddlePawn responds accordingly

// Test 13 - Bottom-up Integration Test: Test sending up input to right paddle
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRightPaddleMoveUpInputTest, "RightPaddleMoveUp",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FRightPaddleMoveUpInputTest::RunTest(FString const& Parameters) {

	UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();
	ALeftPaddlePawn* LeftPaddle = World->SpawnActor<ALeftPaddlePawn>();

	// Right paddle is spawned far away from left paddle to avoid collisions
	ARightPaddlePawn* RightPaddle = World->SpawnActor<ARightPaddlePawn>(FVector(500.0f, 0.0f, 0.0f), FRotator().ZeroRotator);
	UPaddleMovementComponent* MoveComp = (UPaddleMovementComponent*)RightPaddle->GetMovementComponent();

	FVector InitPos = RightPaddle->GetActorLocation();

	float AxisValue = 1.0f;
	float DeltaTime = 0.01f;

	// Have left paddle send movement input to right paddle
	LeftPaddle->SendRightPaddleMove(AxisValue);
	MoveComp->TickComponent(DeltaTime, LEVELTICK_All, new FActorComponentTickFunction());

	// Expected position vector based on the intermediate calculations done by RightPaddlePawn and PaddleMovementComponent
	FVector ExpectedFinalPos = ((RightPaddle->GetActorRightVector() * AxisValue).GetClampedToMaxSize(1.0f) * DeltaTime * MoveComp->SpeedMultiplier) + InitPos;
	FVector FinalPos = RightPaddle->GetActorLocation();

	// Test correct direction and movement amount
	TestEqual("Right paddle X position", FinalPos.X, InitPos.X);
	TestEqual("Right paddle Z position", FinalPos.Z, InitPos.Z);
	TestTrue("Right paddle moved up (+Y direction)", FinalPos.Y > InitPos.Y);
	TestEqual("Final right paddle position", FinalPos, ExpectedFinalPos);

	LeftPaddle->Destroy();
	RightPaddle->Destroy();
	return true;
}

// Test 14 - Bottom-up Integration Test: Test sending down input to right paddle
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRightPaddleMoveDownInputTest, "RightPaddleMoveDown",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FRightPaddleMoveDownInputTest::RunTest(FString const& Parameters) {

	UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();
	ALeftPaddlePawn* LeftPaddle = World->SpawnActor<ALeftPaddlePawn>();

	// Right paddle is spawned far away from left paddle to avoid collisions
	ARightPaddlePawn* RightPaddle = World->SpawnActor<ARightPaddlePawn>(FVector(500.0f, 0.0f, 0.0f), FRotator().ZeroRotator);
	UPaddleMovementComponent* MoveComp = (UPaddleMovementComponent*)RightPaddle->GetMovementComponent();

	FVector InitPos = RightPaddle->GetActorLocation();

	float AxisValue = -1.0f;
	float DeltaTime = 0.01f;

	// Have left paddle send movement input to right paddle
	LeftPaddle->SendRightPaddleMove(AxisValue);
	MoveComp->TickComponent(DeltaTime, LEVELTICK_All, new FActorComponentTickFunction());

	// Expected position vector based on the intermediate calculations done by RightPaddlePawn and PaddleMovementComponent
	FVector ExpectedFinalPos = ((RightPaddle->GetActorRightVector() * AxisValue).GetClampedToMaxSize(1.0f) * DeltaTime * MoveComp->SpeedMultiplier) + InitPos;
	FVector FinalPos = RightPaddle->GetActorLocation();

	// Test correct direction and movement amount
	TestEqual("Right paddle X position", FinalPos.X, InitPos.X);
	TestEqual("Right paddle Z position", FinalPos.Z, InitPos.Z);
	TestTrue("Right paddle moved down (-Y direction)", FinalPos.Y < InitPos.Y);
	TestEqual("Final right paddle position", FinalPos, ExpectedFinalPos);

	LeftPaddle->Destroy();
	RightPaddle->Destroy();
	return true;
}

// Test 15 - Bottom-up Integration Test: Test sending zero input to right paddle
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRightPaddleMoveZeroInputTest, "RightPaddleNoMove",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FRightPaddleMoveZeroInputTest::RunTest(FString const& Parameters) {

	UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();
	ALeftPaddlePawn* LeftPaddle = World->SpawnActor<ALeftPaddlePawn>();

	// Right paddle is spawned far away from left paddle to avoid collisions
	ARightPaddlePawn* RightPaddle = World->SpawnActor<ARightPaddlePawn>(FVector(500.0f, 0.0f, 0.0f), FRotator().ZeroRotator);
	UPaddleMovementComponent* MoveComp = (UPaddleMovementComponent*)RightPaddle->GetMovementComponent();

	FVector InitPos = RightPaddle->GetActorLocation();

	float AxisValue = 0.0f;
	float DeltaTime = 0.01f;

	// Have left paddle send movement input to right paddle
	LeftPaddle->SendRightPaddleMove(AxisValue);
	MoveComp->TickComponent(DeltaTime, LEVELTICK_All, new FActorComponentTickFunction());

	// Expected position vector based on the intermediate calculations done by RightPaddlePawn and PaddleMovementComponent
	FVector ExpectedFinalPos = ((RightPaddle->GetActorRightVector() * AxisValue).GetClampedToMaxSize(1.0f) * DeltaTime * MoveComp->SpeedMultiplier) + InitPos;
	FVector FinalPos = RightPaddle->GetActorLocation();

	// Test correct direction and movement amount
	TestEqual("Right paddle position", FinalPos, InitPos);
	TestEqual("Final right paddle position", FinalPos, ExpectedFinalPos);

	LeftPaddle->Destroy();
	RightPaddle->Destroy();
	return true;
}

#endif
