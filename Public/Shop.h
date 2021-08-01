// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DRPowerUpBase.h"
#include "Shop.generated.h"

/**
 * 
 */

class FInventory;
class FPowerUpItem;



USTRUCT(BlueprintType)
struct FShopItem
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category=Data)
	TSubclassOf<UDRPowerUpBase> PowerUpClass;

	UPROPERTY(EditDefaultsOnly, Category=Data)
	int32 PowerUpPrice;

	UPROPERTY(EditDefaultsOnly, Category=Data)
	UTexture2D* PowerUpIcon;

	UPROPERTY(EditDefaultsOnly, Category=Data)
	UTexture2D* PowerUpIconShop;


	UPROPERTY(EditDefaultsOnly, Category=Data)
	FString ItemDescription;

	FShopItem() = default;

	FShopItem(const FShopItem& Other)
		: PowerUpClass(Other.PowerUpClass),
		  PowerUpPrice(Other.PowerUpPrice),
		  PowerUpIcon(Other.PowerUpIcon),
		  ItemDescription(Other.ItemDescription)
	{
	}


	FShopItem(FShopItem&& Other) noexcept
		: PowerUpClass(std::move(Other.PowerUpClass)),
		  PowerUpPrice(Other.PowerUpPrice),
		  PowerUpIcon(Other.PowerUpIcon),
		  ItemDescription(std::move(Other.ItemDescription))
	{
	}

	FShopItem& operator=(const FShopItem& Other)
	{
		if (this == &Other)
			return *this;
		PowerUpClass = Other.PowerUpClass;
		PowerUpPrice = Other.PowerUpPrice;
		PowerUpIcon = Other.PowerUpIcon;
		ItemDescription = Other.ItemDescription;
		return *this;
	}

	FShopItem& operator=(FShopItem&& Other) noexcept
	{
		if (this == &Other)
			return *this;
		PowerUpClass = std::move(Other.PowerUpClass);
		PowerUpPrice = Other.PowerUpPrice;
		PowerUpIcon = Other.PowerUpIcon;
		ItemDescription = std::move(Other.ItemDescription);
		return *this;
	}

	friend bool operator==(const FShopItem& Lhs, const FShopItem& RHS)
	{
		return Lhs.PowerUpClass == RHS.PowerUpClass;
	}

	friend bool operator!=(const FShopItem& Lhs, const FShopItem& RHS)
	{
		return !(Lhs == RHS);
	}
};

UCLASS(Blueprintable)
class DELIVERYRUSH_API UShop : public UObject
{
	GENERATED_BODY()

public:

	
	
	TArray<FShopItem*> GetShopItemsList();

	int32 GetItemPrice(const TSubclassOf<UDRPowerUpBase>& ItemPowerUpClass);

	int32 GetItemPrice(int32 ItemIndex);

	UTexture2D* GetItemIcon(const TSubclassOf<UDRPowerUpBase>& ItemPowerUpClass);

	UTexture2D* GetItemIcon(int32 ItemIndex);

	FString GetItemDescription(const TSubclassOf<UDRPowerUpBase>& ItemPowerUpClass);

	FString GetItemDescription(int32 ItemIndex);

	/**
	* The Inventory class must manage the PowerUpItems pointers Created    
	*/
	bool BuyItem(int32 ItemIndex, FInventory* Inventory);

	/**
	 * The Inventory class must manage the PowerUpItems pointers Created    
	 */
	bool BuyItem(const TSubclassOf<UDRPowerUpBase>& ItemPowerUpClass, FInventory* Inventory);
	
protected:

private:
	UPROPERTY(EditDefaultsOnly, Category=Data)
	TArray<FShopItem> ShopItemsList;

	TArray<FShopItem*> ShopItemsRef;
	
};
