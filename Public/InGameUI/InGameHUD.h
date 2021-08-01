// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/HUD.h"
#include "InGameHUD.generated.h"


class UInGameUI;
class UScoreBoardWidget;
class UResultWindowWidget;
class UPauseMenuWidget;
class ASoundManager;

UENUM()
enum EInGameHUDViewPortVisibility
{
	InGameUI = 1,
	ScoreBord,
	PauseMenu,
	ResultsMenu
};

/**
 * 
 */
UCLASS()
class DELIVERYRUSH_API AInGameHUD : public AHUD
{
	GENERATED_BODY()
public:
	AInGameHUD();

	UPROPERTY(EditDefaultsOnly, Category= "Desgin")
	TSubclassOf<UScoreBoardWidget> ScoreBoardWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category= "Desgin")
	TSubclassOf<UInGameUI> InGameUIWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category= "Desgin")
	TSubclassOf<UResultWindowWidget> ResultWindowWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category= "Desgin")
	TSubclassOf<UPauseMenuWidget> PauseMenuWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Assets")
	TMap<FString, UTexture2D*> PlayerTypesIcons;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundBase* EndGameSound;


	/**
	 *
	 * Search for the PlayerIcon by TypeName,
	 * return PlayerIcon if PlayerType is correct and
	 * return nullptr otherwise
	 */
	UTexture2D* GetPlayerIcon(FString PlayerType);

	UFUNCTION()
	void ShowScoreBoard();

	UFUNCTION()
	void HideScoreBoard();

	UFUNCTION()
	void ShowPauseMenu();

	UFUNCTION()
	void HidePauseMenu();

	UFUNCTION()
	void ShowResultScreen();

	UPROPERTY()
	UInGameUI* InGameUIWidget;

	void ClearHUD();
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	UScoreBoardWidget* ScoreBoardWidget;

	UPROPERTY()
	UResultWindowWidget* ResultWindowWidget;

	UPROPERTY()
	UPauseMenuWidget* PauseMenuWidget;

	FTimerHandle ClockTickHandle;
	
	void CreateInGameUI();
	void CreateScoreBored();
	void CreateResultsWindowWidget();
	void CreatePauseMenu();
	ASoundManager* TryGetSoundManager();
	void PlayEndGameSound();
};
