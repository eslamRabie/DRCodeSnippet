// Fill out your copyright notice in the Description page of Project Settings.


#include "DRWaveGameMode.h"

#include "Kismet/GameplayStatics.h"


ADRWaveGameMode::ADRWaveGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
	IntervalBetweenCarsMinMaxInSeconds = FVector2D(3, 4);
	NumberOfWaves = FMath::RandRange(3, 5);
	MinimumTimeBetweenWavesInSeconds = 20.f;
	MaximumTimeBetweenWavesInSeconds = 30.f;
}


void ADRWaveGameMode::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> TempActorsList;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACarSpawner::StaticClass(), TempActorsList);
	if (TempActorsList.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("No CarSpawner Found! in: "), *GetName());
	}
	for (auto& Spawner : TempActorsList)
	{
		CarSpawnersArray.Add(Cast<ACarSpawner>(Spawner));
	}

	CurrentWaveCount = 0;

	WaveTime = FMath::RandRange(MinimumTimeBetweenWavesInSeconds, MaximumTimeBetweenWavesInSeconds);
}



void ADRWaveGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// Dont Start the Game Until notification widget initialization is passed to the widget's player 
	if (!bIsNotificationWidgetInit)
	{
		InitNotificationWidget();
		return;
	}
	// first wave was not yet spawned 
	if (!bIsGameStarted)
	{
		GetWorldTimerManager().SetTimer(TimeBetweenWavesTimerHandle, this, &ADRWaveGameMode::GameplayMode,
		                                StartGameDelay);
		// this if will not be visited again
		bIsGameStarted = true;
		return;
	}
}

void ADRWaveGameMode::EndGame()
{
	if(SpawnedCarsCount > ArrivedCarsCount)
	{
		GetWorldTimerManager().SetTimer(EndGameTimerHandle, this, &ADRWaveGameMode::EndGame, 1);
	}
	else if(SpawnedCarsCount == ArrivedCarsCount and !bIsEndingGame)
	{
		// If all waves had spawned and all cars arrived end Game
		bIsEndingGame = true;
		GetWorldTimerManager().SetTimer(EndGameTimerHandle, this, &ADRWaveGameMode::EndGame, EndGameDelay);
	}
	else
	{
		Super::EndGame();
	}
}

void ADRWaveGameMode::GameplayMode()
{
	if(CurrentWaveCount >= NumberOfWaves)
	{
		EndGame();
		return;
	}
		
	float FirstInterval = FMath::RandRange(IntervalBetweenCarsMinMaxInSeconds.X, IntervalBetweenCarsMinMaxInSeconds.Y);
	float SecondInterval = FMath::RandRange(IntervalBetweenCarsMinMaxInSeconds.X, IntervalBetweenCarsMinMaxInSeconds.Y);
	WaveTime = FirstInterval + SecondInterval + FMath::RandRange(MinimumTimeBetweenWavesInSeconds, MaximumTimeBetweenWavesInSeconds);

	int32 GoldenCarLuck = FMath::RandRange(0, 100);

	int32 GoldenCarRate = static_cast<int32>(GoldenCarSpawnRate0_1 * 100);


	if (GoldenCarLuck <= GoldenCarRate)
	{
		for (auto Spawner : CarSpawnersArray)
		{
			if (Spawner->bCanSpawn)
			{
				Spawner->SpawnGoldenCar();

				SpawnedCarsCount += 1;
			}
		}
	}

	else
	{
		CurrentWaveCount++;
		UpdateNotificationWidget();
		for (auto Spawner : CarSpawnersArray)
		{
			if (Spawner->bCanSpawn)
			{
				Spawner->SpawnWave(FirstInterval, SecondInterval);
				// Assume That each wave spawn only 3 cars
				SpawnedCarsCount += 3;
			}
		}
	}

	GetWorldTimerManager().SetTimer(TimeBetweenWavesTimerHandle, this, &ADRWaveGameMode::GameplayMode, WaveTime);

}


void ADRWaveGameMode::InitNotificationWidget()
{
	if (!GameState)
	{
		UE_LOG(LogTemp, Error, TEXT("Cant Get GameState in InitNotificationWidget in: %s "), *GetName());
		return;
	}

	for (auto Player : GameState->PlayerArray)
	{
		if (Player)
		{
			auto PlayerState = Cast<ADRInGamePlayerState>(Player);
			if (PlayerState)
			{
				PlayerState->StartNotification(EGameModes::Wave, NumberOfWaves);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Cant Cast PlayerState in InitNotificationWidget in: %s "), *GetName());
				return;
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Cant Get Player PlayerState in InitNotificationWidget in: %s "), *GetName());
			return;
		}
	}
	bIsNotificationWidgetInit = true;
}

void ADRWaveGameMode::UpdateNotificationWidget()
{
	for (auto Player : GameState->PlayerArray)
	{
		if (Player)
		{
			auto PlayerState = Cast<ADRInGamePlayerState>(Player);
			if (PlayerState)
			{
				PlayerState->UpdateNotification(NumberOfWaves - CurrentWaveCount);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Cant Cast PlayerState in InitNotificationWidget in: %s "), *GetName());
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Cant Get Player PlayerState in InitNotificationWidget in: %s "), *GetName());
		}
	}
}