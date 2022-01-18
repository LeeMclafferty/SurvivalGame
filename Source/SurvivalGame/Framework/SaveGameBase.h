// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Kismet/GameplayStatics.h"
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
		
		//Information
	UPROPERTY(VisibleAnywhere, Category = "Info")
	FString save_slot_name;

	UPROPERTY(VisibleAnywhere, Category = "Info")
	int32 player_index;

	UPROPERTY(VisibleAnywhere, Category = "Info")
	bool is_male;
		
		/// <summary>
		/// Current SkMesh
		/// </summary>
	UPROPERTY(VisibleAnywhere, Category = "Player Customization")
	USkeletalMesh* current_hair_mesh;

	UPROPERTY(VisibleAnywhere, Category = "Player Customization")
	USkeletalMesh* current_beard_mesh;

	UPROPERTY(VisibleAnywhere, Category = "Player Customization")
	USkeletalMesh* current_chest_mesh;

	UPROPERTY(VisibleAnywhere, Category = "Player Customization")
	USkeletalMesh* current_head_mesh;

	UPROPERTY(VisibleAnywhere, Category = "Player Customization")
	USkeletalMesh* current_legs_mesh;

	UPROPERTY(VisibleAnywhere, Category = "Player Customization")
	USkeletalMesh* current_boot_mesh;

	UPROPERTY(VisibleAnywhere, Category = "Player Customization")
	USkeletalMesh* current_belt_mesh;

	UPROPERTY(VisibleAnywhere, Category = "Player Customization")
	USkeletalMesh* current_brow_mesh;

		/// <summary>
		/// Current Materials
		/// </summary>
	UPROPERTY(VisibleAnywhere, Category = "Player Customization")
	TArray<UMaterialInterface*> current_hair_color;

	UPROPERTY(VisibleAnywhere, Category = "Player Customization")
	TArray<UMaterialInterface*> current_beard_color;

	UPROPERTY(VisibleAnywhere, Category = "Player Customization")
	TArray<UMaterialInterface*> current_head_materials;

	UPROPERTY(VisibleAnywhere, Category = "Player Customization")
	TArray<UMaterialInterface*> current_chest_materials;

	UPROPERTY(VisibleAnywhere, Category = "Player Customization")
	TArray<UMaterialInterface*> current_leg_materials;

		//male only
	UPROPERTY(VisibleAnywhere, Category = "Player Customization")
	UMaterialInterface* current_brow_material;	



	
};
