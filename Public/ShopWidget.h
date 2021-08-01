// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShopWidget.generated.h"

/**
 *
 */
UCLASS()
class DELIVERYRUSH_API UShopWidget : public UUserWidget
{
	GENERATED_BODY()

		virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
		class UButton* ExitButton;

	UPROPERTY(meta = (BindWidget))
		class UUniformGridPanel* PowerupsGrid;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UShopItemWidget> ItemWidgetClass;

	TArray<class FPowerUpItem*> ItemsArray;
	
	void CloseShop();

};
