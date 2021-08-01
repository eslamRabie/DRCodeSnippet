// Fill out your copyright notice in the Description page of Project Settings.


#include "DestinationManager.h"

#include "TrafficController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADestinationManager::ADestinationManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bIsCreatedCorrectly = true;
}

// Called when the game starts or when spawned
void ADestinationManager::BeginPlay()
{
	Super::BeginPlay();	
	if(Destinations.Num() == 0)
	{
		bIsCreatedCorrectly = false;
		UE_LOG(LogTemp, Error, TEXT("DestinationManager Require the assignemrnt of the defferent Destinations Before Running the Game!"));		
	}
	if(DestinationsBluePrints.Num() == 0)
	{
		bIsCreatedCorrectly = false;
		UE_LOG(LogTemp, Error, TEXT("DestinationManager Require the assignemrnt of the defferent DestinationTypes BluePrints Before Running the Game!"));
	}
}

void ADestinationManager::GetDestinationsFromScene()
{
	TArray<AActor*> TempActorsList;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADestination::StaticClass(), TempActorsList);

	for(auto& Spawner: TempActorsList)
	{
		Destinations.Add(Cast<ADestination>(Spawner));
	}
}

// Called every frame
void ADestinationManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
//ok
TArray<ADestination*> ADestinationManager::GetSceneDestinations()
{
	if(!bIsCreatedCorrectly) return TArray<ADestination*>();

	return Destinations;
}
//ok
TArray<TSubclassOf<ADestination>> ADestinationManager::GetDestinationsBluePrintsTypes()
{
	if(!bIsCreatedCorrectly) return TArray<TSubclassOf<ADestination>>();
	return DestinationsBluePrints;
}

TArray<ADestination*> ADestinationManager::GetSceneDestinationsByBluePrintType(TSubclassOf<ADestination> BluePrintType)
{
	if(!bIsCreatedCorrectly) return TArray<ADestination*>();	
	TArray<ADestination*> NewDestinations;
	for(auto& Dest : Destinations)
	{
		if(Dest->IsA(BluePrintType)) // works
		{
			NewDestinations.Add(Dest);
		}
	}
	return NewDestinations;
}

TArray<ADestination*> ADestinationManager::GetSceneDestinationsByBluePrintType(FString BluePrintTypeName)
{
	if(!bIsCreatedCorrectly) return TArray<ADestination*>();	
	TArray<ADestination*> NewDestinations;
	TSubclassOf<ADestination> BluePrintType = GetDestinationBluePrintByName(BluePrintTypeName);
	if(BluePrintType)
	{
		NewDestinations = GetSceneDestinationsByBluePrintType(*BluePrintType);
	}
	return NewDestinations;
}

TArray<ADestination*> ADestinationManager::GetSceneDestinationsByTypeName(FString DestinationTypeName)
{
	if(!bIsCreatedCorrectly) return TArray<ADestination*>();
	TArray<ADestination*> NewDestinationsList;
	for(auto& Destination : Destinations)
	{
		if(Destination->GetPlayerTypeName() == DestinationTypeName)
		{
			NewDestinationsList.Add(Destination);
		}
	}
	return NewDestinationsList;
}

TArray<ADestination*> ADestinationManager::GetSceneDestinationsByPlayerType(FString PlayerTypes)
{
	if(!bIsCreatedCorrectly) return TArray<ADestination*>();	
	TArray<ADestination*> NewDestinationsList;
	for(auto& Destination : Destinations)
	{
		if(Destination->GetPlayerTypeName() == PlayerTypes)
		{
			NewDestinationsList.Add(Destination);
		}
	}
	return NewDestinationsList;
}


void ADestinationManager::ChangeDestinationLocation(ADestination& Destination, FVector& NewLocation, FRotator& NewRotation)
{
	if(!bIsCreatedCorrectly) return;		
	Destination.SetActorLocation(NewLocation);
	Destination.SetActorRotation(NewRotation);
}

void ADestinationManager::ChangeDestinationLocation(int32 DestinationIndex, FVector& NewLocation, FRotator& NewRotation)
{

	if(!bIsCreatedCorrectly) return;	
	Destinations[DestinationIndex]->SetActorLocation(NewLocation);
	Destinations[DestinationIndex]->SetActorRotation(NewRotation);
}

