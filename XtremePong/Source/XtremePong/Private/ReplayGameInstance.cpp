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

	paddleInit();
	camInit();
	
	LPaddlePos = { 0 };
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
	// Add BallX
	// Add BallY
	// Check scoreboard. If won, set recorded = 1.
}

bool UReplayGameInstance::Tick(float DeltaSeconds) {
	if (recorded == 0) {
		recordPositions(); // Append new positions each tick
		replayLength += 1; // Ticks in replay
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
	TickDelegateHandle = FTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateUObject(this, &UReplayGameInstance::Tick));

	Super::Init();
}

void UReplayGameInstance::Shutdown() {
	// Cleans up game instance
	FTicker::GetCoreTicker().RemoveTicker(TickDelegateHandle);

	Super::Shutdown();
}

int UReplayGameInstance::loadReplay() {
	// Set rPawn.Y to RPaddlePos[loadedLength]
	// Set lPawn.Y to LPaddlePos[loadedLength]
	// Set Ball.X to BallPosX[loadedLength]
	// Set Ball.Y to BallPosY[loadedLength]
	return 1;
}

int UReplayGameInstance::stopReplay() {
	return 1;
}

void UReplayGameInstance::waitFunc() {
	recorded = 2;
	// Wait 5 seconds or for some user input to move on to playing replay
}

int UReplayGameInstance::errHandler() {
	return 1;
}