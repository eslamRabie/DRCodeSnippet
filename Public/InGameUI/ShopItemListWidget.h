// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Shop.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

#include "ShopItemListWidget.generated.h"

/**
 * 
 */

class UShopMenuWidget;

UCLASS()
class DELIVERYRUSH_API UShopItemListWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void Init(UShopMenuWidget* InParent, FShopItem* InShopItem);	

	UFUNCTION()
	void OnItemClick();

	
	FShopItem* ShopItem;

protected:
	
	virtual bool Initialize() override;
	
private:

	UPROPERTY()
	UShopMenuWidget* ShopParent;
	
	UPROPERTY(meta = (BindWidget))
	UButton* ItemButton;

	UPROPERTY(meta = (BindWidget))
	UImage* ItemImage;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemPriceText;
	
};
