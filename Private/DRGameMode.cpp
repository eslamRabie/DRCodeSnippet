// Fill out your copyright notice in the Description page of Project Settings.


#include "DRGameMode.h"

#include "TrafficController.h"
#include "DRGameState.h"
#include "Network/DRGameSession.h"

ADRGameMode::ADRGameMode()
{
	PrimaryActorTick.bCanEverTick = true;	
	PlayerStateClass = ADRInGamePlayerState::StaticClass();
	StartGameDelay = 5;
	EndGameDelay = 5;

	bIsEndingGame = false;
	bIsGameStarted = false;
	bIsWaitingASpawn = false;

	GoldenCarSpawnRate0_1 = 0.1;

}

void ADRGameMode::RestartGame()
{
	//auto InGameGameSession = Cast<ADRGameSession>(GameSession);
	if ( GameSession->CanRestartGame() )
	{
		if (GetMatchState() == MatchState::LeavingMap)
		{
			return;
		}
		for(auto Player: GameState->PlayerArray)
		{
			auto InGamePlayer = Cast<ADRInGamePlayerState>(Player);
			if(InGamePlayer)
			{
				InGamePlayer->ResetHUD();
			}
		}
		bUseSeamlessTravel = true;
		GetWorld()->ServerTravel("?Restart");
	}
}

void ADRGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ADRGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	ArrivedCarsCount = 0;
	SpawnedCarsCount = 0;
}

void ADRGameMode::TrySwitchTraffic(ATrafficController* ClickedTraffic)
{
	if (ClickedTraffic)
	{
		if (ClickedTraffic->CanSwitch())
		{
			ClickedTraffic->Switch();
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TrySwitchTraffic: Null traffic Ref!"));
	}
}

void ADRGameMode::UpdateScore(FString PlayerTypeName, int32 Score)
{
	auto PlayerState = GetPlayerStateByPlayerTypeName(PlayerTypeName);
	if(!PlayerState)
	{
		UE_LOG(LogTemp, Error, TEXT("Cnat find PlayerState for the type name:%s  to UpdateScore in : %s"), *PlayerTypeName, *GetName());
		return;
	}

	PlayerState->SetScore(PlayerState->GetScore() + Score);
	PlayerState->OnRep_Score();
	OnUpdateScore();
}

void ADRGameMode::IncreaseArrivedCars()
{
	ArrivedCarsCount++;
}


ADRInGamePlayerState* ADRGameMode::GetPlayerStateByPlayerTypeName(FString PlayerTypeName) const
{
	for(auto& OldPlayerSate: GameState->PlayerArray)
	{
		if(!OldPlayerSate) continue;
		auto NewPlayerState = Cast<ADRInGamePlayerState>(OldPlayerSate);
		if(!NewPlayerState) continue;

		if(NewPlayerState->PlayerType == PlayerTypeName) return NewPlayerState;
	}
	return nullptr;
}

void ADRGameMode::OnUpdateScore()
{
	TArray<ADRInGamePlayerState*> TempPlayerArray;
	for(auto TempPlayerState: GameState->PlayerArray)
	{
		TempPlayerArray.Add(Cast<ADRInGamePlayerState>(TempPlayerState));
	}
	TempPlayerArray.Sort();
	int32 Rank = 1; 
	for(auto TempPlayerState: TempPlayerArray)
	{
		TempPlayerState->Rank = Rank;
		Rank++;
	}
	
}

void ADRGameMode::EndGame()
{
	
	if(!GameState)
	{
		UE_LOG(LogTemp, Error, TEXT("Cant Get GameState in EndGame in: %s "), *GetName());
		return;
	}

	for(auto Player: GameState->PlayerArray)
	{
		if(Player)
		{
			auto PlayerState = Cast<ADRInGamePlayerState>(Player);
			if(PlayerState)
			{
				PlayerState->EndGame();
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Cant Cast PlayerState in EndGame in: %s "), *GetName());
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Cant Get Player PlayerState in EndGame in: %s "), *GetName());
		}
	}
}
