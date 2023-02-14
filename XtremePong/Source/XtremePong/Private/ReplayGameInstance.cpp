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