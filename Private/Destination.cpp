// Fill out your copyright notice in the Description page of Project Settings.


#include "Destination.h"
#include "DRInGamePlayerState.h"
#include "Car.h"
#include "DRGameInstance.h"
#include "DRInGamePlayerController.h"
#include "DynamicVFXComponent.h"

#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "InGameUI/HouseDeliveryIDWidget.h"

//Todo Move Samir's Code to its perspective class
// Sets default values
ADestination::ADestination() : FPowerUpApplicableBase{this, Destination}
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	// All Rights Received Ahmed Samir
	OutlineVFXComponent = CreateDefaultSubobject<UDynamicVFXComponent>("OutlineVFXComponent");
	FreezeVFXComponent = CreateDefaultSubobject<UDynamicVFXComponent>("FreezeVFXComponent");
	/**
	 * Bind the Desttination Default events
	 */
	
	OnActorBeginOverlap.AddDynamic(this, &ADestination::OnOverlap);

	/**
	 *
	 * Set the Default Scoring System Values
	 * 
	 */
	Score = 5;
	DoubleScore = 5;
	BankCoins = 9;
	GoldenCarScore = 20;


	/**
	 * Set Userless Types 
	 */
	GoldenCarType = "Golden";
	BankType = "Bank";
	
}

// Called when the game starts or when spawned
void ADestination::BeginPlay()
{
	Super::BeginPlay();
	
	// All Rights Received Ahmed Samir
	TArray<USkeletalMeshComponent*>CenterArray;
	GetComponents(CenterArray);
	if (CenterArray.Num() && CenterArray[0])
		DistinationCenter = CenterArray[0];

	/**
	* Sets the DeliveryID Widget as assigned in the BP
	* At this Point this method is Garenteed to Work.
	* Any Call before this Point will result in Unkowing Behaviour.
	*/
	SetDeliveryID(DeliveryID);
	
}

void ADestination::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	InitOutlineVFX();
}

void ADestination::ChangeTo(ADestination* OtherDestination)
{
	this->DoubleScore = OtherDestination->DoubleScore;
	this->Score = OtherDestination->Score;
	this->PlayerTypeName = OtherDestination->PlayerTypeName;
	this->DeliveryID = OtherDestination->DeliveryID;
	TArray<UActorComponent*> Components = OtherDestination->GetComponentsByTag(
		UActorComponent::StaticClass(), "MainMesh");
	if (!Components.Num())
	{
		return;
	}
	auto OtherStaticMeshComponent = Cast<UStaticMeshComponent>(Components[0]);
	Components = this->GetComponentsByTag(UActorComponent::StaticClass(), "MainMesh");
	if (!Components.Num())
	{
		return;
	}
	auto ThisStaticMeshComponent = Cast<UStaticMeshComponent>(Components[0]);
	if (OtherStaticMeshComponent && ThisStaticMeshComponent)
	{
		UStaticMesh* OtherStaticMesh = OtherStaticMeshComponent->GetStaticMesh();
		ThisStaticMeshComponent->SetStaticMesh(OtherStaticMesh);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Cant Get StaticMeshComponenet in %s"), *GetName());
	}
	SetDeliveryID(DeliveryID);
}

bool ADestination::IsDirtyVfx() const
{
	return bDirtyVFX;
}

bool ADestination::SetDeliveryID(int32 NewID)
{
	if(PlayerTypeName == "Bank") return true;
	DeliveryID = NewID;
	auto UserWidgetComp = Cast<UWidgetComponent>(GetComponentByClass(UWidgetComponent::StaticClass()));
	if (!UserWidgetComp)
	{
		UE_LOG(LogTemp, Error, TEXT("UserWidgetComp is nullptr in ADestination::BeginPlay"));
		return false;
	}

	auto DeliveryIDWidget = Cast<UHouseDeliveryIDWidget>(UserWidgetComp->GetWidget());
	if (!DeliveryIDWidget)
	{
		UE_LOG(LogTemp, Error, TEXT("DeliveryIDWidget is nullptr in ADestination::BeginPlay"));
		return false;
	}

	auto IconTex = IconsMap[static_cast<EDeliveryID>(DeliveryID)];
	if (!IconTex)
	{
		UE_LOG(LogTemp, Error, TEXT("IconTex is nullptr in ADestination::BeginPlay"));
		return false;
	}
	DeliveryIDWidget->SetImageBrush(IconTex);
	return true;
}

