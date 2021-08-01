// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameUI/PauseMenuWidget.h"

#include "DRGameInstance.h"
#include "Components/Button.h"
#include "InGameUI/InGameHUD.h"

void UPauseMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if(!bIsButtonsBound)
	{
		BindButtons();
	}
	
	if(!SettingsWidget)
	{
		CreateSettingsWidget();
	}

}

void UPauseMenuWidget::NativeDestruct()
{
	Super::NativeDestruct();
	OnHideSettings();
}

void UPauseMenuWidget::BindButtons()
{
	if(!ExitButton)
	{
		UE_LOG(LogTemp, Error, TEXT("ExitButton error in : %s"), *GetName());
		return;
	}
	ExitButton->OnClicked.AddDynamic(this, &UPauseMenuWidget::OnExit);

	if(!ResumeButton)
	{
		UE_LOG(LogTemp, Error, TEXT("ResumeButton error in : %s"), *GetName());
		return;
	}
	ResumeButton->OnClicked.AddDynamic(this, &UPauseMenuWidget::OnResume);

	
	if(!SettingsButton)
	{
		UE_LOG(LogTemp, Error, TEXT("SettingsButton error in : %s"), *GetName());
		return;
	}
	SettingsButton->OnClicked.AddDynamic(this, &UPauseMenuWidget::OnShowSettings);


	bIsButtonsBound = true;
	
}


void UPauseMenuWidget::OnResume()
{
	this->RemoveFromViewport();
}

void UPauseMenuWidget::OnExit()
{
	auto GameInstance = Cast<UDRGameInstance>(GetGameInstance());
	if(GameInstance)
	{
		GameInstance->LeaveSession();
	}
}

void UPauseMenuWidget::OnShowSettings()
{
	if(!SettingsWidget)
	{
		CreateSettingsWidget();
	}
	
	SettingsWidget->AddToViewport(EInGameHUDViewPortVisibility::PauseMenu + 1);
}

void UPauseMenuWidget::OnHideSettings()
{
	SettingsWidget->RemoveFromViewport();
}

void UPauseMenuWidget::CreateSettingsWidget()
{
	if(!SettingsWidgetClass)
	{
		UE_LOG(LogTemp, Error, TEXT("SettingsWidgetClass not assigned in BP error in : %s"), *GetName());
		return;
	}

	SettingsWidget = CreateWidget<USettingsWidget>(GetWorld(), SettingsWidgetClass);
	if(!SettingsWidget)
	{
		UE_LOG(LogTemp, Error, TEXT("SettingsWidget is nullptr in: %s"), *GetName());
		return;
	}	
}
