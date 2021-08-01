
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "DRPlayerStateBase.generated.h"

/**
 * 
 */
UCLASS()
class DELIVERYRUSH_API ADRPlayerStateBase : public APlayerState
{
	GENERATED_BODY()

public:

	UPROPERTY(ReplicatedUsing = OnRep_PlayerType)
		FString PlayerType;



	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

	UFUNCTION()
	virtual	void OnRep_PlayerType();

};
