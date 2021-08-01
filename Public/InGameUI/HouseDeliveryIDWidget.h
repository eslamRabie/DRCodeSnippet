// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"

#include "HouseDeliveryIDWidget.generated.h"

/**
 * 
 */
UCLASS()
class DELIVERYRUSH_API UHouseDeliveryIDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	void SetImageBrush(UTexture2D* IconTex);

private:

	UPROPERTY(meta = (BindWidget))
	UImage* IDImage;


	
};