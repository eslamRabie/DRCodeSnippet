/*
 * Old House Class
 */

#pragma once

#include "CoreMinimal.h"
#include "DRGameMode.h"
#include "Reachable.h"
#include "GameFramework/Actor.h"
#include "FPowerUpApplicableBase.h"
#include "SoundManager.h"

#include "Destination.generated.h"

UENUM(BlueprintType, Blueprintable)
enum class EDeliveryID: uint8
{
	ID1,
	ID2,
	ID3
};

/**
 * A class that Represent Destinations on level,
 * PowerUps Applicable <PowerUps Can Be Applied on It>
 * Reachable <Can Be Used in the traffic light system as a next destination>
 */
UCLASS()
class DELIVERYRUSH_API ADestination : public AActor, public IReachable,  public FPowerUpApplicableBase
{
	GENERATED_BODY()
public:	

	// Sets default values for this actor's properties
	ADestination();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/**
	 * Called when this destination overlapped with in game objects
	 * Used to detect Cars.
	 */	
	UFUNCTION()
	void OnOverlap(AActor* OverlappedActor, AActor* OtherActor);

	/**
	 * Deprecated 
	 * Swap Destinations Mesh and Data,
	 * Does not work with the current VFX system
	 */ 
	UFUNCTION()
	void ChangeTo(ADestination* OtherDestination);

	/// Can Be Used By layout Manager to set DeliveryID when the widget is ready
	bool SetDeliveryID(int32 NewID);
	
	/// Freeze Mesh Component, to be replaced with a more dynamic system 
	UPROPERTY(EditDefaultsOnly, Category=VFX)
	class UDynamicVFXComponent* FreezeVFXComponent;

	/// Reference to the traffic light pointing at this destination, to be replace with a more dynamic system   
	UPROPERTY(EditInstanceOnly, Category=Design)
	ATrafficController* TrafficLightReference;

	UPROPERTY(EditDefaultsOnly, Category = AI)
		USkeletalMeshComponent* DistinationCenter;
	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	//FVector GetReachablePosition_Implementation() override;
	virtual FVector GetReachablePosition() override;

	UPROPERTY(EditDefaultsOnly, Category=Design)
	TMap<EDeliveryID, UTexture2D*> IconsMap;

	UPROPERTY(EditDefaultsOnly, Category=VFX)
	class UDynamicVFXComponent* OutlineVFXComponent;
	
private:

	/// Basic Score 
	UPROPERTY(EditAnywhere, Category = "Design")
	int32 Score;

public:
	/**
	 * Class Properties Getters
	 */
	TMap<EDeliveryID, UTexture2D*> GetIconsMap() const;
	int32 GetScore() const;
	int32 GetDoubleScore() const;
	int32 GetBankCoins() const;
	int32 GetGoldenCarScore() const;
	FString GetPlayerTypeName() const;
	int32 GetDeliveryID() const;
	FString GetBankType() const;
	FString GetGoldenCarType() const;
	bool IsDirtyVfx() const;

	void TestDelegate(AActor*)
	{
		UE_LOG(LogTemp, Error, TEXT("Delegate Called!"));
	}
	
private:
	/// Double Scoring Score
	UPROPERTY(EditAnywhere, Category = "Design")
	int32 DoubleScore;

	/// The Coins given by the Bank 
	UPROPERTY(EditAnywhere, Category = "Design")
	int32 BankCoins;

	/// The Score given for delivering a GoldenCar 
	UPROPERTY(EditAnywhere, Category = "Design")
	int32 GoldenCarScore;

	/// The Destination's Owner's Type, To be replaced with an enum
	UPROPERTY(EditAnywhere, Category=Design)
	FString PlayerTypeName;

	/// The Destination's Exact ID
	UPROPERTY(EditAnywhere, Category = "Design")
	int32 DeliveryID;

	FString BankType;
	FString GoldenCarType;
	
	/// Used to Check if the VFX is Assigned Correctly
	bool bDirtyVFX = true;

	// Initialize the OutLine VFX Component, To be replaced with a More Dynamic System
	void InitOutlineVFX();

	// for searching a destination 
	friend bool operator==(const ADestination& Lhs, const ADestination& RHS)
	{
		return Lhs.DeliveryID == RHS.DeliveryID
			&& Lhs.PlayerTypeName == RHS.PlayerTypeName;
	}

	friend bool operator!=(const ADestination& Lhs, const ADestination& RHS)
	{
		return !(Lhs == RHS);
	}
};


