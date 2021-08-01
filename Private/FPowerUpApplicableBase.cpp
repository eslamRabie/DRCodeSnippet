// Fill out your copyright notice in the Description page of Project Settings.


#include "FPowerUpApplicableBase.h"


FPowerUpApplicableBase::FPowerUpApplicableBase(AActor* Child, ETargetType PowerUpTarget): PowerUpTargetType(PowerUpTarget),ChildPtr(Child)
{
	InitializeStatesFunctionsList();
}

void FPowerUpApplicableBase::Bind(const EPowerUpsActorStates State, UDRPowerUpBase* UserObject,
                                  FName* FunctionName)
{
	if(!BoundStatesFunctionsList.Contains(State))
	{
		BoundStatesFunctionsList.Add(State, TDelegate<void(AActor*)>());
	}
	else if(BoundStatesFunctionsList[State].IsBound()) return;
	
	
	BoundStatesFunctionsList[State].BindUFunction(UserObject, *FunctionName);
	if(State == EPowerUpsActorStates::ExecuteOnceAndImmediatelyState)
	{
		if(!BoundStatesFunctionsList[State].ExecuteIfBound(ChildPtr))
		{
			UE_LOG(LogTemp, Error, TEXT("ExecuteOnceAndImmediatelyState didn't bind correctly!"));
		}
		BoundStatesFunctionsList[State].Unbind();
	}
}

void FPowerUpApplicableBase::Bind(const EPowerUpsActorStates State, UDRPowerUpBase* UserObject)
{
	if(!BoundStatesFunctionsList.Contains(State))
	{
		BoundStatesFunctionsList.Add(State, TDelegate<void(AActor*)>());
	}
	else if(BoundStatesFunctionsList[State].IsBound()) return;
	
	BoundStatesFunctionsList[State].BindUObject(UserObject, &UDRPowerUpBase::Effect);
	if(State == EPowerUpsActorStates::ExecuteOnceAndImmediatelyState)
	{
		if(!BoundStatesFunctionsList[State].ExecuteIfBound(ChildPtr))
		{
			UE_LOG(LogTemp, Error, TEXT("ExecuteOnceAndImmediatelyState didn't bind correctly!"));
		}
		BoundStatesFunctionsList[State].Unbind();
	}
}

void FPowerUpApplicableBase::Bind(const EPowerUpsActorStates State, UDRPowerUpBase* UserObject, bool& bOutSuccessful)
{
	if(!BoundStatesFunctionsList.Contains(State))
	{
		BoundStatesFunctionsList.Add(State, TDelegate<void(AActor*)>());
	}
	else if(BoundStatesFunctionsList[State].IsBound())
	{
		bOutSuccessful = false;
		return;
	}

	bOutSuccessful = true;
	BoundStatesFunctionsList[State].BindUObject(UserObject, &UDRPowerUpBase::Effect);
	if(State == EPowerUpsActorStates::ExecuteOnceAndImmediatelyState)
	{
		if(!BoundStatesFunctionsList[State].ExecuteIfBound(ChildPtr))
		{
			UE_LOG(LogTemp, Error, TEXT("ExecuteOnceAndImmediatelyState didn't bind correctly!"));
		}
		BoundStatesFunctionsList[State].Unbind();
	}
}

void FPowerUpApplicableBase::UnBind(const EPowerUpsActorStates& State)
{
	if(BoundStatesFunctionsList[State].IsBound())
		BoundStatesFunctionsList[State].Unbind();
}

void FPowerUpApplicableBase::UnBind(const EPowerUpsActorStates& State, const FName& FunctionName)
{
	if(BoundStatesFunctionsList[State].TryGetBoundFunctionName() == FunctionName)
	{
		BoundStatesFunctionsList[State].Unbind();
	}
}

void FPowerUpApplicableBase::ExecuteEffect(AActor* AffectedActor)
{
	if(BoundStatesFunctionsList[EPowerUpsActorStates::ExecuteAtCallState].IsBound())
	{
		BoundStatesFunctionsList[EPowerUpsActorStates::ExecuteAtCallState].Execute(ChildPtr);
	}
}

void FPowerUpApplicableBase::ExecuteEffect(const EPowerUpsActorStates& State, AActor* AffectedActor)
{
	if(BoundStatesFunctionsList[State].IsBound())
	{
		BoundStatesFunctionsList[State].Execute(AffectedActor);
	}
}

void FPowerUpApplicableBase::ExecuteEffect(const EPowerUpsActorStates& State, const FName& FunctionName, AActor* AffectedActor)
{
	if(BoundStatesFunctionsList[State].TryGetBoundFunctionName() == FunctionName)
	{
		BoundStatesFunctionsList[State].Execute(AffectedActor);
	}
}

bool FPowerUpApplicableBase::IsStateBound(const EPowerUpsActorStates& State)
{
	return BoundStatesFunctionsList[State].IsBound();
}

void FPowerUpApplicableBase::InitializeStatesFunctionsList()
{
	BoundStatesFunctionsList.Add(EPowerUpsActorStates::TickState, TDelegate<void(AActor*)>());
	BoundStatesFunctionsList.Add(EPowerUpsActorStates::BeginState, TDelegate<void(AActor*)>());
	BoundStatesFunctionsList.Add(EPowerUpsActorStates::EndState, TDelegate<void(AActor*)>());
	BoundStatesFunctionsList.Add(EPowerUpsActorStates::TriggerState, TDelegate<void(AActor*)>());
	BoundStatesFunctionsList.Add(EPowerUpsActorStates::OverlapState, TDelegate<void(AActor*)>());
	BoundStatesFunctionsList.Add(EPowerUpsActorStates::ExecuteOnceAndImmediatelyState, TDelegate<void(AActor*)>());
	BoundStatesFunctionsList.Add(EPowerUpsActorStates::ExecuteAtCallState, TDelegate<void(AActor*)>());
}
