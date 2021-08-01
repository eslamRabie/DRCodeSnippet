// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PowerUpItem.h"

/**
 * 
 */
class DELIVERYRUSH_API FInventory 
{
public:

	FInventory();
	
	FInventory(const TArray<FPowerUpItem*>& InItems, int InCoins = 0);
	
	~FInventory();

	int32 GetCoins();

	void AddCoins(int32 InCoins);

	/**
	 * Try Add PowerUpItem to Inventory and deduct the cost from it;
	 * return true if added successfully
	 * return false if item already exists <<But increase the Item Count>>
	 * and false if item cannot be added to Inventory
	 */
	bool AddPowerUpItem(FPowerUpItem* InItem, int32 Cost);

	bool RemoveItem(FPowerUpItem* InItem);

	FPowerUpItem* GetItemAtIndex(int32 InIndex);

	TArray<FPowerUpItem*> GetAllItems();

private:
	int Coins;
	TArray<FPowerUpItem*> OwnedItems;

	
};
