// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGameBase.generated.h"

/**
 * 
 */
USTRUCT()
struct FPlayerSaveData
{
	GENERATED_BODY()

	FString player_name = "default name";
	USkeletalMesh* player_hair;

};

UCLASS()
class SURVIVALGAME_API USaveGameBase : public USaveGame
{
	GENERATED_BODY()

public:

	USaveGameBase();

	FPlayerSaveData player_save_data;
	
	UPROPERTY(VisibleAnywhere, Category = "Basic")
	FString save_slot_name;

	UPROPERTY(VisibleAnywhere, Category = "Basic")
	int32 player_index;
		
		// Saving to a struct does not seem to work, but I am able to save to this variable. 
		// Player Customization.
	UPROPERTY(VisibleAnywhere, Category = "Player Customization")
	USkeletalMesh* current_hair_mesh;
	UPROPERTY(VisibleAnywhere, Category = "Player Customization")
	USkeletalMesh* current_beard_mesh;
	
};
