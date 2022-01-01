// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ArmorItem.h"
#include "Player/CharacterBase.h"

UArmorItem::UArmorItem()
{
	
	armor_value = 0.05f;

}

bool UArmorItem::Equip(class ACharacterBase* player)
{
	bool is_equip_successful = Super::Equip(player);

	if (is_equip_successful && player)
	{
		player->EquipArmor(this);
	}

	return is_equip_successful;
}

bool UArmorItem::UnEquip(class ACharacterBase* player)
{
	bool is_unequip_successful = Super::UnEquip(player);

	if (is_unequip_successful && player)
	{
		player->UnequipArmor(slot);
	}

	return is_unequip_successful;
}
