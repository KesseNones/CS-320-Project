
#include "Tests/AutomationCommon.h"
#include "LeftPaddlePawn.h"
#include "RightPaddlePawn.h"
#include "ScoreBoard.h"
#include "ReplayGameInstance.h"
#include <string>

using namespace std;

# if WITH_DEV_AUTOMATION_TESTS

// TEST 1
IMPLEMENT_SIMPLE_AUTOMATION_TEST(Test1, "TestName1",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool Test1::RunTest(FString const& Parameters) {
	// Acceptance Test
	// Tests if the left paddle pawn starts in the correct position

	UReplayGameInstance* temp = NewObject<UReplayGameInstance>();
	temp->createReplay();

	TestEqual("LPaddle has correct X position", temp->iLPaddleX, 0);
	TestEqual("LPaddle has correct Y position", temp->iLPaddleY, 0);
	TestEqual("LPaddle has correct Z position", temp->iLPaddleZ, 0);


	return true;

}

// TEST 2
IMPLEMENT_SIMPLE_AUTOMATION_TEST(Test2, "TestName2",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool Test2::RunTest(FString const& Parameters) {
	// Acceptance Test
	// Tests if the right paddle pawn starts in the correct position

	UReplayGameInstance* temp = NewObject<UReplayGameInstance>();
	temp->createReplay();

	TestEqual("RPaddle has correct X position", temp->iRPaddleX, 0);
	TestEqual("RPaddle has correct Y position", temp->iRPaddleY, 0);
	TestEqual("RPaddle has correct Z position", temp->iRPaddleZ, 0);


	return true;

}

// TEST 3
IMPLEMENT_SIMPLE_AUTOMATION_TEST(Test3, "TestName3",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool Test3::RunTest(FString const& Parameters) {
	// Acceptance Test
	// Tests if the left paddle pawn stays within game bounds during replay

	int maxY = 450;
	int minY = -450;

	UReplayGameInstance* temp = NewObject<UReplayGameInstance>();
	temp->createReplay();

	for (int i = 0; i < temp->LPaddlePos.Num(); i++) {
		TestTrue("LPaddle is within specified bounds", temp->LPaddlePos[i] < maxY);
		TestTrue("LPaddle is within specified bounds", temp->LPaddlePos[i] > minY);
	}

	return true;

}

// TEST 4
IMPLEMENT_SIMPLE_AUTOMATION_TEST(Test4, "TestName4",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool Test4::RunTest(FString const& Parameters) {
	// Acceptance Test
	// Tests if the right paddle pawn stays within game bounds during replay

	int maxY = 450;
	int minY = -450;

	UReplayGameInstance* temp = NewObject<UReplayGameInstance>();
	temp->createReplay();

	for (int i = 0; i < temp->RPaddlePos.Num(); i++) {
		TestTrue("RPaddle is within specified bounds", temp->RPaddlePos[i] < maxY);
		TestTrue("RPaddle is within specified bounds", temp->RPaddlePos[i] > minY);
	}

	return true;

}

// TEST 5
IMPLEMENT_SIMPLE_AUTOMATION_TEST(Test5, "TestName5",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool Test5::RunTest(FString const& Parameters) {
	// Acceptance Test
	// Tests if the pong ball stays within game bounds during replay

	int maxY = 450;
	int minY = -450;

	int maxX = 800;
	int minX = -800;

	UReplayGameInstance* temp = NewObject<UReplayGameInstance>();
	temp->createReplay();

	for (int i = 0; i < temp->BallPosY.Num(); i++) {
		TestTrue("Ball is within specified bounds (y-axis)", temp->BallPosY[i] < maxY);
		TestTrue("Ball is within specified bounds (y-axis)", temp->BallPosY[i] > minY);
		TestTrue("Ball is within specified bounds (x-axis)", temp->BallPosX[i] < maxX);
		TestTrue("Ball is within specified bounds (x-axis)", temp->BallPosX[i] > minX);
	}

	return true;

}

// TEST 6
IMPLEMENT_SIMPLE_AUTOMATION_TEST(Test6, "TestName6",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool Test6::RunTest(FString const& Parameters) {
	// Acceptance Test
	// Tests if the camera actor spawns in the correct position with the correct parameters
	// Will be useful when camera-tracking is implemented with changing X,Y, and Z positions

	UReplayGameInstance* temp = NewObject<UReplayGameInstance>();
	temp->createReplay();

	TestEqual("Camera has correct X position", temp->iCamX, 0);
	TestEqual("Camera has correct Y position", temp->iCamY, 0);
	TestEqual("Camera has correct Z position", temp->iCamZ, 0);
	TestEqual("Camera has correct FOV", temp->iCamFOV, 120);

	return true;

}

// TEST 7
IMPLEMENT_SIMPLE_AUTOMATION_TEST(Test7, "TestName7",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool Test7::RunTest(FString const& Parameters) {
	// Acceptance Test
	// Tests if there are > 0 ticks recorded indicating a replay was created
	// If replay was created, checks to see if the replay's length is > 0 ticks

	UReplayGameInstance* temp = NewObject<UReplayGameInstance>();
	temp->createReplay();

	TestTrue("Replay exists", temp->Ticks.Num() > 0);

	if (temp->Ticks.Num() > 0) {
		TestTrue("Replay length is greater than 0 seconds", temp->Ticks[temp->Ticks.Num() - 1] > 0);
	}

	return true;

}

// TEST 8
IMPLEMENT_SIMPLE_AUTOMATION_TEST(Test8, "TestName8",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool Test8::RunTest(FString const& Parameters) {
	// Acceptance Test
	// Makes sure that there are no Null or negative bytes in tick array

	UReplayGameInstance* temp = NewObject<UReplayGameInstance>();
	temp->createReplay();

	for (int i = 0; i < temp->Ticks.Num(); i++) {
		TestTrue("Tick is not null or negative", temp->Ticks[i] > 0);
	}

	return true;

}

// TEST 9
IMPLEMENT_SIMPLE_AUTOMATION_TEST(Test9, "TestName9",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool Test9::RunTest(FString const& Parameters) {
	// Whitebox Test (Statement Coverage)
	// createReplays() should return 1 if it works succesfully and will call on every statement in the header file

	UReplayGameInstance* temp = NewObject<UReplayGameInstance>();
	int ret = temp->createReplay();
	int ret2 = temp->loadReplay();
	int ret3 = temp->stopReplay();
	int ret4 = temp->errHandler();

	TestEqual("iLPaddleX statement covered", temp->iLPaddleX, 0);
	TestEqual("iLPaddleY statement covered", temp->iLPaddleY, 0);
	TestEqual("iLPaddleZ statement covered", temp->iLPaddleZ, 0);
	TestEqual("iRPaddleX statement covered", temp->iRPaddleX, 0);
	TestEqual("iRPaddleY statement covered", temp->iRPaddleY, 0);
	TestEqual("iRPaddleZ statement covered", temp->iRPaddleZ, 0);
	TestEqual("iCamX statement covered", temp->iCamX, 0);
	TestEqual("iCamY statements covered", temp->iCamY, 0);
	TestEqual("iCamZ statements covered", temp->iCamZ, 0);
	TestEqual("iCamFOV statements covered", temp->iCamFOV, 120);
	TestEqual("Error handler covered", ret4, 1);
	TestEqual("Stop replay covered", ret3, 1);
	TestEqual("Load replay covered", ret2, 1);
	TestEqual("All statements covered", ret, 1);

	return true;

}

// TEST 10
IMPLEMENT_SIMPLE_AUTOMATION_TEST(Test10, "TestName10",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool Test10::RunTest(FString const& Parameters) {
	// Acceptance Test
	// Ensures that replay can be loaded

	UReplayGameInstance* temp = NewObject<UReplayGameInstance>();
	int ret = temp->loadReplay();

	TestEqual("Replay can be loaded", ret, 1);

	return true;

}

// TEST 11
IMPLEMENT_SIMPLE_AUTOMATION_TEST(Test11, "TestName11",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool Test11::RunTest(FString const& Parameters) {
	// Acceptance Test
	// Ensures that replay can be succesfully stopped

	UReplayGameInstance* temp = NewObject<UReplayGameInstance>();
	int ret = temp->stopReplay();

	TestEqual("Replay can be stopped", ret, 1);

	return true;

}

// TEST 12
IMPLEMENT_SIMPLE_AUTOMATION_TEST(Test12, "TestName12",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool Test12::RunTest(FString const& Parameters) {
	// Acceptance Test
	/* Ensures that the replay error handler is succesfully able to deal with errors that
	   either come up in createReplay() or loadReplay()                                   */

	UReplayGameInstance* temp = NewObject<UReplayGameInstance>();
	int ret = temp->errHandler();

	TestEqual("Not unhandled errors in replay system", ret, 1);

	return true;

}

#endif