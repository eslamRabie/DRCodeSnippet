// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopWidget.h"
#include "Components/UniformGridPanel.h"
#include "Components/Button.h"
#include "PowerUpItem.h"

void UShopWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (ExitButton)
	{
		ExitButton->OnClicked.AddDynamic(this, &UShopWidget::CloseShop);
	}
	//getinventory and all items in items array
	//for each item create widget and put it child to grid
}

void UShopWidget::CloseShop()
{
	RemoveFromParent();
}
