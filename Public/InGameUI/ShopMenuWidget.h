// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Shop.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/WrapBox.h"

#include "ShopMenuWidget.generated.h"

/**
 * 
 */

class UShopItemListWidget;

UCLASS()
class DELIVERYRUSH_API UShopMenuWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta = (BindWidget))
	UImage* ItemImage;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemPriceText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemDescriptionText;
	
	UFUNCTION()
	void OnBuyItemButtonClicked();

	UFUNCTION()
	void OnExit();

	UPROPERTY()
	UShopItemListWidget* CurrentShopItem;
	
protected:
	
	virtual bool Initialize() override;

	virtual void NativeConstruct() override;


private:
	/**************************************************/

	UPROPERTY(meta = (BindWidget))
	UButton* BuyItemButton;

	UPROPERTY(meta = (BindWidget))
	UButton* ExitButton;

	UPROPERTY(meta = (BindWidget))
	UWrapBox* ShopTileView;

	UPROPERTY(EditDefaultsOnly, Category=Defaults)
	TSubclassOf<UShopItemListWidget> ShopItemListWidgetClass;


	UPROPERTY(EditDefaultsOnly, Category=Defaults)
	TSubclassOf<UShop> GameShopClass;

	/**************************************************/
	
	UPROPERTY()
	UShop* Shop;

	void CreateShopItemListWidget(FShopItem* ShopItem);
	
};
