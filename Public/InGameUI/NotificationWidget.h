// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"

#include "NotificationWidget.generated.h"

/**
 * 
 */

class ASoundManager;
UENUM()
enum class EGameModes: uint8
{
	Time,
	Wave
};

UCLASS(Abstract)
class DELIVERYRUSH_API UNotificationWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	void Start(EGameModes GameModes, int32 InitialValue);
	void Update(int32 UpdatedValue);
	void End();
	void StopTickSound();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Design")
	float StartEndNotificationAtTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Design")
	float StartEndNotificationAtWave;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundBase* ClockTickSound;
	
	
protected:
	virtual bool Initialize() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	
private:

	ASoundManager* TryGetSoundManager();
	void PlayClockTick();
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Message ;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MessageType ;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* EndOfGameAnimation;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* UpdateAnimation;

	void UpdateTime(int32 Time);

	void UpdateWave(int32 Wave);
	
	EGameModes WidgetGameMode;

	FTimerHandle ClockTickTimerHandle;
	
	bool bHasStarted;
	bool bStartEnding;
	int32 FullTime;
	int32 NumberOfWaves;
	float CurrentTime;
	int32 CurrentWave;
};
	