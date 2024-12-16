// © Artem Podorozhko. All Rights Reserved. This project, including all associated assets, code, and content, is the property of Artem Podorozhko. Unauthorized use, distribution, or modification is strictly prohibited.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PoolActor.generated.h"

class AAbstractActorPool;
// This class does not need to be modified.
UINTERFACE()
class ACTORPOOL_API UPoolable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ACTORPOOL_API IPoolable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ActivatePoolActor(AAbstractActorPool* InActorPool);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void DeActivePoolActor();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void RequestReturn();
};
