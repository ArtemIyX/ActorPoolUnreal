# Actor Pool Plugin for Unreal Engine 5.3.2+

## Overview

The ActorPool plugin provides a flexible and efficient system for managing a pool of reusable actors in Unreal Engine. 
By utilizing an object pooling pattern, this plugin allows developers to optimize performance by reusing actors instead of repeatedly spawning and destroying them.
The plugin is written in C++ and is fully customizable via Blueprints, making it suitable for both programmers and designers.

## Features

- Object Pooling: Efficiently manage a pool of actors to reduce instantiation overhead.
- Blueprint Support: Functions like GetActorFromPool, ReturnActor, and MakeActor are exposed to Blueprints for easy customization.
- Network Replication: The pool and active actor lists are replicated for multiplayer compatibility.
- Customizable Pool Initialization: Configure pool size, initialization behavior, and spawning options via Blueprint properties.
- Extensible: Override MakeActor and InitializePool in C++ or Blueprints to tailor actor creation and pool setup.

## C++ Example

```C++
// Example of using the pool in C++
AAbstractActorPool* Pool = GetWorld()->SpawnActor<AAbstractActorPool>();
AActor* PooledActor = Pool->GetActorFromPool();
if (PooledActor)
{
    // Use the actor (e.g., set location, activate behavior)
    PooledActor->SetActorLocation(FVector(100, 100, 100));
}

// When done, return the actor to the pool
Pool->ReturnActor(PooledActor);
```

## Limitations

- Actors in the pool must implement the **IPoolable** interface to ensure proper activation and deactivation.
- The plugin assumes actors are lightweight and suitable for pooling. Heavy actors with complex initialization may require additional optimization.
- Network replication is supported, but ensure proper testing in multiplayer scenarios to avoid synchronization issues.

## Support

For issues, feature requests, or contributions, please contact the plugin developer or submit an issue on the project's repository.

## License

This plugin is provided under the MIT License. See the LICENSE file for details.
