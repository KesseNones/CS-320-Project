//Jesse A. Jones
//9 Feb, 2023
//XtremePong

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ScoreBoard.generated.h"

UCLASS()
class XTREMEPONG_API AScoreBoard : public AActor{
	GENERATED_BODY()

private:	
	// Sets default values for this actor's properties
	AScoreBoard();

	//Visual component created.
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent *VisualMesh;

	//Members used to display the score.
	std::string scoreText;
	UTextRenderComponent* scoreModel;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	int player1Score, player2Score,
		gameRound, roundWinCount, maxRoundCount;

	UWorld *Game;

	//Increases the score of a given player by 1.
	void incrementPlayerScore(bool isPlayerOne);
		
	//Checks if a given player has won a round/game.
	void isWin(); //ADD PARTICLE GENERATION LATER!

	//Resets player scores and increments to new round.
	// If maxRoundCount rounds have occured, the game is over.
	void resetScoreToNewRound();

	//Updates the visual component of the scoreboard.
	void updateScoreboard();

};
