// © Artem Podorozhko. All Rights Reserved. This project, including all associated assets, code, and content, is the property of Artem Podorozhko. Unauthorized use, distribution, or modification is strictly prohibited.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "AbstractActorPool.generated.h"

/**
 * @class AAbstractActorPool
 * @brief Manages a pool of actors, allowing for efficient reuse of actors in a scene.
 * 
 * This class contains methods for managing a pool of actors. It allows actors to be retrieved
 * from the pool and returned when no longer in use. The pool can be initialized and customized
 * via Blueprint and C++.
 */
UCLASS(Blueprintable, BlueprintType)
class ACTORPOOL_API AAbstractActorPool : public AInfo
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAbstractActorPool();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	/**
	 * @brief Array of actors available in the pool.
	 * 
	 * This TArray holds the actors that are currently available in the pool.
	 * It is replicated using the OnRep_Pool function.
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Pool, Category="ActorPool")
	TArray<AActor*> Pool;

	/**
	 * @brief Array of actors currently in use.
	 * 
	 * This TArray holds the actors that are currently active (in use).
	 * It is replicated using the OnRep_Active function.
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Active, Category="ActorPool")
	TArray<AActor*> Active;

	/**
	 * @brief Flag to initialize the pool on start.
	 * 
	 * A boolean flag that determines whether the pool should be initialized.
	 * Set to true by default. Can be customized in Blueprint.
	 */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="ActorPool")
	bool bInitializePool{true};

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="ActorPool",
		meta=(ClampMin=1, EditCondition="bInitializePool"))
	int32 PoolSize;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="ActorPool", meta=(EditCondition="bInitializePool"))
	bool bSpawnOnClient{false};

protected:
	UFUNCTION()
	virtual void OnRep_Pool();

	UFUNCTION()
	virtual void OnRep_Active();
	/**
	 * @brief Creates an actor to be added to the pool.
	 * 
	 * A BlueprintNativeEvent function that allows you to create an actor for the pool.
	 * This function can be overridden in Blueprint or C++ to customize actor creation.
	 * 
	 * @return A pointer to the created actor.
	 */
	UFUNCTION(BlueprintNativeEvent, Category="ActorPool")
	AActor* MakeActor();

	/**
	 * @brief Initializes the actor pool.
	 * 
	 * A virtual function that is responsible for initializing the actor pool.
	 * This function can be overridden in C++ for custom initialization behavior.
	 */
	UFUNCTION()
	virtual void InitializePool();

public:
	/**
	 * @brief Retrieves an actor from the pool.
	 * 
	 * This function gets an actor from the pool. If the pool is empty, it might
	 * call MakeActor() to create a new actor. Can be called from Blueprint.
	 * 
	 * @return A pointer to an actor.
	 */
	UFUNCTION(BlueprintCallable, Category="ActorPool")
	virtual AActor* GetActorFromPool();

	/**
	 * @brief Returns an actor back to the pool.
	 * 
	 * This function returns an actor to the pool after it has been used. The actor
	 * will be marked as inactive and returned to the available pool.
	 * 
	 * @param InActor The actor to be returned to the pool.
	 */
	UFUNCTION(BlueprintCallable, Category="ActorPool")
	virtual void ReturnActor(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category="ActorPool")
	int32 GetPoolNum() const;

	UFUNCTION(BlueprintCallable, Category="ActorPool")
	int32 GetActiveNum() const;
};
