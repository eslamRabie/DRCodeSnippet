// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShopItemWidget.generated.h"

/**
 *
 */
UCLASS()
class DELIVERYRUSH_API UShopItemWidget : public UUserWidget
{
	GENERATED_BODY()

		virtual void NativeConstruct() override;
	UPROPERTY(meta = (BindWidget))
		class UButton* BuyButton;
	UPROPERTY(meta = (BindWidget))
		class UImage* ItemImage;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* PriceText;
	UPROPERTY(meta = (BindWidget))
		class UImage* CoinImage;
	class FPowerUpItem* Item;
public:
	void SetPowerUpItem(FPowerUpItem* inItem);
	void TryToBuyItem();
};
