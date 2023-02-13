// Fill out your copyright notice in the Description page of Project Settings.


#include "PaddleMovementComponent.h"

void UPaddleMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Make sure everything is valid and the paddle is allowed to move
	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime)) {
		return;
	}

	// Get the movement vector set in paddles' Tick function
	FVector DesiredMovementThisFrame = ConsumeInputVector().GetClampedToMaxSize(1.0f) * DeltaTime * SpeedMultiplier;

	// Move the paddle, respecting solid barriers
	if (!DesiredMovementThisFrame.IsNearlyZero()) {
		FHitResult Hit;
		SafeMoveUpdatedComponent(DesiredMovementThisFrame, UpdatedComponent->GetComponentRotation(), true, Hit);

		// If we hit something, try to slide along it rather than getting stuck
		if (Hit.IsValidBlockingHit()) {
			SlideAlongSurface(DesiredMovementThisFrame, 1.f - Hit.Time, Hit.Normal, Hit);
		}
	}
}