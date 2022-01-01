
#include "World/LootableActor.h"
#include "Components/InteractionComponent.h"
#include "Components/InventoryComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/DataTable.h"
#include "Items/ItemBase.h"
#include "Player/CharacterBase.h"
#include "World/ItemSpawnPoint.h"

#define LOCTEXT_NAMESPACE "LootableActor"

ALootableActor::ALootableActor()
{
	loot_container_mesh = CreateDefaultSubobject<UStaticMeshComponent>("LootContainerMesh");
	SetRootComponent(loot_container_mesh);

	loot_interaction_comp = CreateDefaultSubobject<UInteractionComponent>("LootInteraction");
	loot_interaction_comp->interactable_action_text = LOCTEXT("LootActorText", "Search");
	loot_interaction_comp->interactable_name_text = LOCTEXT("LootActorName", "Chest");
	loot_interaction_comp->SetupAttachment(GetRootComponent());

	loot_inventory = CreateDefaultSubobject<UInventoryComponent>("Inventory");
	loot_inventory->SetSlotCapacity(20);
	loot_inventory->SetWeightCapacity(100.f);

	loot_rolls = FIntPoint(2, 8);

	SetReplicates(true);

}

void ALootableActor::BeginPlay()
{
	Super::BeginPlay();

	loot_interaction_comp->on_interact.AddDynamic(this, &ALootableActor::OnInteract);

	if (HasAuthority() && loot_data_table)
	{
		TArray<FLootTableRow*> spawn_items;
		loot_data_table->GetAllRows("", spawn_items);

		int32 rolls = FMath::RandRange(loot_rolls.GetMin(), loot_rolls.GetMax());

		for (int32 i = 0; i < rolls; ++i)
		{
			const FLootTableRow* loot_row = spawn_items[FMath::RandRange(0, spawn_items.Num() - 1)];

			ensure(loot_row);

			float probability_of_roll = FMath::FRandRange(0.f, 1.f);

			while (probability_of_roll > loot_row->roll_probablity)
			{
				loot_row = spawn_items[FMath::RandRange(0, spawn_items.Num() - 1)];
				probability_of_roll = FMath::FRandRange(0.f, 1.f);
			}

			if(loot_row && loot_row->items.Num())
			{
				for (auto& item_class : loot_row->items)
				{
					if (item_class)
					{
						const int32 quantity = Cast<UItemBase>(item_class.GetDefaultObject())->GetQuantity();
						loot_inventory->TryAddItemFromClass(item_class, quantity);
					}
				}
			}
		}
	}
	
}

void ALootableActor::OnInteract(class ACharacterBase* player)
{
	if (player)
	{
		player->SetLootSource(loot_inventory);
		player->player_inventory->ClientRefreshInventory();
	}
}

#undef LOCTEXT_NAMESPACE