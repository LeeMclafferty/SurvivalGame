// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveGameBase.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALGAME_API USaveGameBase : public USaveGame
{
	GENERATED_BODY()

public:

	USaveGameBase();

	UPROPERTY(VisibleAnywhere, Category = "Basic")
	FString save_name;
	
	UPROPERTY(VisibleAnywhere, Category = "Basic")
	TArray<class UItemBase*> player_items;

	UPROPERTY(VisibleAnywhere, Category = "Basic")
	FString player_name;

		
	
};
