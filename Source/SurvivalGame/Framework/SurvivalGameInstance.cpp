// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/SurvivalGameInstance.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "Widgets/CharacterCreationWidget.h"

#include "Player/SurvivalPlayerController.h"
#include "Player/CharacterCreationDummy.h"



USurvivalGameInstance::USurvivalGameInstance()
{
	ConstructorHelpers::FClassFinder<UUserWidget> creation_widget_bp(TEXT("/Game/aa_Blueprints/Widgets/CharacterCreation/WBP_CreationScreen"));
	creation_menu_class = creation_widget_bp.Class;
}

void USurvivalGameInstance::Init()
{
	if (creation_menu_class != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found class: %s"), *creation_menu_class->GetName());
	}
}

void USurvivalGameInstance::LoadCreationMenu()
{
	if(ASurvivalPlayerController* player_controller = Cast<ASurvivalPlayerController>(UGameInstance::GetFirstLocalPlayerController()))
	{ 
		creation_menu = CreateWidget<UCharacterCreationWidget>(this, creation_menu_class);
		creation_menu->Setup();
		
	}
}
