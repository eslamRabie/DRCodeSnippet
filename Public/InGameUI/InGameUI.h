// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ShopMenuWidget.h"
#include "NotificationWidget.h"
#include "Blueprint/UserWidget.h"
#include "UMG.h"

#include "InGameUI.generated.h"

/**
 * 
 */


class FInventory;
class ADRInGamePlayerState;
class ADRGameState;
class UPowerUpItemButtonWidget;

UCLASS(Blueprintable)
class DELIVERYRUSH_API UInGameUI : public UUserWidget
{
	GENERATED_BODY()
public:
	
	virtual bool Initialize() override;

	UFUNCTION()
	void OnShopButtonClicked();

	UFUNCTION()
	void OnPowerUpBGHover();

	UFUNCTION()
	void OnPowerUpBGStopHover();
	

	void UpDateScore(int32 NewScore);

	void UpdateCoins(int32 NewCoins);

	void UpdateInventory();

	bool ShowPlayerData();

	UPROPERTY(meta = (BindWidget))
	UNotificationWidget* NotificationWidget;

private:

	UPROPERTY(meta = (BindWidget))
	UOverlay* ShopWidgetOverlay;
		
	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* PowerUpsBox;

	UPROPERTY(meta = (BindWidget))
	UImage* PlayerTypeIcon;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayerNameText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayerScoreText;

	UPROPERTY(meta = (BindWidget))
	UButton* ShopButton;

	UPROPERTY(meta = (BindWidget))
	USizeBox* GameModeNotificationArea;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CoinsCount;

	UPROPERTY(meta = (BindWidget))
	UButton* PowerUpBG;
	
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* PlayerCoinsAddAnimation;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* PlayerScoreChangeAnimation;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* PlayerCoinsDecreaseAnimation;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* ShowPowerUpBG;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* HidePowerUpBG;

	UPROPERTY(EditDefaultsOnly, Category = "Defaults")
	TSubclassOf<UPowerUpItemButtonWidget> PowerUpItemButtonWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Defaults")
	TSubclassOf<UShopMenuWidget> ShopMenuWidgetClass;

	UPROPERTY()
	ADRInGamePlayerState* PlayerState;

	UPROPERTY()
	UPowerUpItemButtonWidget* PowerUpItemButtonWidget;

	UPROPERTY()
	UShopMenuWidget* ShopMenuWidget;


	void ShowPlayerPowerUps();
};
