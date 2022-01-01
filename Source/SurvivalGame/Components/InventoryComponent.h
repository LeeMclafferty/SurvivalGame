// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "Items/ItemBase.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

/* Needs to 
	1. Hold Items - TArray current_items (Then functions to manipulate them)
	2. Find Items
	3. Add Items
	4. Remove Items
*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated); // Bind in order to update UI 

UENUM(BlueprintType)
enum class EItemAddResult : uint8
{
	IAR_NoItemsAdded UMETA(DisplayName = "No items added"),
	IAR_SomeItemsAdded UMETA(DisplayName = "Some items added"),
	IAR_AllItemsAdded UMETA(DisplayName = "All items added")
};

USTRUCT(BlueprintType)
struct FItemAddResult
{

	GENERATED_BODY()
	
public:

	FItemAddResult() {};
	FItemAddResult(int32 in_item_quantity) : amount_to_give(in_item_quantity), actual_amount_given(0) {};
	FItemAddResult(int32 in_item_quantity, int32 in_quantity_added) : amount_to_give(in_item_quantity), actual_amount_given(in_quantity_added) {};

	UPROPERTY(BlueprintReadOnly, Category = "Item Add Result")
	int32 amount_to_give = 0;

	UPROPERTY(BlueprintReadOnly, Category = "Item Add Result")
	int32 actual_amount_given = 0;

	UPROPERTY(BlueprintReadOnly, Category = "Item Add Result")
	EItemAddResult result = EItemAddResult::IAR_NoItemsAdded;

	UPROPERTY(BlueprintReadOnly, Category = "Item Add Result")
	FText error_text = FText::GetEmpty();


	//Helper Functions - Constructs the result then returns it. 
	static FItemAddResult AddedNone(const int32 in_item_quantity, const FText& error_text)
	{
		FItemAddResult added_none_result(in_item_quantity);
		added_none_result.result = EItemAddResult::IAR_NoItemsAdded;
		added_none_result.error_text = error_text;

		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Yellow, FString::Printf(TEXT("AddedNone")));

		return added_none_result;
	}

	static FItemAddResult AddedSome(const int32 in_item_quantity, const int32 amount_given, const FText& error_text)
	{
		FItemAddResult added_some_result(in_item_quantity, amount_given);

		added_some_result.result = EItemAddResult::IAR_SomeItemsAdded;
		added_some_result.error_text = error_text;
		added_some_result.actual_amount_given = amount_given;

		// GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Yellow, FString::Printf(TEXT("AddedSome")));

		return added_some_result;
	}

	static FItemAddResult AddedAll(const int32 in_item_quantity)
	{
		FItemAddResult added_all_result(in_item_quantity);
		added_all_result.result = EItemAddResult::IAR_AllItemsAdded;
		added_all_result.actual_amount_given = in_item_quantity;

		// GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Yellow, FString::Printf(TEXT("AddedAll")));

		return added_all_result;
	}

};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVALGAME_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

	friend class UItemBase; //Gives UItemBase access to InventoryComponent private and protected members

public:	
	
	UInventoryComponent();

	UFUNCTION(BlueprintCallable, Category = "Item")
	FItemAddResult TryAddItem(class UItemBase* item); // Adds an already existing item to inventory

	UFUNCTION(BlueprintCallable, Category = "Item")
	FItemAddResult TryAddItemFromClass(TSubclassOf<class UItemBase> item_class, const int32 quantity); //Use to construct new instance of item

	int32 ConsumeItem(class UItemBase* item); // Consume all
	int32 ConsumeItem(class UItemBase* item, const int32 quantity); // Overload to consume a specified amount. 

	UFUNCTION(BlueprintPure, Category = "Inventory")
	FORCEINLINE TArray<class UItemBase*> GetItems() const { return current_items; }

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool RemoveItem(class UItemBase* item);

	UFUNCTION(BlueprintPure, Category = "Inventory")
	bool HasItem(TSubclassOf<UItemBase> item_class, const int32 quaintity = 1);

	UFUNCTION(BlueprintPure, Category = "Inventory")
	UItemBase* FindItem(class UItemBase* item) const;

	UFUNCTION(BlueprintPure, Category = "Inventory")
	UItemBase* FindItemByClass(TSubclassOf<class UItemBase> item_class) const; //Singular 

	UFUNCTION(BlueprintPure, Category = "Inventory")
	TArray<UItemBase*> FindItemsByClass(TSubclassOf<class UItemBase> item_class) const; //Plural

	UFUNCTION(BlueprintPure, Category = "Inventory")
	float GetCurrentWeight();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetWeightCapacity(const int32 new_capacity);

	UFUNCTION(BlueprintPure, Category = "Invetory")
	FORCEINLINE float GetWeightCapacity() const { return weight_capacity; }

	UFUNCTION(BlueprintPure, Category = "Invetory")
	FORCEINLINE int32 GetSlotCapacity() const { return slot_capacity; } 

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetSlotCapacity(const int32 new_capacity);

	UFUNCTION(Client, Reliable)
	void ClientRefreshInventory(); // UFUNCTION specifier Client means this will only run on the client and not on the server or the server will tell the client to run if being called on the server. 

	UPROPERTY(BlueprintAssignable, Category = Inventory)
	FOnInventoryUpdated OnInventoryUpdated;

protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(ReplicatedUsing = OnRep_Items, VisibleAnywhere, Category = "Inventory")
	TArray<class UItemBase*> current_items;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	float weight_capacity;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory", meta = (ClampMin = 0, ClampMax = 100))
	int32 slot_capacity;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual bool ReplicateSubobjects(class UActorChannel *Channel, class FOutBunch *Bunch, FReplicationFlags *RepFlags) override;

private:

	UItemBase* AddItem(class UItemBase* item); // This will replace current_items.Add() since it does not replicate. New function will replicate. 

	UFUNCTION()
	void OnRep_Items();

	UPROPERTY()
	int32 replicated_items_key; // Each item needs a rep key (in itembase.h) && the inventory itself. 

	FItemAddResult TryAddItem_Internal(class UItemBase* item); //Does most of the work for public adding functions. 

		
};
