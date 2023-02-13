// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainMenuPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class XTREMEPONG_API AMainMenuPlayerController : public APlayerController
{
public:
	virtual void BeginPlay() override;

	GENERATED_BODY()
	
};
