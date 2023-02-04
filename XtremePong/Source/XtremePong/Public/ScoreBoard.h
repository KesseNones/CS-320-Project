//Jesse A. Jones
//4 Feb, 2023
//XtremePong

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ScoreBoard.generated.h"

UCLASS()
class XTREMEPONG_API AScoreBoard : public AActor{
	
public:	
	// Sets default values for this actor's properties
	AScoreBoard();

	//Visual component created.
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent *VisualMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
