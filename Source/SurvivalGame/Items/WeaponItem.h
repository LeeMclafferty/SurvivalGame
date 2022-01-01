// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/EquippableItem.h"
#include "WeaponItem.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class SURVIVALGAME_API UWeaponItem : public UEquippableItem
{
	GENERATED_BODY()

public:

	UWeaponItem();

	virtual bool Equip(class ACharacterBase* player) override;
	virtual bool UnEquip(class ACharacterBase* player) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	TSubclassOf<class AWeapon> weapon_class;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	class UStaticMesh* weapon_mesh;

};
