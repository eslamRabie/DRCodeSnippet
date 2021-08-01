// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRGameMode.h"
#include "CarSpawner.h"
#include "DRWaveGameMode.generated.h"

/**
 * 
 */
UCLASS()
class DELIVERYRUSH_API ADRWaveGameMode : public ADRGameMode
{
	GENERATED_BODY()
	
public:

	ADRWaveGameMode();

	virtual void GameplayMode() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Design)
	int32 NumberOfWaves;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Design)
	int32 MinimumTimeBetweenWavesInSeconds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Design)
	int32 MaximumTimeBetweenWavesInSeconds;
	
protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void EndGame() override;

private:


	void InitNotificationWidget();

	void UpdateNotificationWidget();

	bool bIsNotificationWidgetInit = false;
	
	int32 CurrentWaveCount;
	
	float WaveTime;
	
};
