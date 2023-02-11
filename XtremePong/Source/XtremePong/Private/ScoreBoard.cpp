//Jesse A. Jones
//10 Feb, 2023
//XtremePong

#include "ScoreBoard.h"
#include <string>
using namespace std;

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

	scoreModel = nullptr;
	//Displays initial gamestate.
	updateScoreboard();
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
	//Checks for win and updates board state every frame.
	isWin();
	updateScoreboard();

}

void AScoreBoard::incrementPlayerScore(bool isPlayerOne) {
	if (isPlayerOne) {
		player1Score++;
	}
	else {
		player2Score++;
	}
}

void AScoreBoard::isWin() {
	if (player1Score >= roundWinCount) {
		//DISPLAY PLAYER 1 VICTORY
		resetScoreToNewRound();
	}

	if (player2Score >= roundWinCount) {
		//DISPLAY PLAYER 2 VICTORY
		resetScoreToNewRound();
	}
}

void AScoreBoard::resetScoreToNewRound() {
	//Resets player scores and increments round.
	player1Score = 0;
	player2Score = 0;
	gameRound++;

	//Enters end state if max rounds reached.
	if (gameRound > maxRoundCount) {
		//END GAME LEVEL SOMEHOW. PERHAPS CHANGE LEVEL!
	}
}

void AScoreBoard::updateScoreboard() {
	//Generates string representation of scoreboard.
	scoreText = "Round: " + to_string(gameRound) + "\n"
		+ "Player 1: " + to_string(player1Score) + " " +
		"Player 2: " + to_string(player2Score);

	//Spawns score representation 
	// in the world if it doesn't exist yet.
	if (scoreModel == nullptr) {
		//DOCS: 
		// https://docs.unrealengine.com/5.1/en-US/spawning-actors-in-unreal-engine/
		// 
		//USE SPAWNACTOR FUNCTION.
		//USAGE: MyHUD = SpawnActor<AHUD>(this, Instigator);
		
		//Creates scoreboard.
		scoreModel = CreateDefaultSubobject<UTextRenderComponent>(FName("Score"));

		//Sets position and rotation on board.
		scoreModel->SetRelativeLocation(FVector(0.0f, -31530.0f, 20.0f));
		scoreModel->SetRelativeRotation(FRotator(0.0f, 90.0f, 90.0f));

		//Scales letters to appropriate dimensions.
		scoreModel->SetXScale(1.0f);
		scoreModel->SetYScale(1.0f);
		scoreModel->SetWorldSize(75.0f); //MIGHT BE INCORRECT

		//Sets alignment and hooks component 
		// to root to make it part of the level.
		scoreModel->SetHorizontalAlignment(EHTA_Center);
		scoreModel->SetVerticalAlignment(EVerticalTextAligment::EVRTA_TextCenter);
		scoreModel->SetTextRenderColor(FColor::White);
		scoreModel->SetupAttachment(RootComponent);


	}
	else {
		//Updates scoreboard text to new one.
		scoreModel->SetText(FText::FromString(scoreText.c_str()));
	}
}