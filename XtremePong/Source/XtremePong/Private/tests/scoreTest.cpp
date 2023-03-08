//Jesse A. Jones
//7 Mar, 2023
//Unit Tests

#include "ScoreBoard.h"
#include "Tests/AutomationCommon.h"

#if WITH_DEV_AUTOMATION_TESTS

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FMyAwesomeTest, "Test Player 1 Incrementation", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FMyAwesomeTest::RunTest(FString const& Parameters){
	bool result;
	
	//Creates scoreboard instance and increments player1's score.
	AScoreBoard *scoreTest = NewObject<AScoreBoard>();
	scoreTest->incrementPlayerScore(true);

	//Tests to make sure player1 score is now actually 1 after incrementation.
	result = scoreTest->player1Score == 1;
	TestTrue("CHECKS PLR 1 SCORE", result);

	return true;
}

#endif