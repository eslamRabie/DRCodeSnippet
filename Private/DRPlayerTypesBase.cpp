// Fill out your copyright notice in the Description page of Project Settings.


#include "DRPlayerTypesBase.h"

uint32 PlayerTypesBase::TypeIDGenerator = 0;

TArray<PlayerTypesBase*> PlayerTypesBase::PlayerTypeArray = TArray<PlayerTypesBase*>();

FString PlayerTypesBase::GetTypeName() const
{
	return TypeName;
}

uint32 PlayerTypesBase::GetTypeID() const
{
	return TypeID;
}

bool PlayerTypesBase::IsTypeCreated(const FString& InTypeName, PlayerTypesBase*& OutTypeObject)
{
	for(PlayerTypesBase* Obj: PlayerTypeArray)
	{
		if(Obj->TypeName == InTypeName.ToLower())
		{
			OutTypeObject = Obj;
			return true;
		}
	}
	return false;
}

TArray<PlayerTypesBase*> PlayerTypesBase::GetAllCreatedTypes()
{
	return PlayerTypeArray;
}

PlayerTypesBase::PlayerTypesBase(const FString& TypeName)
{
	this->TypeID = TypeIDGenerator;
	this->TypeName = TypeName.ToLower();
	TypeIDGenerator++;
}
