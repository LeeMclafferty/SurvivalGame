// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include <vector>
#include "CharacterCreationGameMode.generated.h"


/**
 * 
 */
UCLASS()
class SURVIVALGAME_API ACharacterCreationGameMode : public AGameModeBase
{
	GENERATED_BODY()

	ACharacterCreationGameMode();

public:
	UFUNCTION(BlueprintCallable, Category = "Dummy")
	class ACharacterCreationDummy* GetCreationDummy() { return creation_dummy; }

	class ACameraDirector* GetCameraDirector() { return camera_director; }

	//Idle animations
	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	class UAnimationAsset* male_idle;

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	class UAnimationAsset* female_idle;

	UPROPERTY()
	bool is_new_game;

protected:

	virtual void BeginPlay() override;

	//std::vector<ACameraDirector*> camera_directors;
	class ACameraDirector* camera_director;
	TSubclassOf<ACameraDirector> camera_director_class;
	TArray<AActor*> camera_directors;

private:

	UPROPERTY()
	TSubclassOf<class ACharacterCreationDummy> creation_dummy_class;

	UPROPERTY()
	class ACharacterCreationDummy* creation_dummy;

	
};
