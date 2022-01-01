// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Items/ItemBase.h"
#include "InventoryItemWidget.generated.h"


UCLASS()
class SURVIVALGAME_API UInventoryItemWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadOnly, Category = "Inventory Item Widget", meta = (ExposeOnSpawn = true)) //Expose on spawn creates an input pin when called in BPs
	class UItemBase* item;
};
