// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include <Actor.h>
//#include "Destination.h"
#include "CarSpawner.h"
#include "DRGameState.h"
#include "DRInGamePlayerState.h"
#include "GameFramework/GameMode.h"

#include "DRGameMode.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class DELIVERYRUSH_API ADRGameMode : public AGameMode
{
	GENERATED_BODY()

protected:

public:

	ADRGameMode();
	
	virtual void GameplayMode(){};
	//void RestartGame();

	virtual void RestartGame() override;
		
	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameDesign")
	FVector2D IntervalBetweenCarsMinMaxInSeconds;


	// Used in GamePlayMode if overriden 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=GameDesign)
	float StartGameDelay;

	// Used in EndGame if overriden 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=GameDesign)
	float EndGameDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=GameDesign)
	float GoldenCarSpawnRate0_1;
	

	//Start Traffic Management
	void TrySwitchTraffic(class ATrafficController* ClickedTraffic);
	//End Traffic Management

	void UpdateScore(FString PlayerTypeName, int32 Score);

	void IncreaseArrivedCars(); 

	ADRInGamePlayerState* GetPlayerStateByPlayerTypeName(FString PlayerTypeName)const;
	
protected:	
	void OnUpdateScore();
	
	/**
	 * Uses AInGameHUD and ADRInGamePlayerState as Defaults for AHUD and APlayerState respectfully,
	 * Your Class must uses class that inherits from them or overrides this method 
	 */
	UFUNCTION()
	virtual void EndGame();

	// Destinations Must Update this variable to make sure that all cars arrived before ending the game
	int32 ArrivedCarsCount;
	
	UPROPERTY()
	TArray<ACarSpawner*> CarSpawnersArray;
	
	// Updated internally in GameMode 
	int32 SpawnedCarsCount;

	FTimerHandle EndGameTimerHandle;
	
	FTimerHandle TimeBetweenWavesTimerHandle;

	bool bIsEndingGame;

	bool bIsGameStarted;

	bool bIsWaitingASpawn;
private:
		
};
