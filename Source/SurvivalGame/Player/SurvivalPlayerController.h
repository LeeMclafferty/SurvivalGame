// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SurvivalPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALGAME_API ASurvivalPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	ASurvivalPlayerController();
	
	UFUNCTION(Client, Reliable, BlueprintCallable)
	void ClientShowNotification(const FText& message); // Sever sends this message to the client.

	UFUNCTION(BlueprintImplementableEvent)
	void ShowNotification(const FText& message);

	UFUNCTION(BlueprintImplementableEvent)
	void ShowDeathScreen(class ACharacterBase* killer);

	UFUNCTION(BlueprintImplementableEvent)
	void ShowLootMenu(const class UInventoryComponent* loot_source);

	UFUNCTION(BlueprintImplementableEvent)
	void ShowInGameUI();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void HideLootMenu();

	UFUNCTION(BlueprintImplementableEvent)
	void OnHitPlayer();

protected:

private:
	
};
