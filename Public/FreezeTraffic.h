// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRPowerUpBase.h"
#include "FreezeTraffic.generated.h"

class ASoundManager;
/**
 * 
 */
UCLASS()
class DELIVERYRUSH_API UFreezeTraffic : public UDRPowerUpBase
{
	GENERATED_BODY()
public:
	UFreezeTraffic();

	virtual void Tick(float DeltaTime) override;

	virtual bool StartEffect(AActor* AffectedActor) override;

	virtual void Effect(AActor* AffectedActor) override;

	virtual bool StopEffect(AActor* AffectedActor) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Design)
	float FreezeTimeSec = 5.f;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Sound)
	USoundBase* FreezeSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Sound)
	USoundBase* MeltSound;


private:
	UPROPERTY()
	class ATrafficController* AffectedTraffic;

	bool bIsTimerWorking;

	ASoundManager* TryGetSoundManager();

	void PlayFreezeSound(AActor* SoundSource);

	void PlayMeltSound(AActor* SoundSource);

	float CurrentTime;
};
