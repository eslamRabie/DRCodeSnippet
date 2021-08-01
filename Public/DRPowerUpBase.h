// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


UENUM(Blueprintable)
enum ETargetType{ Car, Destination, TrafficLight };

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

class FPowerUpApplicableBase;
#include "DRPowerUpBase.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class DELIVERYRUSH_API UDRPowerUpBase : public UObject, public FTickableGameObject
{
	GENERATED_BODY()

public:

	UDRPowerUpBase();
	
	void Init(enum ETargetType InTargetType);

	/** Default is can only be overridden by the same owner, this function must be Overridden otherwise*/
	virtual bool CanBeOverridden(UDRPowerUpBase& OtherPowerUp) const;

	/** Default is can only be combined with other effect by the same owner, this function must be Overridden otherwise*/
	virtual bool CanBeCombined(UDRPowerUpBase& OtherPowerUp) const;

	/**Apply the PowerUp Effect on the Actor (Bind the Effect function to the actor). Return: true on success*/
	virtual bool StartEffect(AActor* AffectedActor);

	/**The Function that do the effect*/
	UFUNCTION()
	virtual void Effect(AActor* AffectedActor);

	/**Stop The Effect and revert all Changes(unbind the Effect function). Return: true on success */
	virtual bool StopEffect(AActor* AffectedActor);

	
	// Begin FTickableGameObject Interface.
	/** Can Be Used for Timed Effects. */
	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override;
	virtual TStatId GetStatId() const override;
	// End FTickableGameObject Interface.

protected:
	
	ETargetType TargetType;
	
private:

	
	
	//Because engine would construct inner object when game load package (before game start), so we need to add a flag to identify which one is construct on game running.
	bool bIsCreateOnRunning = false;

	// To make sure that the object is initialized before use
	bool bIsInitialized;
};





