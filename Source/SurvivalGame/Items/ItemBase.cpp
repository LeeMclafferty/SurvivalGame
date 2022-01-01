
#include "Items/ItemBase.h"

#include "Components/InventoryComponent.h"
#include "Net/UnrealNetwork.h"

#define  LOCTEXT_NAMESPACE "Item" // I don't quite get how this works yet, but it makes the text users will see able to be translated to other languages

UItemBase::UItemBase()
{
	item_display_name = LOCTEXT("ItemName", "Item");
	use_action_text = LOCTEXT("ItemUseActionText", "Use");
	weight = 0.f;
	is_stackable = true;
	quantity = 1;
	rep_key = 0;
	
}

bool UItemBase::ShouldShowInventory() const
{
	return true;
}

void UItemBase::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UItemBase, quantity);
}

bool UItemBase::IsSupportedForNetworking() const 
{
	return true;
}

#if WITH_EDITOR // This function is for editor use only, it will not be in packaged game.
void UItemBase::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	FName changed_property_name = PropertyChangedEvent.Property ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	if (changed_property_name == GET_MEMBER_NAME_CHECKED(UItemBase, quantity))
	{
		quantity = FMath::Clamp(quantity, 1, is_stackable ? max_stack_size : 1);
	}
}
#endif

void UItemBase::MarkDirtyForReplication()
{
	++rep_key; // mark this item for replication

	if (owning_inventory)
	{
		++owning_inventory->replicated_items_key; // mark inventory array for replication.
	}
}

void UItemBase::OnRep_Quantity()
{
	OnItemModified.Broadcast();
}

void UItemBase::SetQuantity(const int32 new_quantity)
{
	if(quantity != new_quantity )
	{ 
		quantity = FMath::Clamp(new_quantity, 0, is_stackable ? max_stack_size : 1);
		MarkDirtyForReplication();
	}
}

void UItemBase::Use(class ACharacterBase* player)
{

}

void UItemBase::AddedToInventory(class UInventoryComponent* inventory)
{

}

#undef LOCTEXT_NAMESPACE