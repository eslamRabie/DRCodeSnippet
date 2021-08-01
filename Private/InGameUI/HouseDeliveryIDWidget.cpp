// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameUI/HouseDeliveryIDWidget.h"

void UHouseDeliveryIDWidget::SetImageBrush(UTexture2D* IconTex)
{
	if(!IconTex)
	{
		UE_LOG(LogTemp, Error, TEXT("IconTex is nullptr in: UHouseDeliveryIDWidget::SetImageBrush in: %s"), *GetName());
		return;
	}
	if(!IDImage)
	{
		UE_LOG(LogTemp, Error, TEXT("IDImage is nullptr in: UHouseDeliveryIDWidget::SetImageBrush in: %s"), *GetName());
		return;
	}
	IDImage->SetBrushFromTexture(IconTex);
}
