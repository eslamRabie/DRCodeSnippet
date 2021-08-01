// Fill out your copyright notice in the Description page of Project Settings.


#include "DRInGamePlayerState.h"

#include "DRGameInstance.h"
#include "SoundManager.h"
#include "InGameUI/InGameHUD.h"
#include "InGameUI/InGameUI.h"
#include "Net/UnrealNetwork.h"


/**
 * Basics
 */

ADRInGamePlayerState::ADRInGamePlayerState()
{
	PrimaryActorTick.bCanEverTick = true;

	Rank = 0;
	bIsNotificationWidgetInitialized = false;
	bIsNotificationWidgetFinishedInitialization = false;
	bIsPlayerIconInit = false;
}

void ADRInGamePlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ADRInGamePlayerState, Rank);
}

void ADRInGamePlayerState::BeginPlay()
{
	Super::BeginPlay();

	if (!bIsPlayerIconInit)
		InitPlayerIcon();
}


void ADRInGamePlayerState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bIsNotificationWidgetInitialized && !bIsNotificationWidgetFinishedInitialization)
	{
		UE_LOG(LogTemp, Error, TEXT("ADRInGamePlayerState::Tick"));
		bIsNotificationWidgetFinishedInitialization = InitializeNotificationWidget();
	}

	if (!bIsPlayerIconInit)
	{
		InitPlayerIcon();
	}
}

void ADRInGamePlayerState::CopyProperties(APlayerState* PlayerState)
{
	Super::CopyProperties(PlayerState);

	auto OutPlayerState = Cast<ADRInGamePlayerState>(PlayerState);
	if(!OutPlayerState)
	{
		UE_LOG(LogTemp, Error, TEXT("Cant Cast Player State in: ADRInGamePlayerState::CopyProperties in: %s"), *GetName());
		return;
	}
	OutPlayerState->SetPlayerName(GetPlayerName());
	OutPlayerState->PlayerType = PlayerType;
}

/**
 * Start Game
 */

void ADRInGamePlayerState::InitPlayerIcon()
{
	auto World = GetWorld();

	if (!World)
	{
		UE_LOG(LogTemp, Display, TEXT("Cant GetWorld in : %s"), *GetName());
		return;
	}

	auto PC = World->GetFirstPlayerController();
	if (!PC)
	{
		UE_LOG(LogTemp, Display, TEXT("NULL PC : %s"), *GetName());
		return;
	}
	auto ThisHUD = Cast<AInGameHUD>(PC->GetHUD());
	if (!ThisHUD)
	{
		UE_LOG(LogTemp, Display, TEXT("NULL HUD : %s"), *GetName());
		return;
	}
	HUD = ThisHUD;
	PlayerIcon = ThisHUD->GetPlayerIcon(PlayerType);

	if (!PlayerIcon)
	{
		UE_LOG(LogTemp, Display, TEXT("Cant Have empty Player Icon in : %s"), *GetName());
		return;
	}

	if (!HUD->InGameUIWidget)
	{
		UE_LOG(LogTemp, Display, TEXT("InGameUIWidget is not yet created! in: ADRInGamePlayerState::InitPlayerIcon"));
		return;
	}

	bIsPlayerIconInit = HUD->InGameUIWidget->ShowPlayerData();

	UE_LOG(LogTemp, Display, TEXT("**************/ PlayerIcon Just Init : %s /*************"), *PlayerType);
}

/**
 * Gameplay
 */


