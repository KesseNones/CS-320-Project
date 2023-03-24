

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
	//ConstructorHelpers::FObjectFinder<UStaticMesh>ExpectedMesh(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));	// This crashes Unreal :(
	//TestEqual("Static Mesh uses a sphere mesh", StaticMeshComp->GetStaticMesh(), ExpectedMesh);
	//TestEqual("Static Mesh is correctly scaled", StaticMeshComp->GetRelativeScale3D(), FVector(0.6f, 0.6f, 0.6f));

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
	}
	
	PowerUpSpawner->Destroy();
	return true;
}


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FInitOnePowerUpTest, UWorld*, World);
bool FInitOnePowerUpTest::Update() {

	TArray<APowerUp*> PowerUps;
	UGameplayStatics::GetAllActorsOfClass(World, APowerUp::StaticClass(), (TArray<AActor*> &)PowerUps);

	// Check that one and only one PowerUp spawned in the time allotted.
	//Test->TestEqual("Only one PowerUp spawned", PowerUps.Num(), 1);

	APowerUp* PowerUp = PowerUps[0];



	PowerUp->Destroy();
	return true;
}

// Test 6 - Bottom-up Integration Test: Test PowerUpSpawner's ability to spawn PowerUps at the correct intervals
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSpawnPowerUpTimingTest, "SpawnPowerUpTiming",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FSpawnPowerUpTimingTest::RunTest(FString const& Parameters) {
	
	// Latent function: wait for PowerUp to spawn, then check where it spawned and how long it took to spawn
	
	//ADD_LATENT_AUTOMATION_COMMAND(FWaitLatentCommand(PowerUpSpawner->GetSpawnRate() + 1));
	
	// Make sure one PowerUp spawned correctly in that time
	//ADD_LATENT_AUTOMATION_COMMAND(FInitOnePowerUpTest(this, World));
	
	
	return true;
}


#endif


/* Possible tests :

	- Paddle movement tests
		- Call their movement methods with AxisValue = 1.0f ten times or something, then verify that paddle position is 10 units above original position
		- Do the same for moving down
		- Ensure that after moving paddles, their X and Z positions haven't changed
		- Call LeftPaddle::SendRightPaddleMove(1.0f) and compare the right paddle's new position to original position

	- White-box test of PaddleMovementComponent?
	
	- Integration test to make sure PowerUpSpawner actually spawns a PowerUp? test spawning intervals?
	
	- Test objects' initial values (constructor testing)
	
	
	Tests done: 5/12
	- Blackbox
	- Integration

*/