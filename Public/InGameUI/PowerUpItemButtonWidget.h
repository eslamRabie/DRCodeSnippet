// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

#include "PowerUpItemButtonWidget.generated.h"

class FPowerUpItem;
/**
 * 
 */
UCLASS()
class DELIVERYRUSH_API UPowerUpItemButtonWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UButton* PowerUpButton;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UImage* PowerUpIcon;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UTextBlock* PowerUpCountText;

	virtual void NativeConstruct() override;

	void CreateButton(FPowerUpItem*  InPowerUpItem);

	UFUNCTION()
	void OnUsePowerUpButtonClicked();

	
private:

	FPowerUpItem* ThisPowerUpItem;


	bool bIsBound = false;
	
	
};
