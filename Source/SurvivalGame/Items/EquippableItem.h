
#pragma once

#include "CoreMinimal.h"
#include "Items/ItemBase.h"
#include "EquippableItem.generated.h"

UENUM(BlueprintType)
enum class EEquippableSlot : uint8
{
	EIS_Head UMETA(DisplayName = "Head"),
	EIS_Ears UMETA(DisplayName = "Ears"),
	EIS_Hair UMETA(DisplayName = "Hair"),
	EIS_Brow UMETA(DisplayName = "Brow"),
	EIS_Beard UMETA(DisplayName = "Beard"),
	EIS_Chest UMETA(DisplayName = "Chest"),
	EIS_Bracer UMETA(DisplayName = "Bracer"),
	EIS_Back UMETA(DisplayName = "Back"),
	EIS_Hands UMETA(DisplayName = "Hands"),
	EIS_Weapon UMETA(DisplayName = "Weapon"),
	EIS_Shield UMETA(DisplayName = "Shield"),
	EIS_Shoes UMETA(DisplayName = "Shoes"),
	EIS_Belt UMETA(DisplayName = "Belt"),
	EIS_Legs UMETA(DisplayName = "Legs"),
	EIS_Calves UMETA(DisplayName = "Calves"),
	EIS_Throwable UMETA(DisplayName = "Throwable Item")
};

UCLASS(Abstract, NotBlueprintable)
class SURVIVALGAME_API UEquippableItem : public UItemBase
{
	GENERATED_BODY()

public:
	
	UEquippableItem();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Equippables")
	EEquippableSlot slot;

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty> & OutLifetimeProps) const override;

	virtual void Use(class ACharacterBase* player) override;

	UFUNCTION(BlueprintCallable, Category = "Equippables")
	virtual bool Equip(class ACharacterBase* player);

	UFUNCTION(BlueprintCallable, Category = "Equippable")
	virtual bool UnEquip(class ACharacterBase* player);

	virtual bool ShouldShowInventory() const override;

	UFUNCTION(BlueprintPure, Category = "Equippables")
	bool GetIsEquipped() { return is_equipped; }

	void SetIsEquipped(bool is_equipped_new);

protected:

	UPROPERTY(ReplicatedUsing = EquipStatusChanged)
	bool is_equipped;

	UFUNCTION()
	void EquipStatusChanged(); //Gets called on double click of item

	
};
