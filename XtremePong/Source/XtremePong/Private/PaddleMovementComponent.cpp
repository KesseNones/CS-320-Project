
#include "PaddleMovementComponent.h"

void UPaddleMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Make sure everything is valid and the paddle is allowed to move
	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime)) {
		bIsValid = false;
		return;
	}

	bIsValid = true;

	// Get the movement vector set in paddles' Tick function
	FVector DesiredMovementThisFrame = ConsumeInputVector().GetClampedToMaxSize(1.0f) * DeltaTime * SpeedMultiplier;

	// Move the paddle, respecting solid barriers
	if (!DesiredMovementThisFrame.IsNearlyZero()) {
		bWouldMove = true;

		FHitResult Hit;
		SafeMoveUpdatedComponent(DesiredMovementThisFrame, UpdatedComponent->GetComponentRotation(), true, Hit);

		// If we hit something, try to slide along it rather than getting stuck
		if (Hit.IsValidBlockingHit()) {
			bIsHitting = true;
			SlideAlongSurface(DesiredMovementThisFrame, 1.f - Hit.Time, Hit.Normal, Hit);
			return;
		}

		bIsHitting = false;
		return;
	}

	bWouldMove = false;
}