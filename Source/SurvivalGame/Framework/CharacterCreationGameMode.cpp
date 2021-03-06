// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/CharacterCreationGameMode.h"
#include "Kismet/GameplayStatics.h"

#include "World/CameraDirector.h"
#include "Player/CharacterCreationDummy.h"

ACharacterCreationGameMode::ACharacterCreationGameMode()
{
	ConstructorHelpers::FClassFinder<AActor> creation_dummy_bp(TEXT("/Game/aa_Blueprints/Actor/BP_CharacterCreationDummy"));
	creation_dummy_class = creation_dummy_bp.Class;

	is_new_game = true;
	is_hosting = false;
}

void ACharacterCreationGameMode::BeginPlay()
{
	
	 UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACameraDirector::StaticClass(), camera_directors);
	 camera_director = Cast<ACameraDirector>(camera_directors[0]);
	 camera_director->SnapToCameraOne();

	
		// Creating the params for Spawn dummy actor
	FVector location(22460.0f, 75910.0f, -39315.875f);
	FRotator rotation(-0.701221, 13.418568, 2.944208);
	FVector scale(1.f,1.f,1.f);
	FActorSpawnParameters spawn_params;
	spawn_params.bNoFail = true;
	spawn_params.Owner = this;


		// Set the spawned actor = to creation_dummy var so that I have a reference
	creation_dummy = GetWorld()->SpawnActor<ACharacterCreationDummy>(creation_dummy_class, FTransform(rotation, location, scale), spawn_params);
	creation_dummy->is_male = true;



}

