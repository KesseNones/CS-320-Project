// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
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



};
