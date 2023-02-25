// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PaddleControlInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPaddleControlInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 *	Interface for transferring inputs from left paddle to right paddle, allowing for 1 keyboard multiplayer
 */
class XTREMEPONG_API IPaddleControlInterface
{
	GENERATED_BODY()

public:

	virtual void SendRightPaddleMove(float Value);
};
