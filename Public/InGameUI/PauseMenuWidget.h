// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "SettingsWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/Overlay.h"
#include "Components/VerticalBox.h"

#include "PauseMenuWidget.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class DELIVERYRUSH_API UPauseMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void OnExit();
	
	UFUNCTION()
	void OnResume();

	UFUNCTION()
	void OnShowSettings();

	UFUNCTION()
	void OnHideSettings();

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

private:
	bool bIsButtonsBound = false;

	UPROPERTY()
	USettingsWidget* SettingsWidget;

	UPROPERTY(meta = (BindWidget))
	UButton* ResumeButton;

	UPROPERTY(meta = (BindWidget))
	UButton* SettingsButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* ExitButton;

	UPROPERTY(meta = (BindWidget))
	UOverlay* PauseMenu;
	
	UPROPERTY(meta = (BindWidget))
	UOverlay* SettingsMenu;
	
	UPROPERTY(EditDefaultsOnly, Category=Defaults)
	TSubclassOf<USettingsWidget> SettingsWidgetClass;
	

	void BindButtons();
	
	void CreateSettingsWidget();

		
};