TArray<FVector> ADestinationManager::GetDestinationsLocations()
{
	if(!bIsCreatedCorrectly) return TArray<FVector>();	
	TArray<FVector> TempLocationsList;
	for(auto& Destination: Destinations)
	{
		TempLocationsList.Add(Destination->GetActorLocation());
	}
	return TempLocationsList;
}

void ADestinationManager::ChangeDestinationType(ADestination& Destination,
	TSubclassOf<ADestination>& NewDestinationBluePrint)
{
	if(!bIsCreatedCorrectly) return;	
	auto  OldDestTransform = Destination.GetTransform();
	auto OldTrafficLightRef = Destination.TrafficLightReference;
	int32 Index = -1;
	for (int32 i = 0; i < OldTrafficLightRef->Directions.Num(); i++)
	{
		auto Dest = Cast<ADestination>(OldTrafficLightRef->Directions[i].GetObject());
		if(!Dest) continue;
		if(*Dest == Destination)
		{
			Index = i;
			break;
		}
	}
	if(Index == -1)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cant Find Destination at DestinationManager::ChangeDestinationType"));
		return;
	}	
	auto World = GetWorld();
	if(World)
	{
		int32 Idx = Destinations.IndexOfByKey<ADestination*>(&Destination);
		Destinations[Idx] = nullptr;
		if(Destination.Destroy())
		{
			auto NewDestination = Cast<ADestination>(World->SpawnActor(NewDestinationBluePrint, &OldDestTransform));
			NewDestination->TrafficLightReference = OldTrafficLightRef;
			NewDestination->TrafficLightReference->Directions[Index] = NewDestination;
			//Destinations.Add(NewDestination);
			Destinations[Idx] = NewDestination;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Cant Destroy Destination at DestinationManager::ChangeDestinationType"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Cant GetWorld at DestinationManager::ChangeDestinationType"));
	}
}

void ADestinationManager::ChangeDestinationType(ADestination& Destination, FString& NewDestinationBluePrintName)
{
	if(!bIsCreatedCorrectly) return;	
	TSubclassOf<ADestination> NewDestinationType = GetDestinationBluePrintByName(NewDestinationBluePrintName);
	if(NewDestinationType)
	{
		ChangeDestinationType(Destination, NewDestinationType);
	}
}

void ADestinationManager::ChangeDestinationType(int32 DestinationIndex, TSubclassOf<ADestination>& NewDestinationBluePrint)
{	
	if(!bIsCreatedCorrectly) return;	
	ADestination* Destination = Destinations[DestinationIndex];
	ChangeDestinationType(*Destination, NewDestinationBluePrint);
}

void ADestinationManager::ChangeDestinationType(int32 DestinationIndex, FString& NewDestinationBluePrintName)
{
	if(!bIsCreatedCorrectly) return;	
	ADestination* Destination = Destinations[DestinationIndex];
	ChangeDestinationType(*Destination, NewDestinationBluePrintName);
}

void ADestinationManager::ChangeDestinationType(int32 DestinationIndex, int32 NewDestinationBluePrintIndex)
{
	if(!bIsCreatedCorrectly) return;	
	ADestination* Destination = Destinations[DestinationIndex];
	TSubclassOf<ADestination> NewDestinationBluePrint = DestinationsBluePrints[NewDestinationBluePrintIndex];
	ChangeDestinationType(*Destination, NewDestinationBluePrint);
}




void ADestinationManager::ModifyDestinationType(int32 DestinationIndex, int32 NewDestinationBluePrintIndex)
{
	if(!bIsCreatedCorrectly) return;	
	auto World = GetWorld();
	if (World)
	{
		ADestination* NewDestination = World->SpawnActor<ADestination>(DestinationsBluePrints[NewDestinationBluePrintIndex]);
		if (NewDestination)
		{
			Destinations[DestinationIndex]->ChangeTo(NewDestination);
			NewDestination->Destroy();
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Can't Spawn destination"));
		}
	}
}

TSubclassOf<ADestination> ADestinationManager::GetDestinationBluePrintByName(FString& Name)
{
	if(!bIsCreatedCorrectly) return TSubclassOf<ADestination>();	
	for (auto& Dest : DestinationsBluePrints)
	{
		if(Dest->GetName() == Name)
		{
			TSubclassOf<ADestination> Destination = Dest;
			return Destination;
		}
	}
	return nullptr;
}

TSubclassOf<ADestination> ADestinationManager::GetDestinationBluePrintByIndex(int32 Index)
{
	if(!bIsCreatedCorrectly) return TSubclassOf<ADestination>();	
	return DestinationsBluePrints[Index];
}
	
