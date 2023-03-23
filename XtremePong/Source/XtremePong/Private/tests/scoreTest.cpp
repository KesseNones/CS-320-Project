//Jesse A. Jones
//21 Mar, 2023
//Unit Tests

#include "ScoreBoard.h"
#include "Ball.h"
#include "Tests/AutomationCommon.h"
#include "Tests/AutomationEditorCommon.h"

#include <string>

using namespace std;

//INTEGRATION TEST(S) NEED TO WORK!!!

#if WITH_DEV_AUTOMATION_TESTS

//TEST #1
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FScoreIncrem1, "Test Player 1 Incrementation", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

//Tests incrementation of player 1 score.
//acceptance test
bool FScoreIncrem1::RunTest(FString const& Parameters){
	bool result;
	
	//Creates scoreboard instance and increments player1's score.
	AScoreBoard *scoreTest = NewObject<AScoreBoard>();
	scoreTest->incrementPlayerScore(true);

	//Tests to make sure player1 score is now actually 1 after incrementation.
	result = scoreTest->player1Score == 1;
	
	//Gets rid of instantiated scoreboard.
	scoreTest->MarkAsGarbage();
	
	TestTrue("CHECKS PLR 1 SCORE", result);

	return true;
}

//TEST #2
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FScoreIncrem2, "Test Player 2 Incrementation", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

//Tests incrementation of player 2 score.
//acceptance test
bool FScoreIncrem2::RunTest(FString const& Parameters){
	bool result;
	
	//Creates scoreboard instance and increments player2's score.
	AScoreBoard *scoreTest = NewObject<AScoreBoard>();
	scoreTest->incrementPlayerScore(false);

	//Tests to make sure player2 score is now actually 1 after incrementation.
	result = scoreTest->player2Score == 1;
	
	//Gets rid of instantiated scoreboard.
	scoreTest->MarkAsGarbage();
	
	TestTrue("CHECKS PLR 2 SCORE", result);

	return true;
}

//TEST #3
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FWinDetect1, "Test Player 1 Win", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

/*	CODE BEING TESTED:
int AScoreBoard::isWin() {
	//Player 1 round/game victory case.
	if (player1Score >= roundWinCount) {
		resetScoreToNewRound();

		//If player1 wins a round, but the game isn't over, display player 1 victory.
		//Otherwise display player 1 game victory if game is over.
		if (gameRound < maxRoundCount){
			scoreText = updateScoreText("Player 1 Wins Round " + to_string(gameRound) + "!");
			updateScoreboard(scoreText);
		}else{
			scoreText = updateScoreText("Player 1 Wins Game!");
			updateScoreboard(scoreText);
		}
		return 1;
	}

	//Player 2 round/game victory case.
	if (player2Score >= roundWinCount) {
		resetScoreToNewRound();

		//If player2 wins a round, but the game isn't over, display player 2 victory.
		//Otherwise display player 2 game victory.
		if (gameRound < maxRoundCount){
			scoreText = updateScoreText("Player 2 Wins Round " + to_string(gameRound) + "!");
			updateScoreboard(scoreText);
		}else{
			scoreText = updateScoreText("Player 2 Wins Game!");
			updateScoreboard(scoreText);
		}
		return 2;
	}
	return 0;
}
		This test is a whitebox test that tests the player 1 victory branch 
		in detection of victories, achieving 33% coverage. 
		With the test for player 1 victory and no player victory, 
		100% branch coverage is achieved.

*/
bool FWinDetect1::RunTest(FString const& Parameters){
	bool result;
	int retVal;
	
	//Creates scoreboard instance, sets player 1 to winning score for round,
	// then tests to see if a win was detected for player 1.
	AScoreBoard *board = NewObject<AScoreBoard>();
	board->player1Score = board->roundWinCount;
	board->player2Score = 0;
	retVal = board->isWin();

	//Tests to make sure player 1 actually won the round/game.
	result = retVal == 1;
	
	//Gets rid of test scoreboard.
	board->MarkAsGarbage();
	
	TestTrue("CHECKS PLR 1 WIN", result);

	return true;
}

