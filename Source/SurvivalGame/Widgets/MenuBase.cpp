// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/MenuBase.h"
#include "Player/SurvivalPlayerController.h"

bool UMenuBase::Initialize()
{
	bool success = Super::Initialize();

	return success;
}

void UMenuBase::Setup()
{
	this->AddToViewport();
	this->bIsFocusable = true;
	
	if(ASurvivalPlayerController* pc = Cast<ASurvivalPlayerController>(GetWorld()->GetFirstPlayerController())) 
	{
		FInputModeUIOnly input_data;
		input_data.SetWidgetToFocus(this->TakeWidget());
		pc->SetInputMode(input_data);
		pc->bShowMouseCursor = true;
	/*	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Yellow, FString::Printf(TEXT("Setup")));*/
	}
}
