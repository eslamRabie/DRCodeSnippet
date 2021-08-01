// Fill out your copyright notice in the Description page of Project Settings.


#include "Shop.h"

#include "Inventory.h"
#include "PowerUpItem.h"


TArray<FShopItem*> UShop::GetShopItemsList()
{
	if(ShopItemsList.Num() <= 0)
		UE_LOG(LogTemp, Error, TEXT(" Empty ShopItemsList in: FPowerUpItem::GetShopItemsList"))

	if(ShopItemsList.Num() != ShopItemsRef.Num())
	{
		for(auto& Item: ShopItemsList)
		{
			ShopItemsRef.Add(&Item);
		}
	}
	return ShopItemsRef;
}

int32 UShop::GetItemPrice(const TSubclassOf<UDRPowerUpBase>& ItemPowerUpClass)
{
	FShopItem* ShopItem = nullptr;
	for(auto& Item: ShopItemsList)
	{
		if(Item.PowerUpClass == ItemPowerUpClass)
		{
			ShopItem = &Item;
			break;
		}
	}
	if(!ShopItem)
	{
		UE_LOG(LogTemp, Error, TEXT("No Shop Item Found for the PowerUpClass Provided in: FPowerUpItem::BuyItem "))
		return -1;
	}
	return ShopItem->PowerUpPrice;
}

int32 UShop::GetItemPrice(int32 ItemIndex)
{
	if(ItemIndex < 0 && ItemIndex >= ShopItemsList.Num()) return -1;
	const auto ShopItem = ShopItemsList[ItemIndex];
	return ShopItem.PowerUpPrice; 
}

UTexture2D* UShop::GetItemIcon(const TSubclassOf<UDRPowerUpBase>& ItemPowerUpClass)
{
	const FShopItem* ShopItem = nullptr;
	for(auto& Item: ShopItemsList)
	{
		if(Item.PowerUpClass == ItemPowerUpClass)
		{
			ShopItem = &Item;
			break;
		}
	}
	if(!ShopItem)
	{
		UE_LOG(LogTemp, Error, TEXT("No Shop Item Found for the PowerUpClass Provided in: FPowerUpItem::BuyItem "))
		return nullptr;
	}
	return ShopItem->PowerUpIcon;
}

UTexture2D* UShop::GetItemIcon(int32 ItemIndex)
{
	if(ItemIndex < 0 && ItemIndex >= ShopItemsList.Num()) return nullptr;
	const auto ShopItem = ShopItemsList[ItemIndex];
	return ShopItem.PowerUpIcon; 
}

FString UShop::GetItemDescription(const TSubclassOf<UDRPowerUpBase>& ItemPowerUpClass)
{
	const FShopItem* ShopItem = nullptr;
	for(auto& Item: ShopItemsList)
	{
		if(Item.PowerUpClass == ItemPowerUpClass)
		{
			ShopItem = &Item;
			break;
		}
	}
	if(!ShopItem)
	{
		UE_LOG(LogTemp, Error, TEXT("No Shop Item Found for the PowerUpClass Provided in: FPowerUpItem::BuyItem "))
		return "";
	}
	return ShopItem->ItemDescription;
}

FString UShop::GetItemDescription(int32 ItemIndex)
{
	if(ItemIndex < 0 && ItemIndex >= ShopItemsList.Num()) return "";
	const auto ShopItem = ShopItemsList[ItemIndex];
	return ShopItem.ItemDescription; 
}

//todo manage memory
bool UShop::BuyItem(int32 ItemIndex, FInventory* Inventory)
{
	if(ItemIndex < 0 && ItemIndex >= ShopItemsList.Num())
	{
		return false;
	}

	if(!Inventory)
	{
		UE_LOG(LogTemp, Error, TEXT("Inventory is NULL in UShop::BuyItem"));
		return false;
	}
	
	auto ShopItem = &ShopItemsList[ItemIndex];
	
	auto Item = new FPowerUpItem(ShopItem->PowerUpClass, ShopItem->PowerUpIcon, ShopItem->PowerUpPrice, 1);

	if(!Item)
	{
		return false;
	}
	
	if(Inventory->GetCoins() < ShopItem->PowerUpPrice)
	{
		UE_LOG(LogTemp, Error, TEXT("Player Dont have enough coins to buy Item"));
		return false;
	}
	
	if(!Inventory->AddPowerUpItem(Item, ShopItem->PowerUpPrice))
	{
		if(Item)
		{
			delete Item;
		}
	}
	
	return true;
	
}

bool UShop::BuyItem(const TSubclassOf<UDRPowerUpBase>& ItemPowerUpClass, FInventory* Inventory)
{
	if(!Inventory)
	{
		UE_LOG(LogTemp, Error, TEXT("Inventory is nullptr in UShop::BuyItem -> TSubclassOf<UDRPowerUpBase>"));
		return false;
	}
	
	const FShopItem* ShopItem = nullptr;
	for(auto& Item: ShopItemsList)
	{
		if(Item.PowerUpClass == ItemPowerUpClass)
		{
			ShopItem = &Item;
			break;
		}
	}
	if(!ShopItem)
	{
		UE_LOG(LogTemp, Error, TEXT("No Shop Item Found for the PowerUpClass Provided in: UShop::BuyItem "))
		return false;
	}
	
	auto Item = new FPowerUpItem(ItemPowerUpClass, ShopItem->PowerUpIcon, ShopItem->PowerUpPrice, 1);

	if(!Item)
	{
		return false;
	}

	if(Inventory->GetCoins() < ShopItem->PowerUpPrice)
	{
		UE_LOG(LogTemp, Error, TEXT("Player Dont have enough coins to buy Item"));
		return false;
	}
	
	if(!Inventory->AddPowerUpItem(Item, ShopItem->PowerUpPrice))
	{
		if(Item)
		{
			delete Item;
		}
	}
	
	return true;
	
}

