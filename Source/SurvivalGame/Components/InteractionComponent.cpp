// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InteractionComponent.h"

#include "Components/PrimitiveComponent.h"
#include "Player/CharacterBase.h"
#include "Widgets/InteractionWidget.h"

UInteractionComponent::UInteractionComponent()
{
	SetComponentTickEnabled(false);

	interaction_time = 0.f;
	interaction_distance = 200.f;
	interactable_name_text = FText::FromString("Interactable Object");
	interactable_action_text = FText::FromString("Interact");
	allow_multiple_interactors = true;

	Space = EWidgetSpace::Screen;
	DrawSize = FIntPoint(400, 100);
	bDrawAtDesiredSize = true;

	SetActive(true);
	SetHiddenInGame(true);

}

void UInteractionComponent::BeginFocus(class ACharacterBase* player)
{
	if(!IsActive() || !GetOwner() || !player)
	{ 
		return;
	}

	on_begin_focus.Broadcast(player);

	if (GetNetMode() != NM_DedicatedServer) //if not the server
	{
		SetHiddenInGame(false);

		for (auto& visual_component : GetOwner()->GetComponentsByClass(UPrimitiveComponent::StaticClass())) // Get any visual components (called primative components by UE)
		{
			if(UPrimitiveComponent* primative = Cast<UPrimitiveComponent>(visual_component))
			{
				primative->SetRenderCustomDepth(true); // Enable outline around the object player is looking at
			}
		}
	}

	RefreshWidget();
}

void UInteractionComponent::EndFocus(class ACharacterBase* player)
{
	on_end_focus.Broadcast(player);

	

	if (GetNetMode() != NM_DedicatedServer) //if not the server
	{
		SetHiddenInGame(true);

		for (auto& visual_component : GetOwner()->GetComponentsByClass(UPrimitiveComponent::StaticClass())) // Get any visual components (called primative components by UE)
		{
			if (UPrimitiveComponent* primative = Cast<UPrimitiveComponent>(visual_component))
			{
				primative->SetRenderCustomDepth(false); // Disable outline around the object player is looking at
			}
		}
	}
}

void UInteractionComponent::BeginInteraction(ACharacterBase* player)
{
	if (CanInteract(player))
	{
		interacting_players.Add(player);
		on_begin_interaction.Broadcast(player);
	}
}

void UInteractionComponent::EndInteraction(ACharacterBase* player)
{
	interacting_players.Remove(player);
	on_end_interaction.Broadcast(player);
}

void UInteractionComponent::Interact(class ACharacterBase* player)
{
	on_interact.Broadcast(player);
}

float UInteractionComponent::GetInteractionPercentage()
{
	if (interacting_players.IsValidIndex(0))
	{
		if (ACharacterBase* interactor = interacting_players[0])
		{
			if (interactor && interactor->IsInteracting())
			{
				return 1.f - FMath::Abs(interactor->GetRemainingInteractTime() / interaction_time);
			}
		}
	}
	return 0;
}

void UInteractionComponent::SetInteractableNameText(const FText& new_name_text)
{
	interactable_name_text = new_name_text;
	RefreshWidget();
}

void UInteractionComponent::SetInteractableActionText(const FText& new_action_text)
{
	interactable_action_text = new_action_text;
	RefreshWidget();
}

void UInteractionComponent::RefreshWidget()
{
	//if (!bHiddenInGame || GetOwner()->GetNetMode() != NM_DedicatedServer)

		if (UInteractionWidget* interaction_widget = Cast<UInteractionWidget>(GetUserWidgetObject()))
		{
			interaction_widget->UpdateInteractionWidget(this);
			// GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Yellow, FString::Printf(TEXT("Hit interaction comp")));
		}
}

void UInteractionComponent::Deactivate()
{
	Super::Deactivate();

	for (int32 i = interacting_players.Num() - 1; i >= 0; --i)
	{
		if (ACharacterBase* player = interacting_players[i])
		{
			EndFocus(player);
			EndInteraction(player);
		}
	}

	interacting_players.Empty();
}

bool UInteractionComponent::CanInteract(class ACharacterBase* player)
{
	const bool player_already_interacting = !allow_multiple_interactors && interacting_players.Num() >= 1;

	return !player_already_interacting && IsActive() && GetOwner() != nullptr && player != nullptr;
}
