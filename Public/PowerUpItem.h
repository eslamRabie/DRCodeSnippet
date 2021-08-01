// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRPowerUpBase.h"

class DELIVERYRUSH_API FPowerUpItem 
{


public:
	FPowerUpItem(const TSubclassOf<UDRPowerUpBase>& InPowerUpClass, UTexture2D* InIcon, int32 InPowerUpPrice, int32 InQuantity = 1);

	FPowerUpItem(const FPowerUpItem& Other)
		: PowerUpClass(Other.PowerUpClass),
		  Price(Other.Price),
		  Quantity(Other.Quantity),
		  Icon(Other.Icon)
	{
	}

	FPowerUpItem(FPowerUpItem&& Other) noexcept
		: PowerUpClass(std::move(Other.PowerUpClass)),
		  Price(Other.Price),
		  Quantity(Other.Quantity),
		  Icon(Other.Icon)
	{
	}

	FPowerUpItem& operator=(const FPowerUpItem& Other)
	{
		if (this == &Other)
			return *this;
		PowerUpClass = Other.PowerUpClass;
		Price = Other.Price;
		Quantity = Other.Quantity;
		Icon = Other.Icon;
		return *this;
	}

	FPowerUpItem& operator=(FPowerUpItem&& Other) noexcept
	{
		if (this == &Other)
			return *this;
		PowerUpClass = std::move(Other.PowerUpClass);
		Price = Other.Price;
		Quantity = Other.Quantity;
		Icon = Other.Icon;
		return *this;
	}

	friend bool operator==(const FPowerUpItem& Lhs, const FPowerUpItem& RHS)
	{
		return Lhs.PowerUpClass == RHS.PowerUpClass;
	}
	
	friend bool operator!=(const FPowerUpItem& Lhs, const FPowerUpItem& RHS)
	{
		return !(Lhs == RHS);
	}

	
	~FPowerUpItem();

	int32 GetPrice();

	int32 GetQuantity();

	void AddQuantity(int32 InQuantity = 1);
	
	UDRPowerUpBase* CreatePowerUpInstance(UObject* Outer);

	UTexture2D* GetIcon();

	
private:
	TSubclassOf<UDRPowerUpBase> PowerUpClass;
	int32 Price = 0;
	int32 Quantity = 0;
	UTexture2D* Icon;

};
