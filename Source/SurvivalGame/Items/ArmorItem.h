
#pragma once

#include "CoreMinimal.h"
#include "Items/EquippableItem.h"
#include "ArmorItem.generated.h"


UCLASS(Blueprintable)
class SURVIVALGAME_API UArmorItem : public UEquippableItem
{
	GENERATED_BODY()

public:

	UArmorItem();

	
	virtual bool Equip(class ACharacterBase* player) override;
	virtual bool UnEquip(class ACharacterBase* player) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Armor")
	class USkeletalMesh* skeletal_mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Armor")
	class UStaticMesh* static_mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Armor")
	class UMaterialInstance* material_instance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Armor", meta = (ClampMin = 0.0, ClampMax = 1.0))
	float armor_value;
};
