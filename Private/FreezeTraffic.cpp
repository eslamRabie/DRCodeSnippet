// Fill out your copyright notice in the Description page of Project Settings.


#include "FreezeTraffic.h"

#include "DRGameInstance.h"
#include "SoundManager.h"
#include "TrafficController.h"

UFreezeTraffic::UFreezeTraffic()
{
	this->Init(TargetType = ETargetType::TrafficLight);
	bIsTimerWorking = false;
	CurrentTime = FreezeTimeSec;
}

void UFreezeTraffic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIsTimerWorking)
	{
		CurrentTime -= DeltaTime;
		if (CurrentTime <= 0)
		{
			CurrentTime = FreezeTimeSec;
			bIsTimerWorking = false;
			StopEffect(AffectedTraffic);
		}
	}
}

bool UFreezeTraffic::StartEffect(AActor* AffectedActor)
{
	if (!AffectedActor) return false;
	AffectedTraffic = Cast<ATrafficController>(AffectedActor);
	if (!AffectedTraffic) return false;
	AffectedTraffic->Bind(EPowerUpsActorStates::BeginState, this);
	AffectedTraffic->StartFreeze();
	bIsTimerWorking = true;

	return true;
}

void UFreezeTraffic::Effect(AActor* AffectedActor)
{
}

bool UFreezeTraffic::StopEffect(AActor* AffectedActor)
{
	if (AffectedTraffic)
	{
		PlayMeltSound(AffectedTraffic);
		AffectedTraffic->UnBind(EPowerUpsActorStates::BeginState);
		AffectedTraffic->EndFreeze();
		AffectedTraffic = nullptr;
		return true;
	}
	return false;
}


ASoundManager* UFreezeTraffic::TryGetSoundManager()
{
	if (!GetWorld())
	{
		UE_LOG(LogTemp, Error, TEXT("GetWorld nullptr in: %s"), *GetName());
		return nullptr;
	}
	if (!GetWorld()->GetGameInstance<UDRGameInstance>())
	{
		UE_LOG(LogTemp, Error, TEXT("GetGameInstance nullptr in: %s"), *GetName());
		return nullptr;
	}

	if (!GetWorld()->GetGameInstance<UDRGameInstance>()->SoundManager)
	{
		UE_LOG(LogTemp, Error, TEXT("SoundManager in ADestination::TryGetSoundManager is nullptr in: %s"), *GetName());
		return nullptr;
	}

	return GetWorld()->GetGameInstance<UDRGameInstance>()->SoundManager;
}

void UFreezeTraffic::PlayFreezeSound(AActor* SoundSource)
{
	auto SoundManager = TryGetSoundManager();
	if (!SoundManager) return;

	if (!FreezeSound)
	{
		UE_LOG(LogTemp, Error, TEXT("FreezeSound Not Set In BP in: %s"), *GetName());
		return;
	}
	SoundManager->PlaySound(FreezeSound, SoundSource);
}


void UFreezeTraffic::PlayMeltSound(AActor* SoundSource)
{
	auto SoundManager = TryGetSoundManager();
	if (!SoundManager) return;

	if (!MeltSound)
	{
		UE_LOG(LogTemp, Error, TEXT("MeltSound Not Set In BP in: %s"), *GetName());
		return;
	}
	SoundManager->PlaySound(MeltSound, SoundSource);
}