//TEST #4
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FWinDetect2, "Test Player 2 Win", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

/*	CODE BEING TESTED:
int AScoreBoard::isWin() {
	//Player 1 round/game victory case.
	if (player1Score >= roundWinCount) {
		resetScoreToNewRound();

		//If player1 wins a round, but the game isn't over, display player 1 victory.
		//Otherwise display player 1 game victory if game is over.
		if (gameRound < maxRoundCount){
			scoreText = updateScoreText("Player 1 Wins Round " + to_string(gameRound) + "!");
			updateScoreboard(scoreText);
		}else{
			scoreText = updateScoreText("Player 1 Wins Game!");
			updateScoreboard(scoreText);
		}
		return 1;
	}

	//Player 2 round/game victory case.
	if (player2Score >= roundWinCount) {
		resetScoreToNewRound();

		//If player2 wins a round, but the game isn't over, display player 2 victory.
		//Otherwise display player 2 game victory.
		if (gameRound < maxRoundCount){
			scoreText = updateScoreText("Player 2 Wins Round " + to_string(gameRound) + "!");
			updateScoreboard(scoreText);
		}else{
			scoreText = updateScoreText("Player 2 Wins Game!");
			updateScoreboard(scoreText);
		}
		return 2;
	}
	return 0;
}
		This test is a whitebox test that tests the player 2 victory branch 
		in detection of victories, achieving 33% coverage. 
		With the test for player 1 victory and no player victory, 
		100% branch coverage is achieved.
*/
bool FWinDetect2::RunTest(FString const& Parameters){
	bool result;
	int retVal;
	
	//Creates scoreboard instance, sets player 2 to winning score for round,
	// then tests to see if a win was detected for player 2.
	AScoreBoard *board = NewObject<AScoreBoard>();
	board->player1Score = 0;
	board->player2Score = board->roundWinCount;
	retVal = board->isWin();

	//Tests to make sure player 1 actually won the round/game.
	result = retVal == 2;
	
	//Gets rid of test scoreboard.
	board->MarkAsGarbage();
	
	TestTrue("CHECKS PLR 2 WIN", result);

	return true;
}

//TEST #5
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FWinDetectNoWin, "Test No Win", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

/*	CODE BEING TESTED:
int AScoreBoard::isWin() {
	//Player 1 round/game victory case.
	if (player1Score >= roundWinCount) {
		resetScoreToNewRound();

		//If player1 wins a round, but the game isn't over, display player 1 victory.
		//Otherwise display player 1 game victory if game is over.
		if (gameRound < maxRoundCount){
			scoreText = updateScoreText("Player 1 Wins Round " + to_string(gameRound) + "!");
			updateScoreboard(scoreText);
		}else{
			scoreText = updateScoreText("Player 1 Wins Game!");
			updateScoreboard(scoreText);
		}
		return 1;
	}

	//Player 2 round/game victory case.
	if (player2Score >= roundWinCount) {
		resetScoreToNewRound();

		//If player2 wins a round, but the game isn't over, display player 2 victory.
		//Otherwise display player 2 game victory.
		if (gameRound < maxRoundCount){
			scoreText = updateScoreText("Player 2 Wins Round " + to_string(gameRound) + "!");
			updateScoreboard(scoreText);
		}else{
			scoreText = updateScoreText("Player 2 Wins Game!");
			updateScoreboard(scoreText);
		}
		return 2;
	}
	return 0;
}
		This tests if neither player has won a given round. 
		This test achieves 33% coverage. With the test for player 1
		victory and player 2 victory, 100% coverage is achieved.
*/
bool FWinDetectNoWin::RunTest(FString const& Parameters){
	bool result;
	int retVal;
	
	//Creates scoreboard instance and checks for win immediately.
	//Player 1 and 2 scores are both 0 here.  
	AScoreBoard *board = NewObject<AScoreBoard>();
	retVal = board->isWin();

	//Tests to make sure no one won the round/game.
	result = retVal == 0;
	
	//Gets rid of test scoreboard.
	board->MarkAsGarbage();
	
	TestTrue("CHECKS NO WIN DETECTION", result);

	return true;
}

