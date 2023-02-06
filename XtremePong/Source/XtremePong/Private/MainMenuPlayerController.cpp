// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuPlayerController.h"

void AMainMenuPlayerController::BeginPlay() {
	Super::BeginPlay();
	SetInputMode(FInputModeGameAndUI());
}