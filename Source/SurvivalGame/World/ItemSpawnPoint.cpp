// Fill out your copyright notice in the Description page of Project Settings.


#include "World/ItemSpawnPoint.h"
#include "Engine/World.h"
#include "World/Pickup.h"
#include "Items/ItemBase.h"

AItemSpawnPoint::AItemSpawnPoint()
{
	PrimaryActorTick.bCanEverTick = false;
	bNetLoadOnClient = false;

	respawn_range = FIntPoint(10, 30);
}

void AItemSpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		SpawnItem();
	}
}

void AItemSpawnPoint::SpawnItem()
{
	if (HasAuthority() && loot_table)
	{
		TArray<FLootTableRow*> spawn_items;
		loot_table->GetAllRows("", spawn_items);

		const FLootTableRow* loot_row = spawn_items[FMath::RandRange(0, spawn_items.Num() - 1)];

		ensure(loot_row);

		float probability_roll = FMath::FRandRange(0.f, 1.f);

		while (probability_roll > loot_row->roll_probablity)
		{
			loot_row = spawn_items[FMath::RandRange(0, spawn_items.Num() - 1)];
			probability_roll = FMath::FRandRange(0.f, 1.f);
		}

		if (loot_row && loot_row->items.Num() && pickup_class)
		{
			float angle = 0.f;
			for (auto& item_class : loot_row->items)
			{
				const FVector location_offset = FVector(FMath::Cos(angle), FMath::Sin(angle), 0.f) * 50;

				FActorSpawnParameters spawn_params;
				spawn_params.bNoFail = true;
				spawn_params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

				const int32 item_quantity = item_class->GetDefaultObject<UItemBase>()->GetQuantity();

				FTransform spawn_transform = GetActorTransform();
				spawn_transform.AddToTranslation(location_offset);

				APickup* pickup = GetWorld()->SpawnActor<APickup>(pickup_class, spawn_transform, spawn_params);
				pickup->InitializePickcup(item_class,item_quantity);
				pickup->OnDestroyed.AddUniqueDynamic(this, &AItemSpawnPoint::OnItemTaken);

				spawned_pickups.Add(pickup);

				angle += (PI * 2.f) / loot_row->items.Num();
			}
		}
	}
}

void AItemSpawnPoint::OnItemTaken(AActor* destroyed_actor)
{

	if(HasAuthority())
	{ 
		spawned_pickups.Remove(destroyed_actor);

		if (spawned_pickups.Num() <= 0)
		{
			GetWorldTimerManager().SetTimer(respawn_timer, this, &AItemSpawnPoint::SpawnItem, FMath::RandRange(respawn_range.GetMin(), respawn_range.GetMax()), false);
		}
	}
}
