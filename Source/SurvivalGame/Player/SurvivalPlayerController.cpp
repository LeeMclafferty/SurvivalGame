// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SurvivalPlayerController.h"

ASurvivalPlayerController::ASurvivalPlayerController()
{

}

void ASurvivalPlayerController::ClientShowNotification_Implementation(const FText& message)
{
	ShowNotification(message);
}
