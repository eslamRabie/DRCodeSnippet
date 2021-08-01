
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DRPlayerControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class DELIVERYRUSH_API ADRPlayerControllerBase : public APlayerController
{
	GENERATED_BODY()
	

protected:
	virtual void BeginPlay() override;

};