//TEST #6
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FScoreReset, "Reset Scores Test", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

//Tests to see if reset scores method actually resets scores.
//acceptance test
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
	
	//Gets rid of test scoreboard.
	board->MarkAsGarbage();
	
	TestTrue("CHECKS SCORE RESET", result);

	return true;
}

//TEST #7
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FScoreTextDefaultTest, "Test Default Score Text Generation", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

//Tests to see if score text generator actually 
// creates default score text when no custom text is given.
//acceptance test
bool FScoreTextDefaultTest::RunTest(FString const& Parameters){
	bool result;

	string expectedString = "Round: 1\nPlayer 1: 0\nPlayer 2: 0";
	string resultString;
	
	//Creates board, gets return value of creation of score text.
	AScoreBoard *board = NewObject<AScoreBoard>();
	resultString = board->updateScoreText("");

	//Tests to make sure default score text is actually created.
	result = (expectedString.compare(resultString)) == 0;
	
	//Gets rid of test scoreboard.
	board->MarkAsGarbage();
	
	TestTrue("CHECKS DEFAULT SCORE TEXT CREATION", result);

	return true;
}

//TEST #8
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FScoreTextCustomTest, "Test Custom Score Text Generation", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

//Tests to see if score text generator actually 
// creates text when a custom message is given.
//acceptance test
bool FScoreTextCustomTest::RunTest(FString const& Parameters){
	bool result;

	string expectedString = "THIS IS A CUSTOM STRING!\n";
	string resultString;
	
	//Creates board, gets return value of creation of score text.
	AScoreBoard *board = NewObject<AScoreBoard>();
	resultString = board->updateScoreText("THIS IS A CUSTOM STRING!\n");

	//Tests to make sure default score text is actually created.
	result = (expectedString.compare(resultString)) == 0;
	
	//Gets rid of test scoreboard.
	board->MarkAsGarbage();

	TestTrue("CHECKS CUSTOM SCORE TEXT CREATION", result);

	return true;
}

//TEST #9
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FWinText1, "Player 1 Round Victory Text Test", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

//Test player 1 win text generation from isWin.
//This test succeeds if the score text 
// is the correct custom player 1 victory text.
//acceptance test
bool FWinText1::RunTest(FString const& Parameters){
	bool result;
	string plr1VicStr = "Player 1 Wins Round 1!";
	
	//Creates scoreboard instance, sets player 1 to winning score for round,
	// then tests to see if a win was detected for player 1.
	AScoreBoard *board = NewObject<AScoreBoard>();
	board->player1Score = board->roundWinCount;
	board->player2Score = 0;
	board->isWin();

	//Tests to make sure correct victory text for scoreText was generated.
	result = (plr1VicStr.compare(board->getScoreText())) == 0;
	
	//Gets rid of test scoreboard.
	board->MarkAsGarbage();
	
	TestTrue("CHECKS PLR 1 WIN TEXT", result);

	return true;
}

//TEST #10
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FWinText2, "Player 2 Round Victory Text Test", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

//Test player 2 win text generation from isWin.
//This test succeeds if the score text 
// is the correct custom player 2 victory text.
//acceptance test
bool FWinText2::RunTest(FString const& Parameters){
	bool result;
	string plr2VicStr = "Player 2 Wins Round 1!";
	
	//Creates scoreboard instance, sets player 2 to winning score for round,
	// then tests to see if a win was detected for player 2.
	AScoreBoard *board = NewObject<AScoreBoard>();
	board->player1Score = 0;
	board->player2Score = board->roundWinCount;
	board->isWin();

	//Tests to make sure correct victory text for scoreText was generated.
	result = (plr2VicStr.compare(board->getScoreText())) == 0;
	
	//Gets rid of test scoreboard.
	board->MarkAsGarbage();
	
	TestTrue("CHECKS PLR 2 WIN TEXT", result);

	return true;
}

