// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ScrollBox.h"
#include "Components/VerticalBox.h"

#include "ScoreBoardWidget.generated.h"

/**
 * 
 */

class UPlayerRankInfoWidget;

UCLASS()
class DELIVERYRUSH_API UScoreBoardWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(Meta = (BindWidget))
	UScrollBox* ScoreList;

	UPROPERTY(EditDefaultsOnly, Category = "Defaults")
	TSubclassOf<UPlayerRankInfoWidget> PlayerRankInfoWidgetClass;
	

};
