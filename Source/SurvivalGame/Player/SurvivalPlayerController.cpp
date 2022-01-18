// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SurvivalPlayerController.h"

#include "Framework/CharacterCreationGameMode.h"
#include "Framework/SurvivalGameInstance.h"
#include "Player/CharacterCreationDummy.h"
#include "Framework/SaveGameBase.h"
#include "Player/CharacterBase.h"

ASurvivalPlayerController::ASurvivalPlayerController()
{

}

void ASurvivalPlayerController::ClientShowNotification_Implementation(const FText& message)
{
	ShowNotification(message);
}

void ASurvivalPlayerController::SaveNewCharacterData()
{
	ACharacterCreationGameMode* gamemode = Cast<ACharacterCreationGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	ACharacterCreationDummy* dummy = gamemode->GetCreationDummy();
	USaveGameBase* save_instance = Cast<USaveGameBase>(UGameplayStatics::CreateSaveGameObject(USaveGameBase::StaticClass()));
	USurvivalGameInstance* game_instance = Cast<USurvivalGameInstance>(GetWorld()->GetGameInstance());

		// I have to make a separate save for new game since I will be retrieving information from the dummy instead of the pawn. 
	if (dummy != nullptr && save_instance != nullptr && gamemode != nullptr)
	{

		save_instance->is_male = dummy->is_male;

			//SkMesh
		save_instance->current_hair_mesh = dummy->hair_mesh->SkeletalMesh;
		save_instance->current_beard_mesh = dummy->beard_mesh->SkeletalMesh;
		save_instance->current_head_mesh = dummy->head_mesh->SkeletalMesh;
		save_instance->current_chest_mesh = dummy->chest_mesh->SkeletalMesh;
		save_instance->current_legs_mesh = dummy->legs_mesh->SkeletalMesh;
		save_instance->current_belt_mesh = dummy->belt_mesh->SkeletalMesh;
		save_instance->current_boot_mesh = dummy->shoes_mesh->SkeletalMesh;
		save_instance->current_brow_mesh = dummy->brow_mesh->SkeletalMesh;

			//SetMaterials
		save_instance->current_hair_color = dummy->hair_mesh->GetMaterials();
		save_instance->current_beard_color = dummy->beard_mesh->GetMaterials();
		save_instance->current_head_materials = dummy->head_mesh->GetMaterials();
		save_instance->current_leg_materials = dummy->legs_mesh->GetMaterials();
		save_instance->current_chest_materials = dummy->chest_mesh->GetMaterials();
		save_instance->current_brow_material = dummy->brow_mesh->GetMaterial(0);

		UGameplayStatics::SaveGameToSlot(save_instance, slot_name, 0);
	}
}


void ASurvivalPlayerController::LoadPlayerData()
{	
	if(ACharacterBase* pawn = Cast<ACharacterBase>(GetPawn()))
	{ 
		if (USaveGameBase* loaded_game = Cast<USaveGameBase>(UGameplayStatics::LoadGameFromSlot(slot_name, 0)))
		{

			pawn->is_male = loaded_game->is_male;

				//Skeletal Mesh
			pawn->hair_mesh->SetSkeletalMesh(loaded_game->current_hair_mesh);
			pawn->beard_mesh->SetSkeletalMesh(loaded_game->current_beard_mesh);
			pawn->GetMesh()->SetSkeletalMesh(loaded_game->current_head_mesh);
			pawn->legs_mesh->SetSkeletalMesh(loaded_game->current_legs_mesh);
			pawn->chest_mesh->SetSkeletalMesh(loaded_game->current_chest_mesh);
			pawn->belt_mesh->SetSkeletalMesh(loaded_game->current_belt_mesh);
			pawn->shoes_mesh->SetSkeletalMesh(loaded_game->current_boot_mesh);
			pawn->brow_mesh->SetSkeletalMesh(loaded_game->current_brow_mesh);

				//Materials
			for (int32 i = 0; i < pawn->hair_mesh->GetMaterials().Num(); i++)
				pawn->hair_mesh->SetMaterial(i, loaded_game->current_hair_color[i]);

			for (int32 i = 0; i < pawn->beard_mesh->GetMaterials().Num(); i++)
				pawn->beard_mesh->SetMaterial(i, loaded_game->current_beard_color[i]); 

			for (int32 i = 0; i < pawn->GetMesh()->GetMaterials().Num(); i++)
				pawn->GetMesh()->SetMaterial(i, loaded_game->current_head_materials[i]);

			for (int32 i = 0; i < pawn->legs_mesh->GetMaterials().Num(); i++)
				pawn->legs_mesh->SetMaterial(i, loaded_game->current_leg_materials[i]);

			for (int32 i = 0; i < pawn->chest_mesh->GetMaterials().Num(); i++)
				pawn->chest_mesh->SetMaterial(i, loaded_game->current_chest_materials[i]);

			pawn->brow_mesh->SetMaterial(0, loaded_game->current_brow_material);
		
		}	 
	}
}

void ASurvivalPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//LoadPlayerData();
}
