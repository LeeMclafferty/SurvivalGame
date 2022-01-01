// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractionWidget.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALGAME_API UInteractionWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintCallable, Category = "Ineraction")
	void UpdateInteractionWidget(class UInteractionComponent* interaction_component);

	UFUNCTION(BlueprintImplementableEvent)
	void OnUpdateInteractionWidget();

	UPROPERTY(BlueprintReadOnly, Category = "Interaction", meta = (ExposeOnSpawn))
	class UInteractionComponent* owning_interaction_component;
};