void ADRInGamePlayerState::ApplyPowerUpToAll_Implementation(AActor* AffectedActor,
															TSubclassOf<UDRPowerUpBase> PowerUpClass)
{
	if (HasAuthority())
	{
		UE_LOG(LogTemp, Error, TEXT("Server in: %s"), *GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Client in: %s"), *GetName());
	}
	if (!AffectedActor)
	{
		UE_LOG(LogTemp, Error, TEXT("AffectedCar nullptr in ApplyToAll_Implementation in: %s"), *GetName());
		return;
	}
	if (!GetWorld())
	{
		UE_LOG(LogTemp, Error, TEXT("GetWorld nullptr in ApplyToAll_Implementation in: %s"), *GetName());
		return;
	}
	auto PowerUp = NewObject<UDRPowerUpBase>(GetWorld(), PowerUpClass);
	if (!PowerUp)
	{
		UE_LOG(LogTemp, Error, TEXT("PowerUp nullptr in ApplyToAll_Implementation in: %s"), *GetName());
		return;
	}
	PowerUp->StartEffect(AffectedActor);
	UE_LOG(LogTemp, Error, TEXT("ApplyToAll_Implementation apply to all in: %s"), *GetName());
}
void ADRInGamePlayerState::OnRep_Score()
{
	if (HasLocalNetOwner())
		HUD->InGameUIWidget->UpDateScore(GetScore());
}


/**
 * End Game
 */

void ADRInGamePlayerState::EndGame_Implementation()
{
	if (!HUD)
	{
		UE_LOG(LogTemp, Warning, TEXT("NULL HUD ADRInGamePlayerState::EndGame : %s"), *GetName());
		return;
	}

	HUD->ShowResultScreen();
}

void ADRInGamePlayerState::ResetHUD_Implementation()
{
	if(HasLocalNetOwner() && HUD)
	{
		HUD->ClearHUD();
	}
}

/**
 * Notification Widget
 */
void ADRInGamePlayerState::StartNotification_Implementation(EGameModes InWidgetGameMode, int32 InitVal)
{
	this->WidgetGameMode = InWidgetGameMode;
	this->WidgetGameModeInitVal = InitVal;
	bIsNotificationWidgetInitialized = true;
	UE_LOG(LogTemp, Error, TEXT("ADRInGamePlayerState::StartNotification_Implementation"));

}

bool ADRInGamePlayerState::InitializeNotificationWidget()
{
	if (!HUD)
	{
		UE_LOG(LogTemp, Error, TEXT("NULL HUD ADRInGamePlayerState::InitializeNotificationWidget :"));
		return false;
	}
	if (!HUD->InGameUIWidget)
	{
		UE_LOG(LogTemp, Error, TEXT("NULL ADRInGamePlayerState::InitializeNotificationWidget"));
		return false;
	}

	if (!HUD->InGameUIWidget->NotificationWidget)
	{
		UE_LOG(LogTemp, Error, TEXT("NULL ADRInGamePlayerState::InitializeNotificationWidget"));
		return false;
	}

	HUD->InGameUIWidget->NotificationWidget->Start(WidgetGameMode, WidgetGameModeInitVal);
	
	UE_LOG(LogTemp, Error, TEXT("ADRInGamePlayerState::InitializeNotificationWidget"));

	return true;
}

void ADRInGamePlayerState::UpdateNotification_Implementation(int32 Val)
{
	if (!HUD)
	{
		UE_LOG(LogTemp, Error, TEXT("NULL HUD ADRInGamePlayerState::UpdateNotification_Implementation"));
		return;
	}
	if (!HUD->InGameUIWidget)
	{
		UE_LOG(LogTemp, Error, TEXT("NULL ADRInGamePlayerState::UpdateNotification_Implementation"));
		return;
	}

	if (!HUD->InGameUIWidget->NotificationWidget)
	{
		UE_LOG(LogTemp, Error, TEXT("NULL NotificationWidget ADRInGamePlayerState::UpdateNotification_Implementation"));
		return;
	}

	HUD->InGameUIWidget->NotificationWidget->Update(Val);
}

/**
 * Inventory
 */

FInventory* ADRInGamePlayerState::GetInventory()
{
	return &PlayerInventory;
}

void ADRInGamePlayerState::UpdateInventoryView()
{
	HUD->InGameUIWidget->UpdateInventory();
}

void ADRInGamePlayerState::OnUpdateCoins_Implementation(int32 Coins)
{
	if (HasLocalNetOwner())
	{
		PlayerInventory.AddCoins(Coins);
		Coins < 0
			? HUD->InGameUIWidget->UpdateCoins(-PlayerInventory.GetCoins())
			: HUD->InGameUIWidget->UpdateCoins(PlayerInventory.GetCoins());
	}
}

/**
 *
 *	Sounds Effects
 * 
 */

ASoundManager* ADRInGamePlayerState::TryGetSoundManager()
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

void ADRInGamePlayerState::PlayScoreSound_Implementation()
{
	auto SoundManager = TryGetSoundManager();
	if (!SoundManager)
	{
		return;
	}

	if (!ScoreSound)
	{
		UE_LOG(LogTemp, Error, TEXT("ScoreSound Not Set In BP in: %s"), *GetName());
		return;
	}
	SoundManager->PlaySound(ScoreSound, this);
}

void ADRInGamePlayerState::PlayDoubleScoreSound_Implementation()
{
	auto SoundManager = TryGetSoundManager();
	if (!SoundManager)
	{
		return;
	}

	if (!DoubleScoreSound)
	{
		UE_LOG(LogTemp, Error, TEXT("DoubleScoreSound Not Set In BP in: %s"), *GetName());
		return;
	}
	SoundManager->PlaySound(DoubleScoreSound, this);
}

void ADRInGamePlayerState::PlayGoldenCarSound_Implementation()
{
	auto SoundManager = TryGetSoundManager();
	if (!SoundManager)
	{
		return;
	}

	if (!GoldenCarScoreSound)
	{
		UE_LOG(LogTemp, Error, TEXT("GoldenCarScoreSound Not Set In BP in: %s"), *GetName());
		return;
	}
	SoundManager->PlaySound(GoldenCarScoreSound, this);
}

void ADRInGamePlayerState::PlayBankSound_Implementation()
{
	auto SoundManager = TryGetSoundManager();
	if (!SoundManager)
	{
		return;
	}

	if (!BankScoreSound)
	{
		UE_LOG(LogTemp, Error, TEXT("BankScoreSound Not Set In BP in: %s"), *GetName());
		return;
	}
	SoundManager->PlaySound(BankScoreSound, this);
}

void ADRInGamePlayerState::PlayMissScoreSound_Implementation()
{
	auto SoundManager = TryGetSoundManager();
	if (!SoundManager)
	{
		return;
	}

	if (!MissScoreSound)
	{
		UE_LOG(LogTemp, Error, TEXT("MissScoreSound Not Set In BP in: %s"), *GetName());
		return;
	}
	SoundManager->PlaySound(MissScoreSound, this);
}

