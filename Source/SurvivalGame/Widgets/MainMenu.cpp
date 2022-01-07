
#include "Widgets/MainMenu.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/WidgetSwitcher.h"
#include "TimerManager.h"
#include "Components/EditableTextBox.h"

#include "Player/SurvivalPlayerController.h"
#include "Framework/CharacterCreationGameMode.h"
#include "World/CameraDirector.h"
#include "Framework/SurvivalGameInstance.h"

bool UMainMenu::Initialize()
{
	bool succsess = Super::Initialize();

	if (new_button)
	{
		new_button->OnPressed.AddDynamic(this, &UMainMenu::OnPressNewButton);
	}
	if (continue_button)
	{
		continue_button->OnPressed.AddDynamic(this, &UMainMenu::OnPressContinueButton);
	}
	if (settings_button)
	{
		settings_button->OnPressed.AddDynamic(this, &UMainMenu::OnPressSettingsButton);
	}
	if (quit_button)
	{
		quit_button->OnPressed.AddDynamic(this, &UMainMenu::OnPressQuitButton);
	}
	if (host_button)
	{
		host_button->OnPressed.AddDynamic(this, &UMainMenu::OnPressHostButton);
	}
	if(join_button)
	{
		join_button->OnPressed.AddDynamic(this, &UMainMenu::OnPressJoinButton);
	}
	if (back_button)
	{
		back_button->OnPressed.AddDynamic(this, &UMainMenu::OnPressBackButton);
	}
	if (quit_back_button)
	{
		quit_back_button->OnPressed.AddDynamic(this, &UMainMenu::OnPressQuitBackButton);
	}
	if (exit_button)
	{
		exit_button->OnPressed.AddDynamic(this, &UMainMenu::OnPressExitButton);
	}
	if (join_ip_button != nullptr)
	{
		join_ip_button->OnPressed.AddDynamic(this, &UMainMenu::OnPressJoinIpButton);
	}

	return succsess;
}

void UMainMenu::OnPressNewButton()
{
	ACharacterCreationGameMode* gamemode = Cast<ACharacterCreationGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	gamemode->is_new_game = true;

	menu_switcher->SetActiveWidget(join_host_menu);
}

void UMainMenu::OnPressContinueButton()
{
	ACharacterCreationGameMode* gamemode = Cast<ACharacterCreationGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	gamemode->is_new_game = false;
	menu_switcher->SetActiveWidget(join_host_menu);
}

void UMainMenu::OnPressSettingsButton()
{
	//Still need to make the settings menu
}

void UMainMenu::OnPressQuitButton()
{
	menu_switcher->SetActiveWidget(quit_menu);
}

void UMainMenu::OnPressHostButton()
{
	ACharacterCreationGameMode* gamemode = Cast<ACharacterCreationGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if(gamemode != nullptr)
	{ 
		gamemode->is_hosting = true;

		if (gamemode->is_new_game)
		{
			//Show session options
			gamemode->GetCameraDirector()->SetViewToCameraTwo();
			this->RemoveFromParent();

			FTimerHandle timerhandle;
			GetWorld()->GetTimerManager().SetTimer(timerhandle, this, &UMainMenu::LoadCreationMenu, gamemode->GetCameraDirector()->smooth_blend_time, false);
		}
		if (!gamemode->is_new_game)
		{
			//Show existing characters to load
		}
	}
}

void UMainMenu::OnPressJoinButton()
{
	ACharacterCreationGameMode* gamemode = Cast<ACharacterCreationGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (gamemode != nullptr)
	{
		gamemode->is_hosting = false;
		menu_switcher->SetActiveWidget(ip_menu);
	}

	
}

void UMainMenu::OnPressBackButton()
{
	ACharacterCreationGameMode* gamemode = Cast<ACharacterCreationGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	gamemode->is_new_game = true;
	gamemode->is_hosting = false;

	menu_switcher->SetActiveWidget(main_menu);

}

void UMainMenu::OnPressQuitBackButton()
{
	OnPressBackButton();
}

void UMainMenu::OnPressExitButton()
{
	ASurvivalPlayerController* player_controller = Cast<ASurvivalPlayerController>(GetWorld()->GetFirstLocalPlayerFromController());
	UKismetSystemLibrary::QuitGame(GetWorld(), player_controller, EQuitPreference::Quit, false);
}

void UMainMenu::LoadCreationMenu()
{
		// just used to call Load creation menu inside of a delay
		USurvivalGameInstance* game_instance = Cast<USurvivalGameInstance>(GetGameInstance());
		game_instance->LoadCreationMenu();
}

void UMainMenu::OnPressJoinIpButton()
{
	ACharacterCreationGameMode* gamemode = Cast<ACharacterCreationGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if(gamemode != nullptr)
	{ 
		gamemode->is_hosting = false;
		gamemode->SetEnteredIP(ip_field_text->GetText().ToString());
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Yellow, FString::Printf(TEXT("Entered IP: %s"), *gamemode->GetEnteredIP()));
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Yellow, FString::Printf(TEXT("Is Hosting: %i"), gamemode->is_hosting));

		if (gamemode->is_new_game)
		{
			//create new character
			gamemode->GetCameraDirector()->SetViewToCameraTwo();
			this->RemoveFromParent();

			FTimerHandle timerhandle;
			GetWorld()->GetTimerManager().SetTimer(timerhandle, this, &UMainMenu::LoadCreationMenu, gamemode->GetCameraDirector()->smooth_blend_time, false);

		}

		if (!gamemode->is_new_game)
		{
			//Show existing characters to load
		}
	}
}

