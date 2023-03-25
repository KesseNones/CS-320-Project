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
	paddleInit();
	camInit();

	LPaddlePos = { 0 };
	RPaddlePos = { 0 };
	BallPosX = { 0 };
	BallPosY = { 0 };
	Ticks = { 0 };

	return 1;

}

int UReplayGameInstance::loadReplay() {
	return 1;
}

int UReplayGameInstance::stopReplay() {
	return 1;
}

int UReplayGameInstance::errHandler() {
	return 1;
}