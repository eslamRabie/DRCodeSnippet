// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUpItem.h"


FPowerUpItem::FPowerUpItem(const TSubclassOf<UDRPowerUpBase>& InPowerUpClass, UTexture2D* InIcon, int32 InPowerUpPrice, int32 InQuantity)
{
	PowerUpClass = InPowerUpClass;
	Price = InPowerUpPrice;
	Quantity = InQuantity;
	Icon = InIcon;
}


FPowerUpItem::~FPowerUpItem()
{
}

int FPowerUpItem::GetPrice()
{
	return Price;
}

int FPowerUpItem::GetQuantity()
{
	return Quantity;
}

void FPowerUpItem::AddQuantity(int InQuantity)
{
	Quantity += InQuantity;
}

UDRPowerUpBase* FPowerUpItem::CreatePowerUpInstance(UObject* Outer)
{
	if(!PowerUpClass) return nullptr;
		
	if(Quantity>0)
	{
		Quantity--;
		return NewObject<UDRPowerUpBase>(Outer, PowerUpClass);
	}

	return nullptr;
		
}

UTexture2D* FPowerUpItem::GetIcon()
{
	return Icon;
}
