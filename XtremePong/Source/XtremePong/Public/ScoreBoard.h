//Jesse A. Jones
//7 Mar, 2023
//XtremePong

#pragma once

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
	std::string scoreText;
	UPROPERTY(VisibleAnywhere)
	UTextRenderComponent* scoreModel;

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
		gameRound, roundWinCount, maxRoundCount;

	UPROPERTY(VisibleAnywhere)
	unsigned frameCount; //SORT OF TEST
	
	//Increases the score of a given player by 1.
	void incrementPlayerScore(bool isPlayerOne);
		
	//Checks if a given player has won a round/game.
	void isWin(); //ADD PARTICLE GENERATION LATER!

	//Resets player scores and increments to new round.
	// If maxRoundCount rounds have occured, the game is over.
	void resetScoreToNewRound();

	//Updates passed in score string or creates 
	// a score string based on custom text and returns it.
	string updateScoreText(string customString);

	//Updates the visual component of the scoreboard.
	void updateScoreboard(string scoreStr);

	//This function is called by an overlap event when player1 scores.
	UFUNCTION(BlueprintCallable)
	void scoreForPlayer1();

	//Called when player2 scores a goal.
	UFUNCTION(BlueprintCallable)
	void scoreForPlayer2();

};
