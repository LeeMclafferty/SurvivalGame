// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/MenuBase.h"
#include "LoadingMenu.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALGAME_API ULoadingMenu : public UMenuBase
{
	GENERATED_BODY()
	
	virtual bool Initialize() override;

	public:

	virtual void Setup() override;

};