void ADestination::InitOutlineVFX()
{
	// All Rights Received Ahmed Samir
	if (!bDirtyVFX)
	{
		return;
	}

	if (GetNetMode() == NM_DedicatedServer)
	{
		return;
	}

	if (!OutlineVFXComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("OutlineVFXComponent is NULL in ADestination::InitOutlineVFX in: %s"), *GetName());
		return;
	}

	auto* World = GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Error, TEXT("World is NULL in ADestination::InitOutlineVFX in: %s"), *GetName());
		return;
	}

	auto PlayerController = World->GetFirstPlayerController<ADRInGamePlayerController>();
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerController is NULL in ADestination::InitOutlineVFX in: %s"), *GetName());
		return;
	}

	ADRInGamePlayerState* TempPlayerState = PlayerController->GetPlayerState<ADRInGamePlayerState>();
	if (!TempPlayerState)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerController is NULL in ADestination::InitOutlineVFX in: %s"), *GetName());
		return;
	}

	TArray<UActorComponent*> Components = GetComponentsByTag(UActorComponent::StaticClass(), "MainMesh");

	if (!Components.Num())
	{
		UE_LOG(LogTemp, Error, TEXT("No FreezeMesh in ADestination::InitOutlineVFX  in: %s"), *GetName());
		return;
	}

	UStaticMeshComponent* MainMesh = Cast<UStaticMeshComponent>(Components[0]);

	UStaticMeshComponent* FreezeMesh = Cast<UStaticMeshComponent>(Components[0]);
	if (!MainMesh)
	{
		UE_LOG(LogTemp, Error, TEXT("MainMesh nullptr in ADestination::InitOutlineVFX in: %s"), *GetName());
		return;
	}

	OutlineVFXComponent->SetTargetMesh(MainMesh);
	bDirtyVFX = false;
	if (PlayerTypeName == TempPlayerState->PlayerType)
	{
		OutlineVFXComponent->ShowOutline();
	}


	// End of Copy Rights Notice.
}

void ADestination::OnOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	/// Just In Case
	if(!GetWorld()) return;

	auto DRGameMode = GetWorld()->GetAuthGameMode<ADRGameMode>(); 
	
	// NotServer or  GameMode is Un-Available
	if(!DRGameMode) return;
	
	auto Car = Cast<ACar>(OtherActor); // Collided only with a car
	if (!Car)
	{
		return;
	}
	
	DRGameMode->IncreaseArrivedCars();
	auto CarPlayerState = DRGameMode->GetPlayerStateByPlayerTypeName(Car->PlayerTypeName);
	auto DestinationPlayerState = DRGameMode->GetPlayerStateByPlayerTypeName(PlayerTypeName);
	
	// A PowerUp is Applied to this destination
	if (IsStateBound(EPowerUpsActorStates::OverlapState))
	{
		ExecuteEffect(EPowerUpsActorStates::OverlapState, Car);
		return;
	}
	
	if(!CarPlayerState and !DestinationPlayerState)
	{
		Car->Destroy();
		return;
	}
	
	// the car is not Golden, No player currently playing with this type
	if(!CarPlayerState and Car->PlayerTypeName != GoldenCarType)
	{
		Car->Destroy();
		return;
	}
	
	// the destination is not Bank, no player currently playing with this type
	if(!DestinationPlayerState and PlayerTypeName != BankType) 
	{
		// the car reached the wrong destination 
		CarPlayerState->PlayMissScoreSound();
		Car->Destroy();
		return;
	}
	
	if (PlayerTypeName == BankType and Car->PlayerTypeName != GoldenCarType)
	{
		//This destination is a Bank and the Car is not Golden, Hence it has an owner.
		CarPlayerState->OnUpdateCoins(BankCoins);
		CarPlayerState->PlayBankSound();
	}
	else if (Car->PlayerTypeName == GoldenCarType)
	{
		//Golden Car Reached This Destination
		DRGameMode->UpdateScore(PlayerTypeName, GoldenCarScore);
		DestinationPlayerState->PlayGoldenCarSound();
	}
	else if (Car->PlayerTypeName == PlayerTypeName)
	{
		//Car reached the correct destination type
		if (Car->GetCarNumber() == this->DeliveryID)
		{
			//car reached the exact destination 
			DRGameMode->UpdateScore(PlayerTypeName, DoubleScore + Score);
			DestinationPlayerState->PlayDoubleScoreSound();
		}
		else
		{
			DRGameMode->UpdateScore(PlayerTypeName, Score);
			DestinationPlayerState->PlayScoreSound();
		}
	}
	else if(CarPlayerState)
	{
		// the car reached the wrong destination 
		CarPlayerState->PlayMissScoreSound();
	}
	
	Car->Destroy();
}



/**
 *
 *
 *
 *	Getters Section
 *
 *
 * 
 */

FVector ADestination::GetReachablePosition()
{
	//if (DistinationCenter)
		return DistinationCenter->GetComponentLocation();
	//return GetActorLocation();
}

TMap<EDeliveryID, UTexture2D*> ADestination::GetIconsMap() const
{
	return IconsMap;
}

int32 ADestination::GetScore() const
{
	return Score;
}

int32 ADestination::GetDoubleScore() const
{
	return DoubleScore;
}

int32 ADestination::GetBankCoins() const
{
	return BankCoins;
}

int32 ADestination::GetGoldenCarScore() const
{
	return GoldenCarScore;
}

FString ADestination::GetPlayerTypeName() const
{
	return PlayerTypeName;
}

int32 ADestination::GetDeliveryID() const
{
	return DeliveryID;
}

FString ADestination::GetBankType() const
{
	return BankType;
}

FString ADestination::GetGoldenCarType() const
{
	return GoldenCarType;
}