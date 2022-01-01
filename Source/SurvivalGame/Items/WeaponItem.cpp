// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/WeaponItem.h"
#include "Player/CharacterBase.h"
#include "Player/SurvivalPlayerController.h"

UWeaponItem::UWeaponItem()
{
}

bool UWeaponItem::Equip(class ACharacterBase* player)
{
	bool is_equip_successsful = Super::Equip(player);

	if (is_equip_successsful && player)
	{
		player->EquipWeapon(this);
	}

	return is_equip_successsful;
}

bool UWeaponItem::UnEquip(class ACharacterBase* player)
{
	bool is_unequip_successful = Super::UnEquip(player);

	if (is_unequip_successful && player)
	{
		player->UnequipWeapon();
	}

	return is_unequip_successful;
}

