// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnItemModified); //Delegate to bind UI changes in BPs

UENUM(BlueprintType)
enum class EItemRarity : uint8
{
	IR_Common UMETA(DisplayName = "Common"),
	IR_Uncommon UMETA(DisplayName = "Uncommon"),
	IR_Rare UMETA(DisplayName = "Rare"),
	IR_Mythic UMETA(DisplayName = "Mythic"),
	IR_Legendary UMETA(DisplayName = "Legendary"),

};

UCLASS(Abstract, Blueprintable, EditInlineNew, DefaultToInstanced)
class SURVIVALGAME_API UItemBase : public UObject
{
	GENERATED_BODY()

public:

	UItemBase();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	FText item_display_name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (MultiLine = true))
	FText item_description;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	FText  use_action_text;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	class UTexture2D* item_thumbnail;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	class UStaticMesh*  pickup_mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (ClampMin = 0.0))
	EItemRarity rarity;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (ClampMin = 0.0))
	float weight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	bool is_stackable;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (ClampMin = 2, EditCondition = is_stackable))
	int32 max_stack_size;
	 
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	TSubclassOf<class UItemToolTip> item_tool_tip;

	UPROPERTY()
	class UInventoryComponent* owning_inventory;

	UPROPERTY()
	int32 rep_key; //Tracking changes on the server (I don't fully understand this but apparently I need it on UObjects so we are winging it. )

	UPROPERTY(BlueprintAssignable)
	FOnItemModified OnItemModified;

	UFUNCTION(BlueprintCallable, Category = "Item")
	FORCEINLINE float GetStackWeight() const { return quantity * weight; }

	UFUNCTION(BlueprintPure, Category = "Item")
	virtual bool ShouldShowInventory() const;

	void MarkDirtyForReplication(); // Mark the object as needing replication. You have to call after modifying replicated properties on UObject.

	UFUNCTION()
	void OnRep_Quantity();

	UFUNCTION(BlueprintCallable, Category = "Item")
	void SetQuantity(const int32 new_quantity);

	UFUNCTION(BlueprintCallable, Category = "Item")
	int32 GetQuantity() { return quantity; }

	virtual void Use(class ACharacterBase* player);
	virtual void AddedToInventory(class UInventoryComponent* inventory);

protected:

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override; //Set up all replicated values
	virtual bool IsSupportedForNetworking() const override; //Tells UE to network this UObject since they are not networked by default. 

#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	UPROPERTY(ReplicatedUsing = OnRep_Quantity, EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (EditCondition = is_stackable))
	int32 quantity;

private:
};
