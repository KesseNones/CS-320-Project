// Fill out your copyright notice in the Description page of Project Settings.


#include "Replays.h"

UReplays::UReplays()
{
	replayName = "basicReplay";
	freplayName = "basicReplay2";
}

void UReplays::startRecord()
{
	StartRecordingReplay(replayName, freplayName);
}

void UReplays::stopRecord()
{
	StopRecordingReplay();
}

void UReplays::startReplay()
{
	PlayReplay(replayName, nullptr);
}