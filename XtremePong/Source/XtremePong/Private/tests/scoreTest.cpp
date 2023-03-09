//Jesse A. Jones
//8 Mar, 2023
//Unit Tests

#include "ScoreBoard.h"
#include "Tests/AutomationCommon.h"

using namespace std;

#if WITH_DEV_AUTOMATION_TESTS

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FScoreIncrem1, "Test Player 1 Incrementation", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

//Tests incrementation of player 1 score.
bool FScoreIncrem1::RunTest(FString const& Parameters){
	bool result;
	
	//Creates scoreboard instance and increments player1's score.
	AScoreBoard *scoreTest = NewObject<AScoreBoard>();
	scoreTest->incrementPlayerScore(true);

	//Tests to make sure player1 score is now actually 1 after incrementation.
	result = scoreTest->player1Score == 1;
	TestTrue("CHECKS PLR 1 SCORE", result);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FScoreIncrem2, "Test Player 2 Incrementation", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

//Tests incrementation of player 2 score.
bool FScoreIncrem2::RunTest(FString const& Parameters){
	bool result;
	
	//Creates scoreboard instance and increments player2's score.
	AScoreBoard *scoreTest = NewObject<AScoreBoard>();
	scoreTest->incrementPlayerScore(false);

	//Tests to make sure player2 score is now actually 1 after incrementation.
	result = scoreTest->player2Score == 1;
	TestTrue("CHECKS PLR 2 SCORE", result);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FWinDetect1, "Test Player 1 Win", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

//Test player 1 win detection.
bool FWinDetect1::RunTest(FString const& Parameters){
	bool result;
	int retVal;
	
	//Creates scoreboard instance, sets player 1 to winning score for round,
	// then tests to see if a win was detected for player 1.
	AScoreBoard *board = NewObject<AScoreBoard>();
	board->player1Score = 10;
	board->player2Score = 0;
	retVal = board->isWin();

	//Tests to make sure player 1 actually won the round/game.
	result = retVal == 1;
	TestTrue("CHECKS PLR 1 WIN", result);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FWinDetect2, "Test Player 2 Win", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

//Test player 2 win detection.
bool FWinDetect2::RunTest(FString const& Parameters){
	bool result;
	int retVal;
	
	//Creates scoreboard instance, sets player 2 to winning score for round,
	// then tests to see if a win was detected for player 2.
	AScoreBoard *board = NewObject<AScoreBoard>();
	board->player1Score = 0;
	board->player2Score = 10;
	retVal = board->isWin();

	//Tests to make sure player 1 actually won the round/game.
	result = retVal == 2;
	TestTrue("CHECKS PLR 2 WIN", result);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FWinDetectNoWin, "Test No Win", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

//Tests lack of wins detected.
bool FWinDetectNoWin::RunTest(FString const& Parameters){
	bool result;
	int retVal;
	
	//Creates scoreboard instance and checks for win immediately.
	//Player 1 and 2 scores are both 0 here.  
	AScoreBoard *board = NewObject<AScoreBoard>();
	retVal = board->isWin();

	//Tests to make sure no one won the round/game.
	result = retVal == 0;
	TestTrue("CHECKS NO WIN DETECTION", result);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FScoreReset, "Reset Scores Test", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

//Tests to see if reset scores method actually resets scores.
bool FScoreReset::RunTest(FString const& Parameters){
	bool result;
	
	//Creates scoreboard, sets player scores to arbitrary values, 
	// then calls the reset method.
	AScoreBoard *board = NewObject<AScoreBoard>();
	board->player1Score = 4;
	board->player2Score = 6;
	board->resetScoreToNewRound();

	//Tests to make sure scores actually reset.
	result = (board->player1Score == 0) && (board->player2Score == 0);
	TestTrue("CHECKS SCORE RESET", result);

	return true;
}

#endif