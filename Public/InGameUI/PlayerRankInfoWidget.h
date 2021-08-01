// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "DRInGamePlayerState.h"
#include "Blueprint/UserWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

#include "PlayerRankInfoWidget.generated.h"

/**
 * 
 */
UCLASS()
class DELIVERYRUSH_API UPlayerRankInfoWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	

	/**
	 * Takes the PlayerStates of the player that we want to display its info
	 */
	void Create(ADRInGamePlayerState* InPlayerState);
	
	
	ADRInGamePlayerState* GetInGamePlayerState() const { return PlayerState; }


private:

	void SetUpWidget();
	
	UPROPERTY()
	ADRInGamePlayerState* PlayerState;

	UPROPERTY(Meta = (BindWidget))
	UTextBlock* PlayerScore;
	
	UPROPERTY(Meta = (BindWidget))
	UTextBlock* PlayerName;
	
	UPROPERTY(Meta = (BindWidget))
	UTextBlock* PlayerRank;

	UPROPERTY(Meta = (BindWidget))
	UImage* PlayerIcon;



/**
 * Helper for sorting and searching
 * */

public:
	
	friend bool operator==(const UPlayerRankInfoWidget& Lhs, const UPlayerRankInfoWidget& RHS)
	{
		return Lhs.PlayerState == RHS.PlayerState;
	}

	friend bool operator!=(const UPlayerRankInfoWidget& Lhs, const UPlayerRankInfoWidget& RHS)
	{
		return !(Lhs == RHS);
	}


	friend bool operator<(const UPlayerRankInfoWidget& Lhs, const UPlayerRankInfoWidget& RHS)
	{
		return Lhs.PlayerState < RHS.PlayerState;
	}

	friend bool operator<=(const UPlayerRankInfoWidget& Lhs, const UPlayerRankInfoWidget& RHS)
	{
		return !(RHS < Lhs);
	}

	friend bool operator>(const UPlayerRankInfoWidget& Lhs, const UPlayerRankInfoWidget& RHS)
	{
		return RHS < Lhs;
	}

	friend bool operator>=(const UPlayerRankInfoWidget& Lhs, const UPlayerRankInfoWidget& RHS)
	{
		return !(Lhs < RHS);
	}

	
};
