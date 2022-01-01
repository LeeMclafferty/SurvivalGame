// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/CharacterCreationController.h"

#include "Kismet/GameplayStatics.h"

#include "Framework/SurvivalGameInstance.h"
#include "Player/CharacterCreationDummy.h"

ACharacterCreationController::ACharacterCreationController()
{

}

void ACharacterCreationController::BeginPlay()
{
	game_instance = Cast<USurvivalGameInstance>(GetWorld()->GetGameInstance());

}
