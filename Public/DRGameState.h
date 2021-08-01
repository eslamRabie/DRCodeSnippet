// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Shop.h"
#include "GameFramework/GameState.h"
#include "DRGameState.generated.h"

/**
 *
 */
UCLASS()
class DELIVERYRUSH_API ADRGameState : public AGameState
{
	GENERATED_BODY()

public:

	ADRGameState();




protected:
	
	virtual void BeginPlay() override;


private:

	
};
