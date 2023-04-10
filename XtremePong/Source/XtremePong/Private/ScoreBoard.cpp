//Jesse A. Jones
//9 Apr, 2023
//XtremePong ScoreBoard

#include "ScoreBoard.h"
#include <string>
#include "Ball.h"
#include <time.h>
using namespace std;

//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%s"), debugString.c_str())); //SYNTAX FOR PRINTING DEBUG MESSAGES FOR DEV!!!
// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%d"), frameCount));
//CREDIT: https://dev.epicgames.com/community/snippets/JvB/unreal-engine-c-print-string

//ISSUES: 
/*
	--Make round victory text go away after x seconds.
*/

// Sets default values
AScoreBoard::AScoreBoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	player1Score = 0;
	player2Score = 0;
	gameRound = 0;
	previousLoser = 0;

	roundWinCount = 10;
	maxRoundCount = 5;

	//Creates initial score text.
	scoreText = updateScoreText("");

	//Displays score text in model.
	scoreModel = nullptr;
	updateScoreboard(scoreText);

	ballCount = 0;

	// FVector loc = balls[0]->GetActorLocation();
	// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%d %d %d"), loc[0], loc[1], loc[2]));

	// //FVector newLoc = FVector(0.0f, 0.0f, 20.0f);
	// balls[0]->SetActorLocation(FVector(0.0f, 0.0f, 20.0f));

	// FVector loc2 = balls[0]->GetActorLocation();

	// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%d %d %d"), loc[0], loc[1], loc[2]));
}

string AScoreBoard::getScoreText(){
	return scoreText;
}

// Called when the game starts or when spawned
void AScoreBoard::BeginPlay()
{
	Super::BeginPlay();
	createBall();
}

void AScoreBoard::createBall(){
	float ballSpeed;
	int posOrNegVel[2] = {1, -1};
	FVector ballLoc = FVector(0.0f, 0.0f, 20.0f);
	FRotator ballRot = FRotator(0.0f, 0.0f, 0.0f);

	//Creates ball and sets appropriate scale, position, and rotation.
	balls[ballCount] = GetWorld()->SpawnActor<ABall>(ballLoc, ballRot);
	balls[ballCount]->SetActorScale3D(FVector(20.0f));

	//Determines which direction the ball travels after spawning.
	if (previousLoser == 1){
		ballSpeed = -5000.0f;
	}else if (previousLoser == 2){
		ballSpeed = 5000.0f;
	}else{
		ballSpeed = posOrNegVel[time(0) % 2] * 5000.0f; 
	}

	balls[ballCount]->setBallVelocity(FVector(ballSpeed, 0.0f, 0.0f));
	ballCount++;
}

void AScoreBoard::destroyBall(){
	FVector actorLoc;
	//auto splosion = GetWorld()->SpawnActor<AExplosion>();	//FECCING BORKEN
	if (ballCount > 0){
		actorLoc = balls[ballCount - 1]->GetActorLocation();
		//splosion->explode(actorLoc);							//BORKED
		GetWorld()->DestroyActor(balls[ballCount - 1]);
		//GetWorld()->DestroyActor(splosion);	//THOROUGHLY BORKED
		ballCount--;
	}
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

void AScoreBoard::resetScoreToNewRound() {
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
	destroyBall();
	incrementPlayerScore(true);
	scoreText = updateScoreText("");
	updateScoreboard(scoreText);
	isWin();
	previousLoser = 2;
	createBall();
}

void AScoreBoard::scoreForPlayer2(){
	destroyBall();
	incrementPlayerScore(false);
	scoreText = updateScoreText("");
	updateScoreboard(scoreText);
	isWin();
	previousLoser = 1;
	createBall();
}