

#include "Items/EquippableItem.h"
#include "Net/UnrealNetwork.h"
#include "Player/CharacterBase.h"
#include "Components/InventoryComponent.h"

#define  LOCTEXT_NAMESPACE "EquippableItem"

UEquippableItem::UEquippableItem()
{
	is_stackable = false;
	is_equipped = false;
	use_action_text = LOCTEXT("ItemUseActionText", "Equip");
}

void UEquippableItem::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UEquippableItem, is_equipped);
}

void UEquippableItem::Use(class ACharacterBase* player)
{
	if (player && player->HasAuthority())
	{
		if (player->GetEquippedItems().Contains(slot) && !is_equipped)
		{
			UEquippableItem* already_equipped_item = *player->GetEquippedItems().Find(slot);

			already_equipped_item->SetIsEquipped(false);
		}

		SetIsEquipped(!GetIsEquipped());
	}
}

bool UEquippableItem::Equip(class ACharacterBase* player)
{
	if (player)
	{
		return player->EquipItem(this);
	}
	return false;

}

bool UEquippableItem::UnEquip(class ACharacterBase* player)
{
	if (player)
	{
		return player->UnEquipItem(this);
	}
	return false;

}

bool UEquippableItem::ShouldShowInventory() const
{
	return !is_equipped;
}

void UEquippableItem::SetIsEquipped(bool is_equipped_new)
{
	is_equipped = is_equipped_new;
	EquipStatusChanged();
	MarkDirtyForReplication();
}

void UEquippableItem::EquipStatusChanged()
{
	if (ACharacterBase* player = Cast<ACharacterBase>(GetOuter()))
	{
		if (is_equipped)
		{
			Equip(player);
		}
		else
		{
			UnEquip(player);
		}
	}

	OnItemModified.Broadcast();
}

#undef LOCTEXT_NAMESPACE