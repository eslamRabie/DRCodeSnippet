// Fill out your copyright notice in the Description page of Project Settings.


#include "FreezeDestination.h"

#include "Car.h"
#include "Destination.h"
#include "DRGameInstance.h"
#include "DynamicVFXComponent.h"
#include "FPowerUpApplicableBase.h"

UFreezeDestination::UFreezeDestination()
{
	this->Init(TargetType = ETargetType::Destination);
	AffectedDestination = nullptr;
	bIsTimerWorking = false;
	CurrentTime = 0.f;
}

void UFreezeDestination::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIsTimerWorking)
	{
		CurrentTime += DeltaTime;
		if (CurrentTime >= FreezeTimeSec)
		{
			CurrentTime = 0.f;
			bIsTimerWorking = false;
			StopEffect(AffectedDestination);
		}
	}
}

bool UFreezeDestination::StartEffect(AActor* AffectedActor)
{
	if (AffectedDestination) return false;

	AffectedDestination = Cast<ADestination>(AffectedActor);

	if (!AffectedDestination) return false;

	if (!TargetType == AffectedDestination->PowerUpTargetType) return false;

	bool bIsBound;
	AffectedDestination->Bind(EPowerUpsActorStates::OverlapState, this, bIsBound);

	if(!bIsBound)
	{
		UE_LOG(LogTemp, Error, TEXT("Actor is already bound to a delegate in UFreezeDestination::StartEffect in: %s"), *GetName());
		return false;
	}

	if(!AffectedDestination->FreezeVFXComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("FreezeVFXComponent nullptr in UFreezeDestination::StartEffect in: %s"), *GetName());
		return false;
	}
	TArray<UActorComponent*> Components = AffectedDestination->GetComponentsByTag(UActorComponent::StaticClass(), "FreezeMesh");
	if (!Components.Num())
	{
		UE_LOG(LogTemp, Error, TEXT("AffectedDestination Doesn't have a freeze mesh in UFreezeDestination::StartEffect in: %s"), *GetName());
		return false;
	}
	UStaticMeshComponent* FreezeMesh = Cast<UStaticMeshComponent>(Components[0]);
	if (!FreezeMesh)
	{
		UE_LOG(LogTemp, Error, TEXT("FreezeMesh nullptr in UFreezeDestination::StartEffect in: %s"), *GetName());		
		return false;
	}
	AffectedDestination->FreezeVFXComponent->SetTargetMesh(FreezeMesh);
	AffectedDestination->FreezeVFXComponent->StartFreeze();

	bIsTimerWorking = true;	
	PlayFreezeSound(AffectedDestination);

	return true;
}

void UFreezeDestination::Effect(AActor* AffectedActor)
{
	auto AffectedCar = Cast<ACar>(AffectedActor);

	if (!AffectedCar)
	{
		UE_LOG(LogTemp, Error, TEXT("AffectedCar nullptr in UFreezeDestination::Effect in: %s"), *GetName());
		return;
	}
	PlayCarFreezeSound(AffectedCar);
	AffectedCar->Destroy();
	// Do some freeze animations or effects when a car tries to enter house
	AffectedCar = nullptr;
}

bool UFreezeDestination::StopEffect(AActor* AffectedActor)
{
	if (AffectedDestination)
	{
		PlayMeltSound(AffectedDestination);
		AffectedDestination->UnBind(EPowerUpsActorStates::OverlapState);
		AffectedDestination = nullptr;
		return true;
	}
	return false;
}

ASoundManager* UFreezeDestination::TryGetSoundManager()
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

void UFreezeDestination::PlayFreezeSound(AActor* SoundSource)
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

void UFreezeDestination::PlayCarFreezeSound(AActor* SoundSource)
{
	auto SoundManager = TryGetSoundManager();
	if (!SoundManager) return;

	if (!CarFreezeClashSound)
	{
		UE_LOG(LogTemp, Error, TEXT("CarFreezeClashSound Not Set In BP in: %s"), *GetName());
		return;
	}
	SoundManager->PlaySound(CarFreezeClashSound, SoundSource);
}

void UFreezeDestination::PlayMeltSound(AActor* SoundSource)
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
