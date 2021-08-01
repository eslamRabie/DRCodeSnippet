// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopItemWidget.h"
#include "Components/Image.h"
#include "PowerUpItem.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "..\Public\ShopItemWidget.h"

void UShopItemWidget::NativeConstruct()
{
	Super::NativeConstruct();
	//CoinImage->setbrushform texture get coin image from hud
	if (BuyButton)
	{
		BuyButton->OnClicked.AddDynamic(this, &UShopItemWidget::TryToBuyItem);
	}
}

void UShopItemWidget::SetPowerUpItem(FPowerUpItem* inItem)
{
	if (inItem)
	{
		Item = inItem;
		if (PriceText)
		{
			PriceText->SetText(FText::FromName(FName(FString::FromInt(Item->GetPrice()))));
		}
		if (ItemImage)
		{
			//ItemImage->setvrushfromtexture Item->PowerUpIndex from hud
		}
	}
}

void UShopItemWidget::TryToBuyItem()
{
	if (Item)
	{
		//try to buy it from server
	}
}
