

#include "Items/ConsumableItem.h"

#define LOCTEXT_NAMESPACE "ConsumableItem"

UConsumableItem::UConsumableItem()
{
	heal_amount = 20.f;
	use_action_text = LOCTEXT("ItemUseActionText", "Consume");
}

void UConsumableItem::Use(ACharacterBase* player)
{
	//Heal character here
}

#undef LOCTEXT_NAMESPACE