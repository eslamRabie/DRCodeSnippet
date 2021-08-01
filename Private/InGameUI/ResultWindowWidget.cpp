// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameUI/ResultWindowWidget.h"

#include "DRGameInstance.h"
#include "DRGameMode.h"
#include "Components/Button.h"


void UResultWindowWidget::OnLeave()
{
	auto GameInstance = Cast<UDRGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		GameInstance->LeaveSession();
	}
}

/*void UResultWindowWidget::OnReplayPressed()
{
	if (!GetOwningPlayer()->HasAuthority())
	{
		return;
	}

	auto World = GetWorld();
	if (!World)
	{
		return;
	}

	auto GameMode = GetWorld()->GetAuthGameMode<ADRGameMode>();

	if (!GameMode)
	{
		return;
	}

	GameMode->RestartGame();
}*/

/*
void UResultWindowWidget::OnReplayStartHover()
{
	PlayAnimation(ReplayAnim, 0, 5, EUMGSequencePlayMode::Reverse);
}
*/

/*
void UResultWindowWidget::OnReplayStopHover()
{
	StopAnimation(ReplayAnim);
}
*/

bool UResultWindowWidget::Initialize()
{
	if (!Super::Initialize()) return Super::Initialize();
	if (!LeaveButton/* || !RePlayButton*/)
	{
		UE_LOG(LogTemp, Error, TEXT("Some Widgets is not assigned in BP in : %s"), *GetName());
		return false;
	}
	LeaveButton->OnClicked.AddDynamic(this, &UResultWindowWidget::OnLeave);
	/*RePlayButton->OnClicked.AddDynamic(this, &UResultWindowWidget::OnReplayPressed);
	RePlayButton->OnHovered.AddDynamic(this, &UResultWindowWidget::OnReplayStartHover);
	RePlayButton->OnUnhovered.AddDynamic(this, &UResultWindowWidget::OnReplayStopHover);*/
	return true;
}

void UResultWindowWidget::NativeConstruct()
{
	Super::NativeConstruct();

	/*if (GetOwningPlayer()->HasAuthority())
	{
		RePlayButton->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		RePlayButton->SetVisibility(ESlateVisibility::Collapsed);
	}*/
}
