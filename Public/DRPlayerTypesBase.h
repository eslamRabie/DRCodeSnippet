// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class DELIVERYRUSH_API PlayerTypesBase
{
public:

	/** Create a new Type object or return reference to an existing Type object*/
	inline static PlayerTypesBase& CreateType(const FString& TypeNameStr)
	{
		PlayerTypesBase* DrPlayerTypesBase;
		// FName Exist return existing object
		if( IsTypeCreated(TypeNameStr.ToLower(), DrPlayerTypesBase) )
		{
			return *DrPlayerTypesBase;
		}
		
		DrPlayerTypesBase = new PlayerTypesBase(TypeNameStr);
		PlayerTypeArray.Add(DrPlayerTypesBase);
		return *DrPlayerTypesBase;
		
	}

	/** Destroy All Types Created*/ 
	inline static void Destroy()
	{
		for(PlayerTypesBase* Obj: PlayerTypeArray)
		{
			delete Obj;
		}
	}

	friend bool operator==(const PlayerTypesBase& Lhs, const PlayerTypesBase& RHS)
	{
		return Lhs.TypeName == RHS.TypeName
			&& Lhs.TypeID == RHS.TypeID;
	}

	friend bool operator!=(const PlayerTypesBase& Lhs, const PlayerTypesBase& RHS)
	{
		return !(Lhs == RHS);
	}

	
private:
	static TArray<PlayerTypesBase*> PlayerTypeArray;
	static uint32 TypeIDGenerator;
	FString TypeName;
public:
	FString GetTypeName() const;
	uint32 GetTypeID() const;
	static bool IsTypeCreated(const FString& InTypeName, PlayerTypesBase* & OutTypeObject);
	static TArray<PlayerTypesBase*> GetAllCreatedTypes();  
private:
	uint32 TypeID;
	
	
	PlayerTypesBase(const FString& TypeName);
	
};


