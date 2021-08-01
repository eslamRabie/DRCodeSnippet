// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameUI/NotificationWidget.h"

#include "DRGameInstance.h"
#include "SoundManager.h"
#include "GameFramework/PlayerState.h"


void UNotificationWidget::Start(EGameModes GameModes, int32 InitialValue)
{
	WidgetGameMode = GameModes;
	bHasStarted = true;
	if(EGameModes::Time == GameModes)
	{
		FullTime = InitialValue;
		CurrentTime = FullTime;
		MessageType->SetText(FText::FromString("Time Remaining: "));
		UpdateTime(InitialValue);
	}
	else
	{
		NumberOfWaves = InitialValue;
		CurrentWave = NumberOfWaves;
		MessageType->SetText(FText::FromString("Waves Remaining: "));
		UpdateWave(InitialValue);
	}
}

void UNotificationWidget::Update(int32 UpdatedValue)
{
	if(EGameModes::Wave == WidgetGameMode)
	{
		UpdateWave(UpdatedValue);
		if(!bStartEnding && UpdatedValue <= StartEndNotificationAtWave)
		{
			bStartEnding = true;
			GetOwningPlayerState()->GetWorldTimerManager().SetTimer(ClockTickTimerHandle, this,&UNotificationWidget::End, 2, true);
		}
	}
}

void UNotificationWidget::End()
{
	PlayClockTick();
	PlayAnimation(EndOfGameAnimation);
}

void UNotificationWidget::StopTickSound()
{
	GetOwningPlayerState()->GetWorldTimerManager().PauseTimer(ClockTickTimerHandle);
	StopAnimation(EndOfGameAnimation);
}


void UNotificationWidget::UpdateTime(int32 Time)
{
	static int PreviousTime = -1;
	if (PreviousTime == -1)
	{
		PreviousTime = (Time / 60) + 1;
	}
	if(Time < 0) return;
	FString TimeString = FString(FString::FromInt(Time/60)) + FString(":") +FString(FString::FromInt(Time%60));
	Message->SetText(FText::FromString(TimeString));
	if((Time % 60) == 0 && (Time / 60) != PreviousTime)
	{
		PreviousTime = Time / 60;
		PlayAnimation(UpdateAnimation);
	}
}

void UNotificationWidget::UpdateWave(int32 UpdatedValue)
{
	Message->SetText(FText::FromString(FString::FromInt(UpdatedValue)));
	PlayAnimation(UpdateAnimation);
}

bool UNotificationWidget::Initialize()
{
	if(!Super::Initialize()) return false;
	bHasStarted = false;
	bStartEnding = false;
	return true;
}

void UNotificationWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if(bHasStarted && EGameModes::Time == WidgetGameMode)
	{
		CurrentTime -= InDeltaTime;
		UpdateTime(CurrentTime);
		if(!bStartEnding && CurrentTime <= StartEndNotificationAtTime)
		{
			bStartEnding = true;
			GetOwningPlayerState()->GetWorldTimerManager().SetTimer(ClockTickTimerHandle, this,&UNotificationWidget::End, 2, true);
		}
	}
}


ASoundManager* UNotificationWidget::TryGetSoundManager()
{
	if (!GetGameInstance<UDRGameInstance>())
	{
		UE_LOG(LogTemp, Error, TEXT("GetGameInstance nullptr in: %s"), *GetName());
		return nullptr;
	}

	if (!GetGameInstance<UDRGameInstance>()->SoundManager)
	{
		UE_LOG(LogTemp, Error, TEXT("SoundManager in ADestination::TryGetSoundManager is nullptr in: %s"), *GetName());
		return nullptr;
	}
	return GetGameInstance<UDRGameInstance>()->SoundManager;
}

void UNotificationWidget::PlayClockTick()
{
	auto SoundManager = TryGetSoundManager();
	if (!SoundManager) return;

	if (!ClockTickSound)
	{
		UE_LOG(LogTemp, Error, TEXT("ClockTickSound Not Set In BP in: %s"), *GetName());
		return;
	}
	SoundManager->PlaySound(ClockTickSound);
}