// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "PaddleMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class XTREMEPONG_API UPaddleMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()

public:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Makes this variable editable in the editor
	UPROPERTY(EditAnywhere)
		float SpeedMultiplier = 500.0f;
};
