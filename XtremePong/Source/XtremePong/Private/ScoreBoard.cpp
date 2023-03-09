//Jesse A. Jones
//25 Feb, 2023
//XtremePong

#include "ScoreBoard.h"
#include <string>
using namespace std;

//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%s"), debugString.c_str())); //SYNTAX FOR PRINTING DEBUG MESSAGES FOR DEV!!!
// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%d"), frameCount));
//CREDIT: https://dev.epicgames.com/community/snippets/JvB/unreal-engine-c-print-string

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
	//frameCount = 0; //DELETE LATER????

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

	//frameCount++; DELETE LATER????

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
	//Player 1 round/game victory case.
	if (player1Score >= roundWinCount) {
		//DISPLAY PLAYER 1 VICTORY
		resetScoreToNewRound();
		return 1;
	}

	//Player 2 round/game victory case.
	if (player2Score >= roundWinCount) {
		//DISPLAY PLAYER 2 VICTORY
		resetScoreToNewRound();
		return 2;
	}

	return 0;
}

void AScoreBoard::resetScoreToNewRound() {
	//Resets player scores and increments round.
	player1Score = 0;
	player2Score = 0;
	gameRound++;

	//Enters end state if max rounds reached.
	if (gameRound > maxRoundCount) {
		//CHANGE LEVEL HERE LATER!
	}
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
}

void AScoreBoard::scoreForPlayer2(){
	incrementPlayerScore(false);
	scoreText = updateScoreText("");
	updateScoreboard(scoreText);
}