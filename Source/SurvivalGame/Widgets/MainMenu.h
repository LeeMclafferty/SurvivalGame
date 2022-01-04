// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/MenuBase.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALGAME_API UMainMenu : public UMenuBase
{
	GENERATED_BODY()

	virtual bool Initialize() override;

public:

	

protected:
		// MainMenu
	UPROPERTY(meta = (BindWidget))
	class UButton* new_button;

	UPROPERTY(meta = (BindWidget))
	class UButton* continue_button;

	UPROPERTY(meta = (BindWidget))
	class UButton* settings_button;

	UPROPERTY(meta = (BindWidget))
	class UButton* quit_button;

	UPROPERTY(meta = (BindWidget))
	class UWidget* main_menu;	

		
		//Join Host Menu
	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* menu_switcher;

	UPROPERTY(meta = (BindWidget))
	class UButton* host_button;

	UPROPERTY(meta = (BindWidget))
	class UButton* join_button;

	UPROPERTY(meta = (BindWidget))
	class UButton* settings_button01;

	UPROPERTY(meta = (BindWidget))
	class UButton* back_button;

	UPROPERTY(meta = (BindWidget))
	class UWidget* join_host_menu;

		//quit check
	UPROPERTY(meta = (BindWidget))
	class UWidget* quit_menu;

	UPROPERTY(meta = (BindWidget))
	class UButton* quit_back_button;

	UPROPERTY(meta = (BindWidget))
	class UButton* exit_button;

private:

	UFUNCTION()
	void OnPressNewButton();

	UFUNCTION()
	void OnPressContinueButton();

	UFUNCTION()
	void OnPressSettingsButton();

	UFUNCTION()
	void OnPressQuitButton();

	UFUNCTION()
	void OnPressHostButton();

	UFUNCTION()
	void OnPressJoinButton();

	UFUNCTION()
	void OnPressBackButton();

	UFUNCTION()
	void OnPressQuitBackButton();

	UFUNCTION()
	void OnPressExitButton();

	void LoadCreationMenu();

};
