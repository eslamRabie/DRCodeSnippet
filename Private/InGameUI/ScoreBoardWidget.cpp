// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameUI/ScoreBoardWidget.h"

#include "DRGameState.h"
#include "DRInGamePlayerState.h"
#include "Components/BorderSlot.h"
#include "GameFramework/GameStateBase.h"
#include "InGameUI/PlayerRankInfoWidget.h"

void UScoreBoardWidget::NativeConstruct()
{
	Super::NativeConstruct();

	
	auto World = GetWorld();
	if(!World) return;
	
	auto PlayerArray = Cast<ADRGameState>(World->GetGameState())->PlayerArray;
	if(PlayerArray.Num() ==0) return;

	TArray<ADRInGamePlayerState*> InGamePlayerArray;

	for(auto Player: PlayerArray)
	{
		if(Player)
		{
			auto Temp = Cast<ADRInGamePlayerState>(Player);
			if(Temp)
				InGamePlayerArray.Add(Temp);
		}
	}

	InGamePlayerArray.Sort();
	
	ScoreList->ClearChildren();
	
	for(auto& PlayerState: InGamePlayerArray)
	{
		if(!PlayerState)
		{
			UE_LOG(LogTemp, Error, TEXT("PlayerState is nullptr in: %s"), *GetName());
			continue;
		}
		
		auto PlayerRankInfoWidget = CreateWidget<UPlayerRankInfoWidget>(World, PlayerRankInfoWidgetClass);
		if(!PlayerRankInfoWidget)
		{
			UE_LOG(LogTemp, Error, TEXT("Cant Create Widget! in : %s"), *GetName());
			return;
		}
		PlayerRankInfoWidget->Create(PlayerState);
		ScoreList->AddChild(PlayerRankInfoWidget);
			
	}
}

