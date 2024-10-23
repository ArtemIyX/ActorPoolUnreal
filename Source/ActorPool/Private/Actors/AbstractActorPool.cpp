// © Artem Podorozhko. All Rights Reserved. This project, including all associated assets, code, and content, is the property of Artem Podorozhko. Unauthorized use, distribution, or modification is strictly prohibited.


#include "Actors/AbstractActorPool.h"

#include "Data/Interfaces/PoolActor.h"
#include "Net/UnrealNetwork.h"
#include "Net/Core/PushModel/PushModel.h"


// Sets default values
AAbstractActorPool::AAbstractActorPool(): PoolSize(10)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
}


// Called when the game starts or when spawned
void AAbstractActorPool::BeginPlay()
{
	Super::BeginPlay();

	if (bInitializePool)
	{
		// Note that every mode less than this value is a kind of server, so checking NetMode < NM_Client is always some variety of server.
		if (GetNetMode() < NM_Client || bSpawnOnClient)
		{
			InitializePool();
		}
	}
}

void AAbstractActorPool::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	FDoRepLifetimeParams Params;
	Params.bIsPushBased = true;
	DOREPLIFETIME_WITH_PARAMS_FAST(AAbstractActorPool, Pool, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(AAbstractActorPool, Active, Params);
}

// Called every frame
void AAbstractActorPool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


AActor* AAbstractActorPool::MakeActor_Implementation()
{
	// Override in your class
	return nullptr;
}

void AAbstractActorPool::OnRep_Pool()
{
	
}

void AAbstractActorPool::OnRep_Active()
{
	
}

void AAbstractActorPool::InitializePool()
{
	for (int32 i = 0; i < PoolSize; ++i)
	{
		AActor* newActor = MakeActor();
		if (IsValid(newActor) && newActor->Implements<UPoolable>())
		{
			IPoolable::Execute_DeActivePoolActor(newActor);
			Pool.Add(newActor);
		}
	}
	MARK_PROPERTY_DIRTY_FROM_NAME(AAbstractActorPool, Pool, this);
}

AActor* AAbstractActorPool::GetActorFromPool()
{
	AActor* act;
	if (Pool.Num() > 0)
	{
		act = Pool.Pop();
	}
	else
	{
		act = MakeActor();
	}
	if (IsValid(act))
	{
		Active.Add(act);
		if (act->Implements<UPoolable>())
		{
			IPoolable::Execute_ActivatePoolActor(act, this);
		}
	}
	MARK_PROPERTY_DIRTY_FROM_NAME(AAbstractActorPool, Pool, this);
	MARK_PROPERTY_DIRTY_FROM_NAME(AAbstractActorPool, Active, this);
	return act;
}

void AAbstractActorPool::ReturnActor(AActor* InActor)
{
	if (IsValid(InActor))
	{
		if (InActor->Implements<UPoolable>())
		{
			IPoolable::Execute_DeActivePoolActor(InActor);
		}
		Active.Remove(InActor);
		Pool.Add(InActor);
		MARK_PROPERTY_DIRTY_FROM_NAME(AAbstractActorPool, Pool, this);
		MARK_PROPERTY_DIRTY_FROM_NAME(AAbstractActorPool, Active, this);
	}
}
