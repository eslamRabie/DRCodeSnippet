// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"


FInventory::FInventory()
{
	Coins = 0;
}

FInventory::FInventory(const TArray<FPowerUpItem*>& InItems, int InCoins)
{
	Coins = InCoins;
	OwnedItems = InItems;
}

FInventory::~FInventory()
{
	for(auto Item: OwnedItems)
	{
		delete Item;
	}
}

int32 FInventory::GetCoins()
{
	return Coins;
}

void FInventory::AddCoins(int32 InCoins)
{
	if(InCoins > 0)
	{
		Coins += InCoins;
	}
}


bool FInventory::AddPowerUpItem(FPowerUpItem* InItem, int32 Cost)
{
	if(!InItem)
	{
		UE_LOG(LogTemp, Error, TEXT("FPowerUpItem*::InItem is nullptr in: FInventory::AddPowerUpItem"));
		return false;
	}
	Coins -= Cost;
	for(auto Item: OwnedItems)
	{
		if(*Item == *InItem)
		{
			Item->AddQuantity(1);
			return false;
		}
	}
	OwnedItems.Add(InItem);
	return true;
}

bool FInventory::RemoveItem(FPowerUpItem* InItem)
{ 
	if (!InItem)
	{
		return false;
	}
	OwnedItems.Remove(InItem);
	return true;
};


FPowerUpItem* FInventory::GetItemAtIndex(int32 InIndex)
{
	if (InIndex > OwnedItems.Num() && InIndex < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("nullptr in: FInventory::GetItemAtIndex"));
		return nullptr;
	}
	return OwnedItems[InIndex];
}

TArray<FPowerUpItem*> FInventory::GetAllItems()
{
	return OwnedItems;
}



