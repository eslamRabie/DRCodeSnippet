// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "ResultWindowWidget.generated.h"

class UScoreBoardWidget;
class UButton;
/**
 * 
 */
UCLASS()
class DELIVERYRUSH_API UResultWindowWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	UFUNCTION()
	void OnLeave();

	/*
	UFUNCTION()
	void OnReplayPressed();

	UFUNCTION()
	void OnReplayStartHover();

	UFUNCTION()
	void OnReplayStopHover();
	*/

protected:
	virtual bool Initialize() override;

	virtual void NativeConstruct() override;

private:
		
	UPROPERTY(meta = (BindWidget))
	UScoreBoardWidget* Results;

	UPROPERTY(Meta = (BindWidget))
	UButton* LeaveButton;

	// UPROPERTY(Meta = (BindWidget))
	// UButton* RePlayButton;

	/*UPROPERTY(Transient, Meta = (BindWidgetAnim))
	UWidgetAnimation* ReplayAnim;*/

	
};
