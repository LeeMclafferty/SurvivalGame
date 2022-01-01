// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
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

private:

	UPROPERTY()
	TSubclassOf<class UUserWidget> creation_menu_class;

	UPROPERTY()
	class UCharacterCreationWidget* creation_menu;


};
