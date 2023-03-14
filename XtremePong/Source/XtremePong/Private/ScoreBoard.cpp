//Jesse A. Jones
//13 Mar, 2023
//XtremePong

#include "ScoreBoard.h"
#include <string>
using namespace std;

//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%s"), debugString.c_str())); //SYNTAX FOR PRINTING DEBUG MESSAGES FOR DEV!!!
// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%d"), frameCount));
//CREDIT: https://dev.epicgames.com/community/snippets/JvB/unreal-engine-c-print-string

//ISSUES: 
/*
	--Make round victory text go away after x seconds.
	--Create tests for round victory text generation.
	--Make ball respawn after being deleted for victory detection.
*/

// Sets default values
AScoreBoard::AScoreBoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	player1Score = 0;
	player2Score = 0;
	gameRound = 0;

	roundWinCount = 10;
	maxRoundCount = 3;

	//Creates initial score text.
	scoreText = updateScoreText("");

	//Displays score text in model.
	scoreModel = nullptr;
	updateScoreboard(scoreText);
}

// Called when the game starts or when spawned
void AScoreBoard::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AScoreBoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AScoreBoard::incrementPlayerScore(bool isPlayerOne) {
	if (isPlayerOne) {
		player1Score++;
	}
	else {
		player2Score++;
	}
}

int AScoreBoard::isWin() {
	string victoryString;

	//Player 1 round/game victory case.
	if (player1Score >= roundWinCount) {
		resetScoreToNewRound();

		//If player1 wins a round, but the game isn't over, display player 1 victory.
		if (gameRound < maxRoundCount){
			victoryString = "Player 1 Wins Round " + to_string(gameRound) + "!";
			scoreText = updateScoreText(victoryString);
			updateScoreboard(scoreText);
		}

		return 1;
	}

	//Player 2 round/game victory case.
	if (player2Score >= roundWinCount) {
		resetScoreToNewRound();

		//If player2 wins a round, but the game isn't over, display player 2 victory.
		if (gameRound < maxRoundCount){
			victoryString = "Player 1 Wins Round " + to_string(gameRound) + "!";
			scoreText = updateScoreText(victoryString);
			updateScoreboard(scoreText);
		}

		return 2;
	}

	return 0;
}

void AScoreBoard::resetScoreToNewRound() {
	//Enters end state if max rounds reached.
	if (gameRound + 1 > maxRoundCount) {
		//CHANGE LEVEL HERE LATER!
	}

	//Resets player scores and increments round.
	player1Score = 0;
	player2Score = 0;
	gameRound++;

}

string AScoreBoard::updateScoreText(string customString){
	string score;

	//Creates standard score string if custom string is empty, 
	// otherwise string is set to custom string.
	if (customString.empty()){
		//Generates string representation of scoreboard.
		score = "Round: " + to_string(gameRound + 1) + "\n"
			+ "Player 1: " + to_string(player1Score) + "\n" +
			"Player 2: " + to_string(player2Score);
	}else{
		score = customString;
	}

	return score;
}

void AScoreBoard::updateScoreboard(string scoreStr) {

	//Spawns score representation 
	// in the world if it doesn't exist yet.
	if (scoreModel == nullptr) {
		//Creates scoreboard.
		scoreModel = CreateDefaultSubobject<UTextRenderComponent>(FName("Score"));

		//Sets position and rotation on board.
		scoreModel->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		scoreModel->SetRelativeRotation(FRotator(90.0f, 90.0f, 0.0f));

		//Scales letters to appropriate dimensions.
		scoreModel->SetXScale(1.0f);
		scoreModel->SetYScale(1.0f);
		scoreModel->SetWorldSize(1000.0f);

		//Sets alignment and hooks component 
		// to root to make it part of the level.
		scoreModel->SetHorizontalAlignment(EHTA_Center);
		scoreModel->SetVerticalAlignment(EVerticalTextAligment::EVRTA_TextCenter);
		scoreModel->SetTextRenderColor(FColor::Black);
		scoreModel->SetupAttachment(RootComponent);

		//Sets text display.
		scoreModel->SetText(FText::FromString(scoreStr.c_str()));
	}
	else {
		//Updates scoreboard text to new one.
		scoreModel->SetText(FText::FromString(scoreStr.c_str()));
	}

}

void AScoreBoard::scoreForPlayer1(){
	incrementPlayerScore(true);
	scoreText = updateScoreText("");
	updateScoreboard(scoreText);
	isWin();
}

void AScoreBoard::scoreForPlayer2(){
	incrementPlayerScore(false);
	scoreText = updateScoreText("");
	updateScoreboard(scoreText);
	isWin();
}