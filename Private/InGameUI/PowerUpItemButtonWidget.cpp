// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameUI/PowerUpItemButtonWidget.h"

#include "DRInGamePlayerController.h"
#include "DRInGamePlayerState.h"
#include "DRPowerUpBase.h"


void UPowerUpItemButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(!bIsBound)
	{
		if(!PowerUpButton) return;
		PowerUpButton->OnClicked.AddDynamic(this, &UPowerUpItemButtonWidget::OnUsePowerUpButtonClicked);
	}
}

void UPowerUpItemButtonWidget::CreateButton(FPowerUpItem* InPowerUpItem)
{
	if(!InPowerUpItem)
	{
		UE_LOG(LogTemp, Error, TEXT("InPowerUpItem is nullptr in : %s"), *GetName());
		return;
	}
	ThisPowerUpItem = InPowerUpItem;

	PowerUpIcon->SetBrushFromTexture(ThisPowerUpItem->GetIcon());

	PowerUpCountText->SetText(FText::FromString(FString::FromInt(ThisPowerUpItem->GetQuantity())));
		
}

void UPowerUpItemButtonWidget::OnUsePowerUpButtonClicked()
{
	auto World = GetWorld();
	if(!World)
	{
		UE_LOG(LogTemp, Error, TEXT("World is nullptr in : UPowerUpItemButtonWidget::OnUsePowerUpButtonClicked"));
		return;
	}
	
	auto PC =GetOwningPlayer<ADRInGamePlayerController>();
	auto PS = GetOwningPlayerState<ADRInGamePlayerState>();

	if(!PC || !PS)
	{
		UE_LOG(LogTemp, Error, TEXT("PC or PS is nullptr in : UPowerUpItemButtonWidget::OnUsePowerUpButtonClicked"));
		return;
	}

	if(PC->CurrentPowerUP)
	{
		if(*ThisPowerUpItem == *PC->CurrentPowerUpItem)
		{
			ThisPowerUpItem->AddQuantity();
			PC->CurrentPowerUP = nullptr;
			PC->CurrentPowerUpItem = nullptr;
			PS->UpdateInventoryView();
			return;
		}
		else
		{
			PC->CurrentPowerUpItem->AddQuantity();	
		}
	}
	
	auto PowerUp = ThisPowerUpItem->CreatePowerUpInstance(World);
	if(!PowerUp)
	{
		if(ThisPowerUpItem->GetQuantity() <= 0)
		{
			PS->GetInventory()->RemoveItem(ThisPowerUpItem);
			RemoveFromParent();
		}
		return;
	}
	
	PC->CurrentPowerUP = PowerUp;
	PC->CurrentPowerUpItem = ThisPowerUpItem;

	PS->UpdateInventoryView();
}
