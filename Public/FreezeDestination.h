// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRPowerUpBase.h"
#include "FreezeDestination.generated.h"


class UDRGameInstance;
class ASoundManager;
class ACar;
class ADestination;

/**
 * 
 */
UCLASS()
class DELIVERYRUSH_API UFreezeDestination : public UDRPowerUpBase
{
	GENERATED_BODY()
public:

	UFreezeDestination();
	
	virtual void Tick(float DeltaTime) override;

	virtual bool StartEffect(AActor* AffectedActor) override;

	virtual void Effect(AActor* AffectedActor) override;

	virtual bool StopEffect(AActor* AffectedActor) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Design)
	float FreezeTimeSec = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Sound)
	USoundBase* FreezeSound;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Sound)
	USoundBase* CarFreezeClashSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Sound)
	USoundBase* MeltSound;
	
private:

	UPROPERTY()
	ADestination* AffectedDestination;

	ASoundManager* TryGetSoundManager();
	
	void PlayFreezeSound(AActor* SoundSource);

	void PlayCarFreezeSound(AActor* SoundSource);

	void PlayMeltSound(AActor* SoundSource);
	
	bool bIsTimerWorking;

	float CurrentTime;
};
