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

		//New Character
	if (dummy != nullptr && save_instance != nullptr && gamemode != nullptr)
	{
		save_instance->current_hair_mesh = dummy->hair_mesh->SkeletalMesh;
		save_instance->current_beard_mesh = dummy->beard_mesh->SkeletalMesh;

		UGameplayStatics::SaveGameToSlot(save_instance, slot_name, 0);
	}
}


void ASurvivalPlayerController::LoadPlayerData()
{	
	if(ACharacterBase* pawn = Cast<ACharacterBase>(GetPawn()))
	{ 
		if (USaveGameBase* loaded_game = Cast<USaveGameBase>(UGameplayStatics::LoadGameFromSlot(slot_name, 0)))
		{
			pawn->hair_mesh->SetSkeletalMesh(loaded_game->current_hair_mesh);
			pawn->beard_mesh->SetSkeletalMesh(loaded_game->current_beard_mesh);
		}
	}
}

void ASurvivalPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//LoadPlayerData();
}
