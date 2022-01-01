
#include "InventoryComponent.h"
#include "Net/UnrealNetwork.h"
#include "Engine/ActorChannel.h"

#define LOCTEXT_NAMESPACE "Inventory"

UInventoryComponent::UInventoryComponent()
{
	SetIsReplicated(true);
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UInventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UInventoryComponent, current_items);
}

bool UInventoryComponent::ReplicateSubobjects(class UActorChannel* Channel, class FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool wrote_to_actor_channel = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	if (Channel->KeyNeedsToReplicate(0, replicated_items_key))
	{
		for (auto& item : current_items)
		{
			wrote_to_actor_channel |= Channel->ReplicateSubobject(item, *Bunch, *RepFlags);
		}
	}

	return wrote_to_actor_channel;
}

UItemBase* UInventoryComponent::AddItem(class UItemBase* item)
{
	if (GetOwner() && GetOwner()->HasAuthority()) // Checks to make sure this is the server, then duplicates the item to the player. 
	{
		UItemBase* new_item = NewObject<UItemBase>(GetOwner(), item->GetClass()); 
		new_item->SetQuantity(item->GetQuantity());
		new_item->owning_inventory = this;
		new_item->AddedToInventory(this);
		current_items.Add(new_item);
		new_item->MarkDirtyForReplication(); //Replicates

		return new_item;
	}

	return nullptr; //If client and not server
}

void UInventoryComponent::OnRep_Items()
{
	ClientRefreshInventory();
}

FItemAddResult UInventoryComponent::TryAddItem_Internal(class UItemBase* item)
{
	if (GetOwner() && GetOwner()->HasAuthority())
	{
		const int32 add_amount = item->GetQuantity();

		if (current_items.Num() + 1 > GetSlotCapacity()) // Add nothing if the current_items TArray is greater then the max slot capacity
		{
			return FItemAddResult::AddedNone(add_amount, LOCTEXT("InventoryCapacityFullText", "Cannot hold anything else. Inventory is full!"));
		}
		
		if (!FMath::IsNearlyZero(item->weight)) // if the item has weight
		{
			if (GetCurrentWeight() + item->weight > GetWeightCapacity()) //If the weight of the item you are adding pushes the inventory weight above max, add nothing. 
			{
				return FItemAddResult::AddedNone(add_amount, LOCTEXT("InventoryTooMuchWeightText", "Cannot hold anything else, Too heavy!"));
			}
		}

		if (item->is_stackable) // if the item is stackable, do not let the item quantity exceed stack size
		{
			ensure(item->GetQuantity() <= item->max_stack_size);

			if (UItemBase* existing_item = FindItem(item)) // if the item is stackable, is it already in the inventory
			{
				if(existing_item->GetQuantity() < existing_item->max_stack_size) // If the stack is not full
				{ 
					const int32 capacity_max_add_amount = existing_item->max_stack_size - existing_item->GetQuantity(); //How much space is remaining in stack
					int32 actual_add_amount = FMath::Min(add_amount, capacity_max_add_amount); // either all that is trying to be added or the space that is left before stack is full

					FText error_text = LOCTEXT("InventoryErrorText", "Couldn't add all of the items to your inventory.");

					if (!FMath::IsNearlyZero(item->weight)) // if the item has weight
					{
						const int32 weight_max_add_amount = FMath::FloorToInt((weight_capacity - GetCurrentWeight()) / item->weight);
						actual_add_amount = FMath::Min(actual_add_amount, weight_max_add_amount);

						if (actual_add_amount < add_amount) // if what is getting added is less than what was attempted
						{
							error_text = FText::Format(LOCTEXT("InventoryTooMuchWeightText", "Couldn't add entire stack of {item_name} to inventory."), item->item_display_name);
						}
					}
					else if (actual_add_amount < add_amount) 
					{
						error_text = FText::Format(LOCTEXT("InventoryCapacityFullText", "Counldn't add entire stack of {item_name} to inventory. Inventory is full."), item->item_display_name);
					}

					if (add_amount <= 0) // has to be 1 or more
					{
						return FItemAddResult::AddedNone(add_amount, FText::Format(LOCTEXT("InventoryErrorText", "Couldn't add {item_name} to inventory."), item->item_display_name));
					}

					existing_item->SetQuantity(existing_item->GetQuantity() + actual_add_amount); // Setting the new item quantity since we already had the item in the inventory and we know the actual add amount checked out okay. 

					ensure(existing_item->GetQuantity() <= existing_item->max_stack_size); // double check the item quantity is less that or equal to the max_stack_size

					if (actual_add_amount < add_amount) 
					{
						return FItemAddResult::AddedSome(add_amount, actual_add_amount, error_text);
					}
					else
					{
						return FItemAddResult::AddedAll(add_amount);
					}
				}
				else
				{
					return FItemAddResult::AddedNone(add_amount, FText::Format(LOCTEXT("InventoryFullStackText", "Couldn't add {item_name}. There is already too many of this item!"), item->item_display_name));
				}
			}
			else
			{
				AddItem(item);
				return FItemAddResult::AddedAll(add_amount);
			}
		}
		else //item is not stackable
		{
			ensure(item->GetQuantity() == 1);
			AddItem(item);
			return FItemAddResult::AddedAll(add_amount);
		}

	} 

	check(false);
	return FItemAddResult::AddedNone(-1, LOCTEXT("ErrorMessage", "")); // function cannot be called on client.

}

