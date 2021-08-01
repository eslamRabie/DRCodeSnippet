// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "CarSpawner.h"
#include "DRGameMode.h"
#include "DRTimeGameMode.generated.h"

/**
 * 
 */
UCLASS()
class DELIVERYRUSH_API ADRTimeGameMode : public ADRGameMode
{
	GENERATED_BODY()

public:

	ADRTimeGameMode();


	virtual void GameplayMode() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Design)
	int32 GameTimeInMinutes = 0;


protected:
		
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	

private:

	void Spawn();

	void InitNotificationWidget();

	bool bIsNotificationWidgetInit = false;
	
	float GameTimeInSec;



	
};
