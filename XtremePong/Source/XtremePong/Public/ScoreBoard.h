//Jesse A. Jones
//7 Apr, 2023
//XtremePong

#pragma once

#include "Ball.h"
#include "Explosion.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
#include "Engine/EngineTypes.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "ScoreBoard.generated.h"

using namespace std;

UCLASS()
class XTREMEPONG_API AScoreBoard : public AActor{
	GENERATED_BODY()

private:	

	//Members used to display the score.
	string scoreText;
	UPROPERTY(VisibleAnywhere)
	UTextRenderComponent* scoreModel;

	//Tracks previous losing player in game.
	int previousLoser;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this actor's properties
	AScoreBoard();
	
	// Called every frame
	UFUNCTION(BlueprintCallable)
	virtual void Tick(float DeltaTime) override;

	int player1Score, player2Score,
		gameRound, roundWinCount, maxRoundCount, explosionCount;

	//Used to track balls and the number of them on the board.
	ABall *balls[64];
	int ballCount;

	//Returns the score text when requested. 
	// Acts as a getter method since scoreText is private.
	string getScoreText();
	
	//Increases the score of a given player by 1.
	void incrementPlayerScore(bool isPlayerOne);
		
	//Checks if a given player has won a round/game.
	//Returns 1 for player 1 win, 2 for player 2 win, and 0 for no wins.
	int isWin(); //ADD PARTICLE GENERATION LATER!

	//Resets player scores and increments to new round.
	// If maxRoundCount rounds have occured, the game is over.
	void resetScoreToNewRound();

	//Updates passed in score string or creates 
	// a score string based on custom text and returns it.
	string updateScoreText(string customString);

	//Updates the visual component of the scoreboard.
	void updateScoreboard(string scoreStr);

	//Creates a ball to be used in the game.
	void createBall();

	//Does the opposite of createBall, 
	// getting rid of a ball actor from the game.
	void destroyBall();

	//This function is called by an overlap event when player1 scores.
	UFUNCTION(BlueprintCallable)
	void scoreForPlayer1();

	//Called when player2 scores a goal.
	UFUNCTION(BlueprintCallable)
	void scoreForPlayer2();

};
