// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "XtremePongGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class XTREMEPONG_API AXtremePongGameModeBase : public AGameModeBase
{
public:
	// Remove current menu widget and create a new one from the specified class, if provided
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
		void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

protected:
	virtual void BeginPlay() override;

	// The widget class to use as the menu when game starts
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
		TSubclassOf<UUserWidget> StartingWidgetClass;

	// The widget instance used as the menu
	UPROPERTY()
		UUserWidget* CurrentWidget;

	GENERATED_BODY()
	
};
