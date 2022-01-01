// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ShieldItem.h"

#include "Player/CharacterBase.h"
#include "Player/SurvivalPlayerController.h"

UShieldItem::UShieldItem()
{

}

bool UShieldItem::Equip(class ACharacterBase* player)
{
	bool is_equip_successsful = Super::Equip(player);

	if (is_equip_successsful && player)
	{
		player->EquipShield(this);
	}

	return is_equip_successsful;
}

bool UShieldItem::UnEquip(class ACharacterBase* player)
{
	bool is_unequip_successful = Super::UnEquip(player);

	if (is_unequip_successful && player)
	{
		player->UnequipShield();
	}

	return is_unequip_successful;
}