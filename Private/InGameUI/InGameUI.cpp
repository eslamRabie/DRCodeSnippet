// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameUI/InGameUI.h"

#include <DRInGamePlayerState.h>
#include "InGameUI/PowerUpItemButtonWidget.h"

bool UInGameUI::Initialize()
{
	if (!Super::Initialize())
	{
		UE_LOG(LogTemp, Error, TEXT("Initialize Super in: %s"), *GetName());
		return false;
	}

	if (!ShopButton || !PowerUpBG)
	{
		UE_LOG(LogTemp, Error, TEXT("Some Widgets not handled in BP in: %s"), *GetName());
		return false;
	}
	
	ShopButton->OnClicked.AddDynamic(this, &UInGameUI::OnShopButtonClicked);
	PowerUpBG->OnHovered.AddDynamic(this, &UInGameUI::OnPowerUpBGHover);
	PowerUpBG->OnUnhovered.AddDynamic(this, &UInGameUI::OnPowerUpBGStopHover);
	
	
	return true;
}


void UInGameUI::OnShopButtonClicked()
{
	/*
	if (!ShopMenuWidget)
	{
		if (!ShopMenuWidgetClass)
		{
			UE_LOG(LogTemp, Error, TEXT("ShopMenuWidgetClass not handled in BP in: %s"), *GetName());
			return;
		}

		if (!GetWorld()) UE_LOG(LogTemp, Error, TEXT("Cant Get World in OnShopButtonClicked in: %s"), *GetName());

		ShopMenuWidget = CreateWidget<UShopMenuWidget>(GetWorld(), ShopMenuWidgetClass);

		if (!ShopMenuWidget)
		{
			UE_LOG(LogTemp, Error, TEXT("Cant Create ShopMenuWidget in: %s"), *GetName());
			return;
		}
		ShopMenuWidget->SetAnchorsInViewport(FAnchors(0.5, 0.5));
		ShopMenuWidget->SetAlignmentInViewport(FVector2D(0.5, 0.5));
	}
	*/
	
	if (ShopWidgetOverlay->GetVisibility() != ESlateVisibility::Visible)
	{
		ShopWidgetOverlay->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		ShopWidgetOverlay->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UInGameUI::OnPowerUpBGHover()
{
	PlayAnimation(ShowPowerUpBG);
	PowerUpsBox->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	
}

void UInGameUI::OnPowerUpBGStopHover()
{
	PowerUpsBox->SetVisibility(ESlateVisibility::Collapsed);
	PlayAnimation(HidePowerUpBG);
}


void UInGameUI::UpDateScore(int32 NewScore)
{
	PlayerScoreText->SetText(FText::FromString(FString::FromInt(NewScore)));
	PlayAnimation(PlayerScoreChangeAnimation);
}

void UInGameUI::UpdateCoins(int32 NewCoins)
{
	//Update Coins On UI
	if(NewCoins < 0)
	{
		NewCoins *= -1;
		CoinsCount->SetText(FText::FromString(FString::FromInt(NewCoins)));
		PlayAnimation(PlayerCoinsDecreaseAnimation);		
	}
	else
	{
		CoinsCount->SetText(FText::FromString(FString::FromInt(NewCoins)));
		PlayAnimation(PlayerCoinsAddAnimation);	
	}

}

void UInGameUI::UpdateInventory()
{
	ShowPlayerPowerUps();
}

void UInGameUI::ShowPlayerPowerUps()
{
	if (!PlayerState)
	{
		PlayerState = GetOwningPlayerState<ADRInGamePlayerState>();
		if (!PlayerState)
		{
			UE_LOG(LogTemp, Error, TEXT("PlayerState is nullptr UInGameUI::ShowPlayerPowerUps"));
			return;
		}
	}

	PowerUpsBox->ClearChildren();

	if (PowerUpItemButtonWidgetClass)
	{
		if (!GetWorld())
		{
			UE_LOG(LogTemp, Error, TEXT("Cant Get World in ShowPlayerPowerUps in: %s"), *GetName());
			return;
		}
		if (PlayerState->GetInventory())
		{
			for (FPowerUpItem* Item : PlayerState->GetInventory()->GetAllItems())
			{
				PowerUpItemButtonWidget = CreateWidget<UPowerUpItemButtonWidget>(
					GetWorld(), PowerUpItemButtonWidgetClass);
				if (!PowerUpItemButtonWidget)
				{
					UE_LOG(LogTemp, Error, TEXT("PowerUpItemButtonWidget is nullptr in: %s"), *GetName());
				}
				else
				{
					PowerUpItemButtonWidget->CreateButton(Item);
					PowerUpsBox->AddChild(PowerUpItemButtonWidget);
				}
			}
		}
	}
}

bool UInGameUI::ShowPlayerData()
{
	if (!PlayerState)
	{
		PlayerState = GetOwningPlayerState<ADRInGamePlayerState>();
		if (!PlayerState)
		{
			UE_LOG(LogTemp, Error, TEXT("InPlayerState is nullptr in: UInGameUI::ShowPlayerData"));
			return false;
		}
	}
	if (!PlayerTypeIcon || !PlayerNameText || !PlayerScoreText)
	{
		UE_LOG(LogTemp, Error, TEXT("InPlayerState is nullptr in: UInGameUI::ShowPlayerData"));
		return false;
	}
	PlayerNameText->SetText(FText::FromString(PlayerState->GetPlayerName()));
	PlayerScoreText->SetText(FText::FromString(FString::FromInt(PlayerState->GetScore())));
	PlayerTypeIcon->SetBrushFromTexture(PlayerState->PlayerIcon);
	return true;
}
