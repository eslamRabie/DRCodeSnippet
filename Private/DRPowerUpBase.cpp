// Fill out your copyright notice in the Description page of Project Settings.


#include "DRPowerUpBase.h"
#include "FPowerUpApplicableBase.h"

UDRPowerUpBase::UDRPowerUpBase()
{
	bIsCreateOnRunning = GIsRunning;
	bIsInitialized = false;
}

void UDRPowerUpBase::Init( ETargetType InTargetType)
{
	this->TargetType = InTargetType;
	bIsInitialized = true;
}

bool UDRPowerUpBase::CanBeOverridden(UDRPowerUpBase& OtherPowerUp) const
{
	return true;
}

bool UDRPowerUpBase::CanBeCombined(UDRPowerUpBase& OtherPowerUp) const
{
	return true;
}

bool UDRPowerUpBase::StartEffect(AActor* AffectedActor)
{
	return true;
}

void UDRPowerUpBase::Effect(AActor* AffectedActor)
{

}

bool UDRPowerUpBase::StopEffect(AActor* AffectedActor)
{
	return true;
}



void UDRPowerUpBase::Tick(float DeltaTime)
{
	//Don't invoke Super::Tick(), otherwise would link failed!!!
	//Super::Tick(DeltaTime);
	if(!bIsInitialized)
	{
		UE_LOG(LogTemp, Error, TEXT("UDRPowerUpBase needs to be Initialized in:<<<< %s >>>>"), *GetName());

	}
}
 
bool UDRPowerUpBase::IsTickable() const
{
	//notify engine to ingore Tick of the object constructed before game running.
	return bIsCreateOnRunning;
}
TStatId UDRPowerUpBase::GetStatId() const
{
	return UObject::GetStatID();
}