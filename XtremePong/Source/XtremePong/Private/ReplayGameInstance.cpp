// Fill out your copyright notice in the Description page of Project Settings.

#include "ReplayGameInstance.h"

UReplayGameInstance::UReplayGameInstance()
{
	replayName = "basicReplay";
	freplayName = "basicReplay2";
}

void UReplayGameInstance::startRecord()
{
	StartRecordingReplay(replayName, freplayName);
}

void UReplayGameInstance::stopRecord()
{
	StopRecordingReplay();
}

void UReplayGameInstance::startReplay()
{
	PlayReplay(replayName, nullptr);
}

void UReplayGameInstance::paddleInit() {

	iLPaddleX = 0;
	iLPaddleY = 0;
	iLPaddleZ = 0;

	iRPaddleX = 0;
	iRPaddleY = 0;
	iRPaddleZ = 0;

}

void UReplayGameInstance::camInit() {

	iCamX = 0;
	iCamY = 0;
	iCamZ = 0;
	iCamFOV = 120;

}

int UReplayGameInstance::createReplay() {
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARightPaddlePawn::StaticClass(), (TArray<AActor*> &)rPawn);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALeftPaddlePawn::StaticClass(), (TArray<AActor*> &)lPawn);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABall::StaticClass(), (TArray<AActor*> &)Ball);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AScoreBoard::StaticClass(), (TArray<AActor*> &)ScoreBoard);

	paddleInit();
	camInit();
	
	LPaddlePos = {0};
	RPaddlePos = { 0 };
	BallPosX = { 0 };
	BallPosY = { 0 };
	Ticks = { 0 };
	recorded = 0;

	return 1;

}

int UReplayGameInstance::recordPositions() {
	// Calculate new positions for paddles and ball here


	RPaddlePos.Add(rPawn[0]->GetActorLocation().Y);
	LPaddlePos.Add(lPawn[0]->GetActorLocation().Y);
	BallPosX.Add(Ball[0]->GetActorLocation().X);
	BallPosY.Add(Ball[0]->GetActorLocation().Y);


	// If match is won
	if (ScoreBoard[0]->player1Score == 10 || ScoreBoard[0]->player2Score == 10) {
		recorded = 1;
	}

	return 1;
}

bool UReplayGameInstance::Tick(float DeltaSeconds) {
	if (recorded == 0) {
		if (!rPawn.IsEmpty() && !lPawn.IsEmpty() && !Ball.IsEmpty()) {
			recordPositions(); // Append new positions each tick
			replayLength += 1; // Ticks in replay
		}
	}
	else if (recorded == 1) {
		waitFunc();
	}
	else {
		loadReplay(); // Start loading positions to play replay
		if (loadedLength < replayLength) {
			loadedLength += 1;
		}
		return true;
	}
	return true;
}

void UReplayGameInstance::Init() {
	// Creates tick delegate (used in this case to maintain the same delay between gathering position of objects in game)
	TickDelegateHandle = FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateUObject(this, &UReplayGameInstance::Tick));

}

void UReplayGameInstance::Shutdown() {
	// Cleans up game instance
	FTSTicker::GetCoreTicker().RemoveTicker(TickDelegateHandle);

}

int UReplayGameInstance::loadReplay() {
	if (!rPawn.IsEmpty() && !lPawn.IsEmpty() && !Ball.IsEmpty()) {
		rPawn[0]->SetActorLocation(FVector(900.0f, RPaddlePos[loadedLength], 100.0f));
		lPawn[0]->SetActorLocation(FVector(100.0f, LPaddlePos[loadedLength], 100.0f));
		Ball[0]->SetActorLocation(FVector(BallPosX[loadedLength], BallPosY[loadedLength], 100.0f));
	}
	return 1;
}

int UReplayGameInstance::stopReplay() {
	// Obsolete
	return 1;
}

void UReplayGameInstance::waitFunc() {
	// Wait 5 seconds or for some user input to move on to playing replay
	// "Requires timer, timer delegate, and all that stuff"
	recorded = 2;
}

int UReplayGameInstance::errHandler() {
	return 1;
}