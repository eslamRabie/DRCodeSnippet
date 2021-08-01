// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameUI/PlayerRankInfoWidget.h"

void UPlayerRankInfoWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UPlayerRankInfoWidget::Create(ADRInGamePlayerState* InPlayerState)
{
	if(!InPlayerState)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't SetInGamePlayerState in: "), *GetName());
		return;
	}
	this->PlayerState = InPlayerState;
	SetUpWidget();
}

void UPlayerRankInfoWidget::SetUpWidget()
{
	if(!PlayerState)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't Get PlayerState in SetUpWidget, in: "), *GetName());
		return;
	}

	if(!PlayerState->PlayerIcon)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't Get PlayerIcon in SetUpWidget, in: "), *GetName());
		return;
	}
	PlayerIcon->SetBrushFromTexture(PlayerState->PlayerIcon);

	PlayerName->SetText(FText::FromString(PlayerState->GetPlayerName()));

	PlayerRank->SetText(FText::FromString(FString::FromInt(PlayerState->Rank)));

	PlayerScore->SetText(FText::FromString(FString::FromInt(PlayerState->GetScore())));
	
}
