// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/InteractionWidget.h"
#include "Components/InteractionComponent.h"

void UInteractionWidget::UpdateInteractionWidget(class UInteractionComponent* interaction_component)
{	
	owning_interaction_component = interaction_component;
	OnUpdateInteractionWidget();

}
