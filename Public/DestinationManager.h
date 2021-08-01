// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Destination.h"
#include "GameFramework/Actor.h"
#include "DestinationManager.generated.h"

UCLASS()
class DELIVERYRUSH_API ADestinationManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADestinationManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GameDesign")
	TArray<TSubclassOf<ADestination>> DestinationsBluePrints;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GameDesign")
	TArray<ADestination*> Destinations;

	/**
	 * Get an Array of Scene Destinations by the order they where added by the Game Designer
	 */
	TArray<ADestination*> GetSceneDestinations();

	/**
	* Get an Array of Destinations types Blueprints by the order they where added by the Game Designer
	*/
	TArray<TSubclassOf<ADestination>> GetDestinationsBluePrintsTypes();

	/**
	* Get an Array of Scene Destinations by their blueprint Type
	*/
	TArray<ADestination*> GetSceneDestinationsByBluePrintType(TSubclassOf<ADestination> BluePrintType);

	/**
	* Get an Array of Scene Destinations by their Blueprint Name
	*/
	TArray<ADestination*> GetSceneDestinationsByBluePrintType(FString BluePrintTypeName);

	/**
	* Get an Array of Scene Destinations by their PlayerType Name
	*/
	TArray<ADestination*> GetSceneDestinationsByTypeName(FString DestinationTypeName);

	/**
	* Get an Array of Scene Destinations by their PlayerType 
	*/
	TArray<ADestination*> GetSceneDestinationsByPlayerType(FString PlayerTypes);
	
	/**
	* Get a Destinations Blueprint Type  by Blueprint name 
	*/
	TSubclassOf<ADestination> GetDestinationBluePrintByName(FString& Name);

	/**
	* Get a Destinations Blueprint Type  by Blueprint index in DestinationsBluePrints array 
	*/
	TSubclassOf<ADestination> GetDestinationBluePrintByIndex(int32 Index);
	
	/**
	* Get an array of all Destinations Locations  
	*/
	TArray<FVector> GetDestinationsLocations();
	

	/**
	* Change Destination Location <Move> 
	*/
	void ChangeDestinationLocation(ADestination& Destination, FVector& NewLocation, FRotator& NewRotation);

	/**
	* Change Destination Location <Move> 
	*/
	void ChangeDestinationLocation(int32 DestinationIndex, FVector& NewLocation, FRotator& NewRotation);

	/**
	* Change Destination Type <Destroy & Spawn> 
	*/
	void ChangeDestinationType(ADestination& Destination, TSubclassOf<ADestination>& NewDestinationBluePrint);

	/**
	* Change Destination Type <Destroy & Spawn> 
	*/
	void ChangeDestinationType(ADestination& Destination, FString& NewDestinationBluePrintName);

	/**
	* Change Destination Type <Destroy & Spawn> 
	*/
	void ChangeDestinationType(int32 DestinationIndex, TSubclassOf<ADestination>& NewDestinationBluePrint);

	/**
	* Change Destination Type <Destroy & Spawn> 
	*/
	void ChangeDestinationType(int32 DestinationIndex, FString& NewDestinationBluePrintName);

	/**
	* Change Destination Type <Destroy & Spawn> 
	*/
	void ChangeDestinationType(int32 DestinationIndex, int32 NewDestinationBluePrintIndex);

	/**
	* Change Destination Type <Copy Type From another Destination>
	* DeliveryID property must be assigned correctly after this.
	*/
	void ModifyDestinationType(int32 DestinationIndex, int32 NewDestinationBluePrintIndex);
	
private:

	// Get All Scene Destinations 
	void GetDestinationsFromScene();
	
	bool bIsCreatedCorrectly;
	
};