//TEST #11
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FWinGameText1, "Game Victory Text Test Player 1", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

//Tests if correct score text is set in scoreText 
// for player 1 winning the game.
//acceptance test
bool FWinGameText1::RunTest(FString const& Parameters){
	bool result;
	string expectStr = "Player 1 Wins Game!";
	
	//Creates scoreboard, sets player 1 to winning score. 
	// Reset happens so round moves beyond max, 
	// ending the game with player 1 victory.
	AScoreBoard *board = NewObject<AScoreBoard>();
	board->player1Score = board->roundWinCount;
	board->player2Score = 0;
	board->gameRound = board->maxRoundCount - 1;
	board->isWin();

	//Tests to make sure correct victory text for scoreText was generated.
	result = (expectStr.compare(board->getScoreText())) == 0;
	
	//Gets rid of test scoreboard.
	board->MarkAsGarbage();
	
	TestTrue("CHECKS PLR 1 GAME WIN TEXT", result);

	return true;
}

//TEST #12
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FWinGameText2, "Game Victory Text Test Player 2", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

//Tests if correct score text is set in scoreText 
// for player 2 winning the game.
//acceptance test
bool FWinGameText2::RunTest(FString const& Parameters){
	bool result;
	string expectStr = "Player 2 Wins Game!";
	
	//Creates scoreboard, sets player 2 to winning score. 
	// Reset happens so round moves beyond max, 
	// ending the game with player 2 victory.
	AScoreBoard *board = NewObject<AScoreBoard>();
	board->player1Score = 0;
	board->player2Score = board->roundWinCount;
	board->gameRound = board->maxRoundCount - 1;
	board->isWin();

	//Tests to make sure correct victory text for scoreText was generated.
	result = (expectStr.compare(board->getScoreText())) == 0;
	
	//Gets rid of test scoreboard.
	board->MarkAsGarbage();
	
	TestTrue("CHECKS PLR 2 GAME WIN TEXT", result);

	return true;
}

//TEST #13
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBallCreationTest, "Ball Creation Test", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

/*
	Two units are being tested in this integration test. 
The two units inolved are the AScoreBoard class I made 
and the ABall class made by Ben. My scoreboard's createBall method is called
which creates an instance of Ben's ball. The location of the ball is tested
to see if it's correct.

	The overall approach of this integration test is bottom-up, 
since it takes two relatively simple classes and connects them 
in a bottom up fashion by linking them together 
in the ball creaiton method.

*/

//Tests if correct score text is set in scoreText 
// for player 2 winning the game.
bool FBallCreationTest::RunTest(FString const& Parameters){
	FVector expectedCoords = FVector(0.0f, 0.0f, 20.0f);

	FVector scoreLoc = FVector(0.0f, 0.0f, 0.0f);
	FRotator scoreRot = FRotator(0.0f, 0.0f, 0.0f);

	UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();

	//Creates scoreboard that then creates a ball.
	AScoreBoard *board = World->SpawnActor<AScoreBoard>(scoreLoc, scoreRot);
	board->createBall();

	//Gets Ball's coordinates.
	auto ballPtr = board->balls[board->ballCount - 1];
	FVector ballCoords = ballPtr->GetActorLocation();

	//Gets rid of spawned ball.
	board->balls[0]->Destroy();

	//Gets rid of test scoreboard.
	board->Destroy();
	
	//Tests to make sure all coordinate axis are valid.
	TestTrue("X == 0", (expectedCoords[0] == ballCoords[0]));
	TestTrue("Y == 0", (expectedCoords[1] == ballCoords[1]));
	TestTrue("Z == 20", (expectedCoords[2] == ballCoords[2]));

	return true;
}

#endif
