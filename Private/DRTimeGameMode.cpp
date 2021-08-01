// Fill out your copyright notice in the Description page of Project Settings.


#include "DRTimeGameMode.h"

#include "Kismet/GameplayStatics.h"


ADRTimeGameMode::ADRTimeGameMode()
{
	PrimaryActorTick.bCanEverTick = true;

	GameTimeInSec = 60.f;
	GameTimeInMinutes = 1;
	IntervalBetweenCarsMinMaxInSeconds = FVector2D(100, 500);
}



void ADRTimeGameMode::BeginPlay()
{
	Super::BeginPlay();

	GameTimeInSec = GameTimeInMinutes * 60.f;

	TArray<AActor*> TempActorsList;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACarSpawner::StaticClass(), TempActorsList);
	if(TempActorsList.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("No CarSpawner Found! in: "), *GetName());
	}
	for(auto& Spawner: TempActorsList)
	{
		CarSpawnersArray.Add(Cast<ACarSpawner>(Spawner));
	}
	
}


void ADRTimeGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if(!bIsNotificationWidgetInit)
	{
		InitNotificationWidget();
		return;
	}
	
	// Spawn Waves of cars as long as the GameTime is not over
	if(GameTimeInSec > 0)
	{
		GameTimeInSec -= DeltaSeconds;
		GameplayMode();
	}
	else
	{
		if(SpawnedCarsCount == ArrivedCarsCount && !bIsWaitingASpawn && !bIsEndingGame)
		{
			bIsEndingGame = true;
			GetWorldTimerManager().SetTimer(EndGameTimerHandle, this, &ADRTimeGameMode::EndGame, EndGameDelay);
			
		}
	}

	
}

void ADRTimeGameMode::GameplayMode()
{
	if(bIsWaitingASpawn) return;
	for (auto Spawner : CarSpawnersArray)
	{
		if (!Spawner->bCanSpawn)
		{
			return;
		}
	}
	if(!bIsGameStarted)
	{
		bIsGameStarted = true;
		bIsWaitingASpawn = true;
		GetWorldTimerManager().SetTimer(TimeBetweenWavesTimerHandle, this, &ADRTimeGameMode::Spawn, StartGameDelay);
		return;
	}

	bIsWaitingASpawn = true;
	GetWorldTimerManager().SetTimer(TimeBetweenWavesTimerHandle, this, &ADRTimeGameMode::Spawn, IntervalBetweenCarsMinMaxInSeconds.X);
}


void ADRTimeGameMode::Spawn()
{

	
	int32 GoldenCarLuck = FMath::RandRange(0, 100);

	int32 GoldenCarRate = static_cast<int32>(GoldenCarSpawnRate0_1 * 100);
	
	
	if(GoldenCarLuck <= GoldenCarRate)
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
		float FirstInterval = FMath::RandRange(IntervalBetweenCarsMinMaxInSeconds.X, IntervalBetweenCarsMinMaxInSeconds.Y);
		float SecondInterval = FMath::RandRange(IntervalBetweenCarsMinMaxInSeconds.X, IntervalBetweenCarsMinMaxInSeconds.Y);
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
	
	bIsWaitingASpawn = false;
}

void ADRTimeGameMode::InitNotificationWidget()
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
				PlayerState->StartNotification(EGameModes::Time, GameTimeInSec);
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
