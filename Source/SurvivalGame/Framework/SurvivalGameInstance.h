// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include <vector>
#include "SurvivalGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALGAME_API USurvivalGameInstance : public UGameInstance
{
	GENERATED_BODY()

	USurvivalGameInstance();
	virtual void Init();

public:

	UFUNCTION(BlueprintCallable, Category = "Menu Loading")
	void LoadCreationMenu();

		//Called on level bp of creation level. 
	UFUNCTION(BlueprintCallable, Category = "Menu Loading")
	void LoadGameMainMenu();

	UFUNCTION(Exec)
	void Host();

	UFUNCTION(Exec)
	void Join(FString ip);

private:

	UPROPERTY()
	TSubclassOf<class UUserWidget> creation_menu_class;

	UPROPERTY()
	class UCharacterCreationWidget* creation_menu;

	UPROPERTY()
	TSubclassOf<class UUserWidget> main_menu_class;

	UPROPERTY()
	class UMainMenu* main_menu;

public:

	class USkeletalMesh* male_head;
	class USkeletalMesh* female_head;
	class USkeletalMesh* male_peasant_belt;
	class USkeletalMesh* female_peasant_belt;
	class USkeletalMesh* male_peasant_boots;
	class USkeletalMesh* female_peasant_boots;
	class USkeletalMesh* male_brows;
	class USkeletalMesh* female_empty;
	class USkeletalMesh* male_empty;
	class USkeletalMesh* male_peasant_chest_sk;
	class USkeletalMesh* male_peasant_legs_sk;
	class USkeletalMesh* female_peasant_chest_sk;
	class USkeletalMesh* female_peasant_legs_sk;



	//Hair
	class USkeletalMesh* male_hair_01;
	class USkeletalMesh* male_hair_02;
	class USkeletalMesh* male_hair_03;
	class USkeletalMesh* male_hair_04;
	class USkeletalMesh* male_hair_05;
	std::vector<USkeletalMesh*> male_hairstyles;

	class USkeletalMesh* female_hair_01;
	class USkeletalMesh* female_hair_02;
	class USkeletalMesh* female_hair_03;
	class USkeletalMesh* female_hair_04;
	class USkeletalMesh* female_hair_05;
	class USkeletalMesh* female_hair_06;
	class USkeletalMesh* female_hair_07;
	class USkeletalMesh* female_hair_08;
	std::vector<USkeletalMesh*> female_hairstyles;

	//Beards
	class USkeletalMesh* beard_01;
	class USkeletalMesh* beard_02;
	class USkeletalMesh* beard_03;
	class USkeletalMesh* beard_04;
	class USkeletalMesh* beard_05;
	std::vector<USkeletalMesh*> beards;

	//Hair Color 1
	UPROPERTY(EditDefaultsOnly, Category = "Hair Color")
		class UMaterialInterface* blackhair_01;
	UPROPERTY(EditDefaultsOnly, Category = "Hair Color")
		class UMaterialInterface* blondehair_01;
	UPROPERTY(EditDefaultsOnly, Category = "Hair Color")
		class UMaterialInterface* brownhair_01;
	UPROPERTY(EditDefaultsOnly, Category = "Hair Color")
		class UMaterialInterface* greyhair_01;
	UPROPERTY(EditDefaultsOnly, Category = "Hair Color")
		class UMaterialInterface* redhair_01;

	//hair Color 2
	UPROPERTY(EditDefaultsOnly, Category = "Hair Color")
		class UMaterialInterface* blackhair_02;
	UPROPERTY(EditDefaultsOnly, Category = "Hair Color")
		class UMaterialInterface* blondehair_02;
	UPROPERTY(EditDefaultsOnly, Category = "Hair Color")
		class UMaterialInterface* brownhair_02;
	UPROPERTY(EditDefaultsOnly, Category = "Hair Color")
		class UMaterialInterface* greyhair_02;
	UPROPERTY(EditDefaultsOnly, Category = "Hair Color")
		class UMaterialInterface* redhair_02;

	UPROPERTY(EditDefaultsOnly, Category = "Hair Color")
		class UMaterialInterface* hair_tie;
	UPROPERTY(EditDefaultsOnly, Category = "Hair Color")
		class UMaterialInterface* brow_color;

	//Beard Color
	UPROPERTY(EditDefaultsOnly, Category = "Beard Colors")
		class UMaterialInterface* beard_black;
	UPROPERTY(EditDefaultsOnly, Category = "Beard Colors")
		class UMaterialInterface* beard_blonde;
	UPROPERTY(EditDefaultsOnly, Category = "Beard Colors")
		class UMaterialInterface* beard_brown;
	UPROPERTY(EditDefaultsOnly, Category = "Beard Colors")
		class UMaterialInterface* beard_grey;
	UPROPERTY(EditDefaultsOnly, Category = "Beard Colors")
		class UMaterialInterface* beard_red;

	//Eye colors
	UPROPERTY(EditDefaultsOnly, Category = "Eye Colors")
		class UMaterialInterface* brown_eyes;
	UPROPERTY(EditDefaultsOnly, Category = "Eye Colors")
		class UMaterialInterface* blue_eyes;
	UPROPERTY(EditDefaultsOnly, Category = "Eye Colors")
		class UMaterialInterface* green_eyes;
	UPROPERTY(EditDefaultsOnly, Category = "Eye Colors")
		class UMaterialInterface* purple_eyes;

	//Skin Tones
	UPROPERTY(EditDefaultsOnly, Category = "Skine Tones")
		class UMaterialInterface* skintone_01;
	UPROPERTY(EditDefaultsOnly, Category = "Skine Tones")
		class UMaterialInterface* skintone_02;
	UPROPERTY(EditDefaultsOnly, Category = "Skine Tones")
		class UMaterialInterface* skintone_03;
	UPROPERTY(EditDefaultsOnly, Category = "Skine Tones")
		class UMaterialInterface* skintone_04;
	UPROPERTY(EditDefaultsOnly, Category = "Skine Tones")
		class UMaterialInterface* skintone_05;

	//Peasant Materials for skin tones
	//Male 
	UPROPERTY(EditDefaultsOnly, Category = "Skine Tones")
		class UMaterialInterface* male_peasant_set_01;
	UPROPERTY(EditDefaultsOnly, Category = "Skine Tones")
		class UMaterialInterface* male_peasant_set_02;
	UPROPERTY(EditDefaultsOnly, Category = "Skine Tones")
		class UMaterialInterface* male_peasant_set_03;
	UPROPERTY(EditDefaultsOnly, Category = "Skine Tones")
		class UMaterialInterface* male_peasant_set_04;
	UPROPERTY(EditDefaultsOnly, Category = "Skine Tones")
		class UMaterialInterface* male_peasant_set_05;

	UPROPERTY(EditDefaultsOnly, Category = "Skine Tones")
		class UMaterialInterface* female_peasant_set_01;
	UPROPERTY(EditDefaultsOnly, Category = "Skine Tones")
		class UMaterialInterface* female_peasant_set_02;
	UPROPERTY(EditDefaultsOnly, Category = "Skine Tones")
		class UMaterialInterface* female_peasant_set_03;
	UPROPERTY(EditDefaultsOnly, Category = "Skine Tones")
		class UMaterialInterface* female_peasant_set_04;
	UPROPERTY(EditDefaultsOnly, Category = "Skine Tones")
		class UMaterialInterface* female_peasant_set_05;


protected:

	void ConstuctAllAssetReferences();

};

