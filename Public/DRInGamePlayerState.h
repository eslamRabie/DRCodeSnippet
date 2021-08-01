// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include <stdbool.h>

#include "DRPlayerStateBase.h"
#include "Inventory.h"
#include "InGameUI/InGameHUD.h"
#include "InGameUI/NotificationWidget.h"

#include "DRInGamePlayerState.generated.h"

/**
 * 
 */
UCLASS()
class DELIVERYRUSH_API ADRInGamePlayerState : public ADRPlayerStateBase
{
	GENERATED_BODY()

public:

	ADRInGamePlayerState();

	virtual void Tick(float DeltaSeconds) override;

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

	UFUNCTION(Client, Reliable)
	void EndGame();

	UFUNCTION(Client, Reliable)
	void ResetHUD();

	UFUNCTION(Client, Reliable)
	void StartNotification(EGameModes InWidgetGameMode, int32 InitVal);

	UFUNCTION(Client, Reliable)
	void UpdateNotification(int32 Val);

	UFUNCTION(Client, Reliable)
	void OnUpdateCoins(int32 Coins);

	UFUNCTION(NetMulticast, Reliable)
	void ApplyPowerUpToAll(AActor* AffectedActor, TSubclassOf<UDRPowerUpBase> PowerUpClass);

	UFUNCTION(Client, Reliable)
	void PlayScoreSound();

	UFUNCTION(Client, Reliable)
	void PlayDoubleScoreSound();

	UFUNCTION(Client, Reliable)
	void PlayGoldenCarSound();

	UFUNCTION(Client, Reliable)
	void PlayBankSound();

	UFUNCTION(Client, Reliable)
	void PlayMissScoreSound();

	virtual void CopyProperties(APlayerState* PlayerState) override;
	
	
	void UpdateInventoryView();

	FInventory* GetInventory();

	virtual void OnRep_Score() override;

	/***********************************
	 * 
	 */
	
	UPROPERTY(Replicated)
	int32 Rank;

	UPROPERTY()
	UTexture2D* PlayerIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Sound)
	USoundBase* ScoreSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Sound)
	USoundBase* DoubleScoreSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Sound)
	USoundBase* BankScoreSound;;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Sound)
	USoundBase* GoldenCarScoreSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Sound)
	USoundBase* MissScoreSound;


	

protected:
	virtual void BeginPlay() override;

private:


	// Sound Manager

	ASoundManager* TryGetSoundManager();
	void InitPlayerIcon();
	bool InitializeNotificationWidget();
	



	//todo: replicate inventory
	FInventory PlayerInventory;

	bool bIsNotificationWidgetInitialized = false;
	bool bIsNotificationWidgetFinishedInitialization = false;
	bool bIsPlayerIconInit = false;

	UPROPERTY()
	AInGameHUD* HUD;

	EGameModes WidgetGameMode;
	int32 WidgetGameModeInitVal;

	
	/**
	 * For Sorting the PlayerArray
	 */

public:
	friend bool operator<(const ADRInGamePlayerState& Lhs, const ADRInGamePlayerState& RHS)
	{
		return Lhs.GetScore() > RHS.GetScore();
	}

	friend bool operator<=(const ADRInGamePlayerState& Lhs, const ADRInGamePlayerState& RHS)
	{
		return !(RHS < Lhs);
	}

	friend bool operator>(const ADRInGamePlayerState& Lhs, const ADRInGamePlayerState& RHS)
	{
		return RHS < Lhs;
	}

	friend bool operator>=(const ADRInGamePlayerState& Lhs, const ADRInGamePlayerState& RHS)
	{
		return !(Lhs < RHS);
	}


	
	
};
