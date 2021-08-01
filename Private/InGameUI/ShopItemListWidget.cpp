// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameUI/ShopItemListWidget.h"

#include "InGameUI/ShopMenuWidget.h"


bool UShopItemListWidget::Initialize()
{
	Super::Initialize();
	if (!ItemButton || !ItemImage || !ItemPriceText)
	{
		UE_LOG(LogTemp, Error, TEXT("Some Widgets not assigned in BP in: UShopItemListWidget::Initialize"))
		return false;
	}
	ItemButton->OnClicked.AddDynamic(this, &UShopItemListWidget::OnItemClick);
	return true;
}

void UShopItemListWidget::Init(UShopMenuWidget* InParent, FShopItem* InShopItem)
{
	if (!InParent)
	{
		UE_LOG(LogTemp, Error, TEXT("InParent is nullptr in: UShopItemListWidget::OnItemClick"));
		return;
	}
	if (!InShopItem)
	{
		UE_LOG(LogTemp, Error, TEXT("InShopItem is nullptr in: UShopItemListWidget::OnItemClick"));
		return;
	}


	ShopParent = InParent;
	ShopItem = InShopItem;

	ItemImage->SetBrushFromTexture(ShopItem->PowerUpIconShop);
	ItemPriceText->SetText(FText::FromString(FString::FromInt(ShopItem->PowerUpPrice)));
}

void UShopItemListWidget::OnItemClick()
{
	if (!ShopParent)
	{
		UE_LOG(LogTemp, Error, TEXT("Parent is a nullptr UShopItemListWidget::OnItemClick in:%s"), *GetName());
		return;
	}
	ShopParent->CurrentShopItem = this;
	ShopParent->ItemImage->SetBrushFromTexture(ShopItem->PowerUpIconShop);
	ShopParent->ItemDescriptionText->SetText(FText::FromString(ShopItem->ItemDescription));
	ShopParent->ItemPriceText->SetText(FText::FromString(FString::FromInt(ShopItem->PowerUpPrice)));
}
