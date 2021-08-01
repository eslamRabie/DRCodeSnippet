
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Reachable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UReachable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DELIVERYRUSH_API IReachable
{
	GENERATED_BODY()

	
public:
	virtual FVector GetReachablePosition() = 0;
};
