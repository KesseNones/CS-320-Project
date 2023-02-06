// Copyright Epic Games, Inc. All Rights Reserved.


#include "XtremePongGameModeBase.h"

void AXtremePongGameModeBase::BeginPlay() {
	Super::BeginPlay();
	ChangeMenuWidget(StartingWidgetClass);
}

void AXtremePongGameModeBase::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass) {

	// Remove whatever User Widget is active in the viewport, if any
	if (CurrentWidget != nullptr) {
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}

	// Create a new User Widget and add it to the viewport
	if (NewWidgetClass != nullptr) {
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
		if (CurrentWidget != nullptr) {
			CurrentWidget->AddToViewport();
		}
	}
}