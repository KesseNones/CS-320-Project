// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LeftPaddlePawn.h"
#include "RightPaddlePawn.h"
#include "ScoreBoard.h"
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "ReplayGameInstance.generated.h"

/**
 *
 */
UCLASS()

class XTREMEPONG_API UReplayGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UReplayGameInstance();

	UPROPERTY(EditDefaultsOnly, Category = "XtremePong")
		FString replayName;

	UPROPERTY(EditDefaultsOnly, Category = "XtremePong")
		FString freplayName;

	UFUNCTION(BlueprintCallable, Category = "XtremePong")
		void startRecord();

	UFUNCTION(BlueprintCallable, Category = "XtremePong")
		void stopRecord();

	UFUNCTION(BlueprintCallable, Category = "XtremePong")
		void startReplay();

	void paddleInit();
	void camInit();
	int createReplay();
	int recordPositions();
	int loadReplay();
	int stopReplay();
	int errHandler();
	void waitFunc();

	int iLPaddleX;
	int iLPaddleY;
	int iLPaddleZ;

	int iRPaddleX;
	int iRPaddleY;
	int iRPaddleZ;

	int iCamX;
	int iCamY;
	int iCamZ;
	int iCamFOV;

	int replayLength;
	int loadedLength;
	int recorded;

	TArray<ARightPaddlePawn*> rPawn;
	TArray<ALeftPaddlePawn*> lPawn;

	TArray<int> LPaddlePos;
	TArray<int> RPaddlePos;
	TArray<int> BallPosX;
	TArray<int> BallPosY;
	TArray<int> Ticks;
	

	void Init() override;

	void Shutdown() override;

	bool Tick(float DeltaSeconds);

	FDelegateHandle TickDelegateHandle;


};
