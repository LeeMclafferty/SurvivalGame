// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "InteractionComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBeginInteraction, class ACharacterBase*, Character);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEndInteraction, class ACharacterBase*, Character);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBeginFocus, class ACharacterBase*, Character);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEndFocus, class ACharacterBase*, Character);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteract, class ACharacterBase*, Character);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SURVIVALGAME_API UInteractionComponent : public UWidgetComponent
{
	GENERATED_BODY()
	
public:
	UInteractionComponent();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
	float interaction_time;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
	float interaction_distance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction") //Name that will come up when player looks at interactable
	FText interactable_name_text;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction") //Describes how the player will interact with interactable. ("Eat" for food, "Loot" for chest, ect. )
	FText interactable_action_text;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
	bool allow_multiple_interactors;

	UPROPERTY(EditDefaultsOnly, BlueprintAssignable)
	FOnBeginInteraction on_begin_interaction;

	UPROPERTY(EditDefaultsOnly, BlueprintAssignable)
	FOnEndInteraction on_end_interaction;

	UPROPERTY(EditDefaultsOnly, BlueprintAssignable)
	FOnBeginFocus on_begin_focus;

	UPROPERTY(EditDefaultsOnly, BlueprintAssignable)
	FOnEndFocus on_end_focus;

	UPROPERTY(EditDefaultsOnly, BlueprintAssignable)
	FOnInteract on_interact;

	void BeginFocus(class ACharacterBase* player); // when you start looking at interactable
	void EndFocus(class ACharacterBase* player); //// when you stop looking at interactable

	void BeginInteraction(ACharacterBase* player); // Call on press "E"
	void EndInteraction(ACharacterBase* player); // call on release "E"

	void Interact(class ACharacterBase* player); // Do the interaction

	UFUNCTION(BlueprintPure, Category = "Interaction")
	float GetInteractionPercentage();

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void SetInteractableNameText(const FText& new_name_text);

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void SetInteractableActionText(const FText& new_action_text);
	 
	void RefreshWidget(); // UI does not auto update, so you have to call a function to do it

protected:

	void Deactivate();

	bool CanInteract(class ACharacterBase* player);

	UPROPERTY()
	TArray<class ACharacterBase*> interacting_players; // Array of everyone looking at an interactable. 


private:

};