//Jesse A. Jones
//11 Feb, 2023
//XtremePong

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
#include "Engine/EngineTypes.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "ScoreBoard.generated.h"

UCLASS()
class XTREMEPONG_API AScoreBoard : public AActor{
	GENERATED_BODY()

private:	
	// Sets default values for this actor's properties
	AScoreBoard();

	//Visual component created.
	// UPROPERTY(VisibleAnywhere)
	// UStaticMeshComponent *VisualMesh; //DELETE LATER??

	//Members used to display the score.
	std::string scoreText;
	UPROPERTY(VisibleAnywhere)
	UTextRenderComponent* scoreModel;

	UPROPERTY(VisibleAnywhere)
	unsigned frameCount; //SORT OF TEST

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	UFUNCTION(BlueprintCallable)
	virtual void Tick(float DeltaTime) override;

	int player1Score, player2Score,
		gameRound, roundWinCount, maxRoundCount;

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
