
#include "DRPlayerStateBase.h"

#include "Net/UnrealNetwork.h"

void ADRPlayerStateBase::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ADRPlayerStateBase, PlayerType);
}

void ADRPlayerStateBase::OnRep_PlayerType()
{
	
}
