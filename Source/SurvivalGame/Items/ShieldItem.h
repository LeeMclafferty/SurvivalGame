// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/EquippableItem.h"
#include "ShieldItem.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class SURVIVALGAME_API UShieldItem : public UEquippableItem
{
	GENERATED_BODY()

public:

	UShieldItem();

	virtual bool Equip(class ACharacterBase* player) override;
	virtual bool UnEquip(class ACharacterBase* player) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	TSubclassOf<class AShield> shield_class;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	class UStaticMesh* shieldMesh;
	
};
