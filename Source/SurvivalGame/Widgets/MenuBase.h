// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuBase.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALGAME_API UMenuBase : public UUserWidget
{
	GENERATED_BODY()
	

public:

	virtual void Setup();

protected:
	virtual bool Initialize() override;
};
