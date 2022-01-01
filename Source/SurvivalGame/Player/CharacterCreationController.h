// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CharacterCreationController.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALGAME_API ACharacterCreationController : public APlayerController
{
	GENERATED_BODY()

	ACharacterCreationController();
	virtual void BeginPlay() override;

public:
	
	UPROPERTY(BlueprintReadWrite, Category = "References")
	class USurvivalGameInstance* game_instance;

	// Value set in BP
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "References")
	class ACharacterCreationDummy* creation_dummy;

	//male default meshes
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Male Defaults")
	class USkeletalMesh* male_head_default;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Male Defaults")
	class USkeletalMesh* male_brow_default;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Male Defaults")
	class USkeletalMesh* male_chest_default;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Male Defaults")
	class USkeletalMesh* male_legs_default;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Male Defaults")
	class USkeletalMesh* male_shoes_default;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Male Defaults")
	class USkeletalMesh* male_belt_default;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Male Defaults")
	class USkeletalMesh* male_hair_default;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Male Defaults")
	class USkeletalMesh* male_beard_default;

	//Female default meshes
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Male Defaults")
	class USkeletalMesh* female_head_default;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Male Defaults")
	class USkeletalMesh* female_brow_default;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Male Defaults")
	class USkeletalMesh* female_chest_default;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Male Defaults")
	class USkeletalMesh* female_legs_default;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Male Defaults")
	class USkeletalMesh* female_shoes_default;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Male Defaults")
	class USkeletalMesh* female_belt_default;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Male Defaults")
	class USkeletalMesh* female_hair_default;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Male Defaults")
	class USkeletalMesh* female_beard_default;

	
	
};
