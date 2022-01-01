
#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "Engine/DataTable.h"
#include "ItemSpawnPoint.generated.h"

USTRUCT(BlueprintType)
struct FLootTableRow : public FTableRowBase
{
	GENERATED_BODY()

	public:

	UPROPERTY(EditDefaultsOnly, Category = "Loot")
	TArray<TSubclassOf<class UItemBase>> items;

	
	UPROPERTY(EditDefaultsOnly, Category = "Loot", meta = (ClampMin = 0.001, ClampMax = 1.0))
	float roll_probablity;
};

UCLASS()
class SURVIVALGAME_API AItemSpawnPoint : public ATargetPoint
{
	GENERATED_BODY()

public:
	AItemSpawnPoint();

	UPROPERTY(EditAnywhere, Category = "Loot")
	class UDataTable* loot_table;

	UPROPERTY(EditDefaultsOnly, Category = "Loot")
	TSubclassOf<class APickup> pickup_class;

	UPROPERTY(EditDefaultsOnly, Category = "Loot")
	FIntPoint respawn_range;

protected:

	FTimerHandle respawn_timer;

	UPROPERTY()
	TArray<AActor*> spawned_pickups; // keep track of curently spawned item so another cannot spawn until this one is taken

	virtual void BeginPlay() override;

	UFUNCTION()
	void SpawnItem();

	UFUNCTION()
	void OnItemTaken(AActor* destroyed_actor);
	
};
