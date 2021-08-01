// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameUI/InGameHUD.h"

#include "DRGameInstance.h"
#include "SoundManager.h"
#include "InGameUI/ScoreBoardWidget.h"
#include "InGameUI/InGameUI.h"
#include "InGameUI/ResultWindowWidget.h"
#include "InGameUI/PauseMenuWidget.h"


AInGameHUD::AInGameHUD()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AInGameHUD::ClearHUD()
{	
	if (InGameUIWidget && InGameUIWidget->IsInViewport()) InGameUIWidget->RemoveFromViewport();
	if (PauseMenuWidget && PauseMenuWidget->IsInViewport()) PauseMenuWidget->RemoveFromViewport();
	if (ResultWindowWidget && ResultWindowWidget->IsInViewport()) ResultWindowWidget->RemoveFromViewport();
	if (ScoreBoardWidget && ScoreBoardWidget->IsInViewport()) ScoreBoardWidget->RemoveFromViewport();
	ClockTickHandle.Invalidate();
}

void AInGameHUD::BeginPlay()
{
	Super::BeginPlay();

	CreateInGameUI();
}


UTexture2D* AInGameHUD::GetPlayerIcon(FString PlayerType)
{
	if (PlayerTypesIcons.Contains(PlayerType))
	{
		return PlayerTypesIcons[PlayerType];
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("The Level DOSE NOT Contain the PlayerType in: %s"), *GetName());
		return nullptr;
	}
}

void AInGameHUD::ShowScoreBoard()
{
	if (!ScoreBoardWidget) CreateScoreBored();

	if (ScoreBoardWidget)
	{
		ScoreBoardWidget->AddToViewport(EInGameHUDViewPortVisibility::ScoreBord);
	}
}

void AInGameHUD::HideScoreBoard()
{
	if (!ScoreBoardWidget) return;
	ScoreBoardWidget->RemoveFromViewport();
}

void AInGameHUD::ShowPauseMenu()
{
	if (!PauseMenuWidget) CreatePauseMenu();

	if (PauseMenuWidget)
	{
		PauseMenuWidget->AddToViewport(EInGameHUDViewPortVisibility::PauseMenu);
	}
}

void AInGameHUD::HidePauseMenu()
{
	if (!PauseMenuWidget) return;
	PauseMenuWidget->RemoveFromViewport();
}

void AInGameHUD::ShowResultScreen()
{
	if (!ResultWindowWidget) CreateResultsWindowWidget();
	if (ResultWindowWidget)
	{
		ResultWindowWidget->AddToViewport(EInGameHUDViewPortVisibility::ResultsMenu);
		PlayEndGameSound();
		InGameUIWidget->NotificationWidget->StopTickSound();
	}
}


void AInGameHUD::CreateInGameUI()
{
	if (InGameUIWidgetClass)
	{
		InGameUIWidget = CreateWidget<UInGameUI>(GetWorld(), InGameUIWidgetClass);
		if (InGameUIWidget)
		{
			InGameUIWidget->AddToViewport(EInGameHUDViewPortVisibility::InGameUI);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("InGameUIWidget is nullptr in: %s"), *GetName());
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("InGameUIWidgetClass is  was not assigned in BP in: %s"), *GetName());
	}
}

void AInGameHUD::CreateScoreBored()
{
	if (ScoreBoardWidgetClass)
	{
		ScoreBoardWidget = CreateWidget<UScoreBoardWidget>(GetWorld(), ScoreBoardWidgetClass);
		if (!ScoreBoardWidget)
		{
			UE_LOG(LogTemp, Error, TEXT("ScoreBoardWidget is nullptr in: %s"), *GetName());
			return;
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ScoreBoardWidgetClass is nullptr was not assigned in BP in: %s"), *GetName());
	}
}

void AInGameHUD::CreateResultsWindowWidget()
{
	if (ResultWindowWidgetClass)
	{
		ResultWindowWidget = CreateWidget<UResultWindowWidget>(GetWorld(), ResultWindowWidgetClass);
		if (!ResultWindowWidget)
		{
			UE_LOG(LogTemp, Error, TEXT("ResultWindowWidget is nullptr in: %s"), *GetName());
			return;
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ResultWindowWidgetClass is nullptr was not assigned in BP in: %s"), *GetName());
		return;
	}
}

void AInGameHUD::CreatePauseMenu()
{
	if (PauseMenuWidgetClass)
	{
		PauseMenuWidget = CreateWidget<UPauseMenuWidget>(GetWorld(), PauseMenuWidgetClass);
		if (!PauseMenuWidget)
		{
			UE_LOG(LogTemp, Error, TEXT("PauseMenuWidget is nullptr in: %s"), *GetName());
			return;
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("PauseMenuWidgetClass is nullptr was not assigned in BP in: %s"), *GetName());
		return;
	}
}

ASoundManager* AInGameHUD::TryGetSoundManager()
{
	if (!GetGameInstance<UDRGameInstance>())
	{
		UE_LOG(LogTemp, Error, TEXT("GetGameInstance nullptr in: %s"), *GetName());
		return nullptr;
	}

	if (!GetGameInstance<UDRGameInstance>()->SoundManager)
	{
		UE_LOG(LogTemp, Error, TEXT("SoundManager in ADestination::TryGetSoundManager is nullptr in: %s"), *GetName());
		return nullptr;
	}
	return GetGameInstance<UDRGameInstance>()->SoundManager;
}

void AInGameHUD::PlayEndGameSound()
{
	auto SoundManager = TryGetSoundManager();
	if (!SoundManager) return;

	if (!EndGameSound)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayEndGameSound Not Set In BP in: %s"), *GetName());
		return;
	}
	SoundManager->PlaySound(EndGameSound);
}

