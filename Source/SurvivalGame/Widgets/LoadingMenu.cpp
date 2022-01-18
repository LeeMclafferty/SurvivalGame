// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/LoadingMenu.h"

#include "Player/SurvivalPlayerController.h"

bool ULoadingMenu::Initialize()
{
	bool succsess = Super::Initialize();


	return succsess;
}

void ULoadingMenu::Setup()
{	
	this->AddToViewport();
	this->bIsFocusable = true;

	if (ASurvivalPlayerController* pc = Cast<ASurvivalPlayerController>(GetWorld()->GetFirstPlayerController()))
	{
		FInputModeUIOnly input_data;
		input_data.SetWidgetToFocus(this->TakeWidget());
		pc->SetInputMode(input_data);
		pc->bShowMouseCursor = false;
	}
}
