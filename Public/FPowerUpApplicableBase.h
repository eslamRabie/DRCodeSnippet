// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRPowerUpBase.h"



/**
 * Used normal enum to allow easy expansion of this list of states by any means needed
 */
UENUM()
enum EPowerUpsActorStates
{
	/**
	 *
	 *You can Add more Sates if needed in your class as long as the PowerUp class that targets your class uses it too.
	 * 
	 */
	TickState = 0,
	BeginState,
	EndState,
	TriggerState,
	OverlapState,
	ExecuteOnceAndImmediatelyState,
	ExecuteAtCallState,
	End_Of_EPowerUpsActorStates
};


/**
 * An Abstract Class That if any actor wants be able to execute a PowerUp in DeliveryRush game, must implement it.  
 */
/*struct DelegateObject
{
	DelegateObject(){};
	TDelegate<void(AActor*)> MyDelegate;
}; */

class DELIVERYRUSH_API FPowerUpApplicableBase
{
public:
	FPowerUpApplicableBase():PowerUpTargetType{ETargetType::Car}{ChildPtr = nullptr;};
	//FPowerUpApplicableBase(){ChildPtr = nullptr;};
	explicit FPowerUpApplicableBase(AActor* Child, ETargetType PowerUpTarget);

	/**
	* Bind The Member function by it name of the class UDRPowerUpBase
	* Require the function to be a UFunction to work
	*
	* If the provided state was not found then a new delegate with that state is created and added to the DB,
	* used carefully not add a new state ny mistake
	*
	* If the state <ExecuteOnceAndImmediatelyState> is used the delegate will execute at once on the Child object of
	* this class.
	*/
	virtual void Bind(const EPowerUpsActorStates State, UDRPowerUpBase* UserObject, FName* FunctionName);


	/**
	* Bind The Member function by it name of the class UDRPowerUpBase
	* Require the function to be a UFunction to work
	*
	* If the provided state was not found then a new delegate with that state is created and added to the DB,
	* used carefully not add a new state ny mistake
	*
	* If the state <ExecuteOnceAndImmediatelyState> is used the delegate will execute at once on the Child object of
	* this class.
	*/
	virtual void Bind(const EPowerUpsActorStates State, UDRPowerUpBase* UserObject);

	/**
	* Bind The Member function by it name of the class UDRPowerUpBase
	* Require the function to be a UFunction to work
	*
	* If the provided state was not found then a new delegate with that state is created and added to the DB,
	* used carefully not add a new state ny mistake
	*
	* If the state <ExecuteOnceAndImmediatelyState> is used the delegate will execute at once on the Child object of
	* this class.
	*
	* The boolean bOutSuccessful is used to check if the delegate was bound correctly.
	*/
	virtual void Bind(const EPowerUpsActorStates State, UDRPowerUpBase* UserObject, bool& bOutSuccessful);

	
	/**
	 * Unbind the function at the Provided State, if bound
	 */
	virtual void UnBind(const EPowerUpsActorStates& State);


	/**
	* Unbind the function at the Provided State if the FunctionName matches the bound function name
	*/
	virtual void UnBind(const EPowerUpsActorStates& State,const FName& FunctionName);


	/**
	 * Execute the ExecuteAtCallState if bound
	 */
	virtual void ExecuteEffect(AActor* AffectedActor);



	const ETargetType PowerUpTargetType;
	
protected:
	/**
	* Execute the Provided state if bound
	*/
	virtual void ExecuteEffect(const EPowerUpsActorStates& State, AActor* AffectedActor);


	/**
	* Execute the provided state if bound to the provided FunctionName
	*/
	virtual void ExecuteEffect(const EPowerUpsActorStates& State, const FName& FunctionName, AActor* AffectedActor);


	/**
	 * Checks to see if any delegate is bound to the given state
	 */
	virtual bool IsStateBound(const EPowerUpsActorStates& State);
	
	
	virtual ~FPowerUpApplicableBase(){}

	virtual void DefaultTickStateFunc(){}

	virtual void DefaultBeginStateFunc(){}

	virtual void DefaultEndStateFunc(){}

	virtual void DefaultTriggerStateFunc(){}

	virtual void DefaultOverlapStateFunc(){}


	virtual void DefaultTickStateFunc(AActor*){}

	virtual void DefaultBeginStateFunc(AActor*){}

	virtual void DefaultEndStateFunc(AActor*){}

	virtual void DefaultTriggerStateFunc(AActor*){}

	virtual void DefaultOverlapStateFunc(AActor*){}
	

	
private:
	// Require an AActor Child to work; final Child must be an AActor  
	AActor* ChildPtr;

	/**
	*Map between States and Bound States Functors,
	*/
	TMap<int32, TDelegate<void(AActor*)>> BoundStatesFunctionsList;
	
	/** Initialize the Functions Lists:  DefaultStatesFunctionsList, BoundStatesFunctionsList. */
	void InitializeStatesFunctionsList();
	
	
};