FItemAddResult UInventoryComponent::TryAddItem(class UItemBase* item)
{
	return TryAddItem_Internal(item);
}

FItemAddResult UInventoryComponent::TryAddItemFromClass(TSubclassOf<class UItemBase> item_class, const int32 quantity)
{
	UItemBase* item = NewObject<UItemBase>(GetOwner(), item_class); // Create object
	item->SetQuantity(quantity); // Set amount

	return TryAddItem_Internal(item);
}

int32 UInventoryComponent::ConsumeItem(class UItemBase* item)
{
	if (item)
	{
		ConsumeItem(item, item->GetQuantity());
	}
	return 0;
}

int32 UInventoryComponent::ConsumeItem(class UItemBase* item, const int32 quantity)
{
	if (GetOwner() && GetOwner()->HasAuthority() && item)
	{
		const int32 remove_quantity = FMath::Min(quantity, item->GetQuantity()); // remove_quantity = passed in quantity or item quantity, depending on which is the smaller value. 
		
		ensure(!(item->GetQuantity() - remove_quantity < 0)); // Stop from having a negative amount

		item->SetQuantity(item->GetQuantity() - remove_quantity); // item quantity set to current quantity - result from remove_quantity

		if(item->GetQuantity() <= 0) // if no item is left, remove from inventory
		{
			RemoveItem(item); 
		}
		else // else update the client with the new amount 
		{
			ClientRefreshInventory(); 
		}

		return remove_quantity;
	}

	return 0; //if not the server
}

bool UInventoryComponent::RemoveItem(class UItemBase* item)
{
	if (GetOwner() && GetOwner()->HasAuthority())
	{
		if (item)
		{
			current_items.RemoveSingle(item);

			replicated_items_key++;

			ClientRefreshInventory();

			return true;
		}
	}

	return false;
}

bool UInventoryComponent::HasItem(TSubclassOf<UItemBase> item_class, const int32 quaintity /*= 1*/)
{
	if (UItemBase* item_to_find = FindItemByClass(item_class))
	{
		return item_to_find->GetQuantity() >= quaintity;
	}
	return false;
}

UItemBase* UInventoryComponent::FindItem(class UItemBase* item) const
{
	if (item)
	{
		for (auto& inventory_item : current_items)
		{
			if (inventory_item && inventory_item->GetClass() == item->GetClass())
			{
				return inventory_item;
			}
		}
	}
	return nullptr;
}

UItemBase* UInventoryComponent::FindItemByClass(TSubclassOf<class UItemBase> item_class) const
{
	for (auto& inventory_item : current_items)
	{
		if (inventory_item && inventory_item->GetClass() == item_class)
		{
			return inventory_item;
		}
	}

	return nullptr;
}

TArray<UItemBase*> UInventoryComponent::FindItemsByClass(TSubclassOf<class UItemBase> item_class) const
{
	TArray<UItemBase*> items_of_class;

	for (auto& inventory_item : current_items)
	{
		if (inventory_item && inventory_item->GetClass()->IsChildOf(item_class))
		{
			items_of_class.Add(inventory_item);
		}
	}

	return items_of_class;
}

float UInventoryComponent::GetCurrentWeight()
{
	float weight = 0.f;

	for (auto& item : current_items)
	{
		if (item)
		{
			weight += item->GetStackWeight();
		}
	}

	return weight;
}

void UInventoryComponent::SetWeightCapacity(const int32 new_capacity)
{
	weight_capacity = new_capacity;
	ClientRefreshInventory();
}

void UInventoryComponent::SetSlotCapacity(const int32 new_capacity)
{
	slot_capacity = new_capacity;
	//ClientRefreshInventory();
}

void UInventoryComponent::ClientRefreshInventory_Implementation()
{
	OnInventoryUpdated.Broadcast();
}

#undef LOCTEXT_NAMESPACE