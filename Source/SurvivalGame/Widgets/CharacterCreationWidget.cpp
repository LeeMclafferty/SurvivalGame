

#include "Widgets/CharacterCreationWidget.h"
#include "Containers/Array.h"
#include "Engine/SkeletalMesh.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/SizeBox.h"
#include "Internationalization/Text.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "EditableTextBox.h"

#include "Player/CharacterCreationDummy.h"
#include "Framework/CharacterCreationGameMode.h"
#include "Framework/SurvivalGameInstance.h"
#include "World/CameraDirector.h"
#include "Framework/SaveGameBase.h"
#include "Player/SurvivalPlayerController.h"



bool UCharacterCreationWidget::Initialize()
{
	bool succsess = Super::Initialize();
		//Gender
	if (gender_left_button)
	{
		gender_left_button->OnPressed.AddDynamic(this, &UCharacterCreationWidget::OnPressedGenderLeft);
	}
	if (gender_right_button)
	{
		gender_right_button->OnPressed.AddDynamic(this, &UCharacterCreationWidget::OnPressedGenderRight);
	}
	if (gender_text)
	{
		gender_text->SetText(FText::FromString(male));
	}
		//Hair Styles
	if (hairstyle_left)
	{
		hairstyle_left->OnPressed.AddDynamic(this, &UCharacterCreationWidget::OnPressedHairsStyleLeft);
	}
	if (hairstyle_right)
	{
		hairstyle_right->OnPressed.AddDynamic(this, &UCharacterCreationWidget::OnPressedHairsStyleRight);

	}
	if (hairstyle_text)
	{
		hairstyle_text->SetText(FText::FromString("Hair Style"));
	}
		//Facial hair
	if (facialhair_left)
	{
		facialhair_left->OnPressed.AddDynamic(this, &UCharacterCreationWidget::OnPressedBeardLeft);

	}
	if (facialhair_right)
	{
		facialhair_right->OnPressed.AddDynamic(this, &UCharacterCreationWidget::OnPressedBeardRight);

	}
	if (haircolor_left)
	{
		haircolor_left->OnPressed.AddDynamic(this, &UCharacterCreationWidget::OnPressHairColorLeft);

	}
	if (haircolor_right)
	{
		haircolor_right->OnPressed.AddDynamic(this, &UCharacterCreationWidget::OnPressHairColorRight);
	

	}
	if (haircolor_text)
	{
		haircolor_text->SetText(FText::FromString("Brown"));
	}
		//Eye Color
	if (eyecolor_left)
	{
		eyecolor_left->OnPressed.AddDynamic(this, &UCharacterCreationWidget::OnPressEyeColorLeft);
	}
	if (eyecolor_right)
	{
		eyecolor_right->OnPressed.AddDynamic(this, &UCharacterCreationWidget::OnPressEyeColorRight);
	}
	if (eyecolor_text)
	{
		eyecolor_text->SetText(FText::FromString("Brown"));
	}
	if (skintone_left)
	{
		skintone_left->OnPressed.AddDynamic(this, &UCharacterCreationWidget::OnPressSkinToneLeft);
	}
	if (skintone_right)
	{
		skintone_right->OnPressed.AddDynamic(this, &UCharacterCreationWidget::OnPressSkinToneRight);
	}
	if (create_character_button)
	{
		create_character_button->OnPressed.AddDynamic(this,&UCharacterCreationWidget::OnPressCreateCharacter);
	}
	if (back_button)
	{
		back_button->OnPressed.AddDynamic(this, &UCharacterCreationWidget::OnPressBackButton);
	}
	if (zoom_out_button)
	{
		zoom_out_button->OnPressed.AddDynamic(this, &UCharacterCreationWidget::OnPressZoomOutButton);
	}
	if (zoom_in_button)
	{
		zoom_in_button->OnPressed.AddDynamic(this, &UCharacterCreationWidget::OnPressZoomInButton);
	}
	skin_index = 0;
	hairstyle_index = 0;
	beard_index = 0;
	haircolor_index = 0;
	eyecolor_index = 0;

	return succsess;
}

void UCharacterCreationWidget::OnPressedGenderLeft()
{
	// TODO
	// Change skeletal mesh to female peasant set.
	
		//References I should need
	ACharacterCreationGameMode* gamemode = Cast<ACharacterCreationGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	ACharacterCreationDummy* dummy = gamemode->GetCreationDummy();

		//set all meshes to male mesh
	gender_text->SetText(FText::FromString(male));
	dummy->head_mesh->SetSkeletalMesh(dummy->male_head);
	dummy->hair_mesh->SetSkeletalMesh(dummy->male_hairstyles[0]);
	dummy->chest_mesh->SetSkeletalMesh(dummy->male_peasant_chest_sk);
	dummy->legs_mesh->SetSkeletalMesh(dummy->male_peasant_legs_sk);
	dummy->belt_mesh->SetSkeletalMesh(dummy->male_peasant_belt);
	dummy->shoes_mesh->SetSkeletalMesh(dummy->male_peasant_boots);
	dummy->brow_mesh->SetSkeletalMesh(dummy->male_brows);
	dummy->is_male = true;
	hairstyle_index = 0;
	beard_index = 0;
	haircolor_index = 0;
	eyecolor_index = 0;
	skin_index = 0;
	haircolor_text->SetText(FText::FromString("Brown"));
	eyecolor_text->SetText(FText::FromString("Brown"));
	dummy->hair_mesh->SetMaterial(0, dummy->brownhair_01);
	dummy->brow_mesh->SetMaterial(0, dummy->brownhair_01);
	dummy->beard_mesh->SetMaterial(0, dummy->beard_brown);
	dummy->head_mesh->SetMaterial(0, dummy->brown_eyes);
	dummy->head_mesh->SetMaterial(1, dummy->skintone_02);
	facial_hair->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	dummy->head_mesh->PlayAnimation(gamemode->male_idle, true);
	SetHairStyleNumber();
	SetBeardNumber();
	SetSkintone();
}


void UCharacterCreationWidget::OnPressedGenderRight()
{
	ACharacterCreationGameMode* gamemode = Cast<ACharacterCreationGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	ACharacterCreationDummy* dummy = gamemode->GetCreationDummy();

		//set all meshes to female mesh. 
	gender_text->SetText(FText::FromString(female));
	dummy->head_mesh->SetSkeletalMesh(dummy->female_head);
	dummy->hair_mesh->SetSkeletalMesh(dummy->female_hairstyles[0]);
	dummy->chest_mesh->SetSkeletalMesh(dummy->female_peasant_chest_sk);
	dummy->legs_mesh->SetSkeletalMesh(dummy->female_peasant_legs_sk);
	dummy->belt_mesh->SetSkeletalMesh(dummy->female_peasant_belt);
	dummy->shoes_mesh->SetSkeletalMesh(dummy->female_peasant_boots);
	dummy->brow_mesh->SetSkeletalMesh(nullptr);
	dummy->beard_mesh->SetSkeletalMesh(nullptr);
	dummy->is_male = false;
	hairstyle_index = 0;
	beard_index = 0;
	haircolor_index = 0;
	eyecolor_index = 0;
	skin_index = 3;
	haircolor_text->SetText(FText::FromString("Brown"));
	eyecolor_text->SetText(FText::FromString("Brown"));
	dummy->hair_mesh->SetMaterial(0, dummy->brownhair_01);
	dummy->head_mesh->SetMaterial(0, dummy->brownhair_01);
	dummy->head_mesh->SetMaterial(1, dummy->brown_eyes);
	dummy->head_mesh->SetMaterial(2, dummy->skintone_04);
	dummy->head_mesh->SetMaterial(3, dummy->hair_tie);
	facial_hair->SetVisibility(ESlateVisibility::Hidden);
	dummy->head_mesh->PlayAnimation(gamemode->female_idle, true);
	SetHairStyleNumber();
	SetBeardNumber();
	SetSkintone();
}

void UCharacterCreationWidget::OnPressedHairsStyleLeft()
{
	ACharacterCreationGameMode* gamemode = Cast<ACharacterCreationGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	USurvivalGameInstance* game_instance = Cast<USurvivalGameInstance>(GetWorld()->GetGameInstance());
	ACharacterCreationDummy* dummy = gamemode->GetCreationDummy();
	
		//Male has 5 hair styles
	if (dummy->is_male)
	{
		if (hairstyle_index > 0)
		{
			hairstyle_index--;
			dummy->hair_mesh->SetSkeletalMesh(game_instance->male_hairstyles[hairstyle_index]);
			//dummy->male_hairstyles[hairstyle_index]
		}
	}
		//Female has 7 hair styles
	if (!dummy->is_male)
	{
		if (hairstyle_index > 0)
		{
			hairstyle_index--;
			dummy->hair_mesh->SetSkeletalMesh(game_instance->female_hairstyles[hairstyle_index]);
		}
	}
	//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Yellow, FString::Printf(TEXT("Color index: %i"), haircolor_index));
		//Set Hairstyle number
	SetHairStyleNumber();
		//Makes sure the hairstyle has the right material
	SetHairColor();
}

void UCharacterCreationWidget::OnPressedHairsStyleRight()
{
	USurvivalGameInstance* game_instance = Cast<USurvivalGameInstance>(GetWorld()->GetGameInstance());
	ACharacterCreationGameMode* gamemode = Cast<ACharacterCreationGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	ACharacterCreationDummy* dummy = gamemode->GetCreationDummy();
	
		//Male has 5 hair styles
	if (dummy->is_male)
	{
		if (hairstyle_index < 5)
		{
				hairstyle_index++;
				dummy->hair_mesh->SetSkeletalMesh(game_instance->male_hairstyles[hairstyle_index]);
		}
	}

		//Female has 8 hair styles
	if (!dummy->is_male)
	{
		if (hairstyle_index < 8)
		{
			hairstyle_index++;
			dummy->hair_mesh->SetSkeletalMesh(game_instance->male_hairstyles[hairstyle_index]);
		}
	}
	//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Yellow, FString::Printf(TEXT("Color index: %i"), haircolor_index));
		//Set Hairstyle number
	SetHairStyleNumber();
		//Makes sure the hairstyle has the right material
	SetHairColor();
	
}

void UCharacterCreationWidget::SetHairStyleNumber()
{
	hairstyle_number->SetText(FText::FromString(FString::FromInt(hairstyle_index + 1)));
}

void UCharacterCreationWidget::OnPressedBeardLeft()
{
	USurvivalGameInstance* game_instance = Cast<USurvivalGameInstance>(GetWorld()->GetGameInstance());
	ACharacterCreationGameMode* gamemode = Cast<ACharacterCreationGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	ACharacterCreationDummy* dummy = gamemode->GetCreationDummy();
		//Only works on male
	if (dummy->is_male)
	{
		if (beard_index > 0)
		{
			beard_index--;
			dummy->beard_mesh->SetSkeletalMesh(game_instance->beards[beard_index]);
		}
	}
	else
	{
		return;
	}
	//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Yellow, FString::Printf(TEXT("Color index: %i"), haircolor_index));
	SetBeardNumber();
}

void UCharacterCreationWidget::OnPressedBeardRight()
{
	USurvivalGameInstance* game_instance = Cast<USurvivalGameInstance>(GetWorld()->GetGameInstance());
	ACharacterCreationGameMode* gamemode = Cast<ACharacterCreationGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	ACharacterCreationDummy* dummy = gamemode->GetCreationDummy();

	if (dummy->is_male)
	{
		if (beard_index < 5)
		{
			beard_index++;
			dummy->beard_mesh->SetSkeletalMesh(game_instance->beards[beard_index]);
		}
	}
	else
	{
		return;
	}
	//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Yellow, FString::Printf(TEXT("Color index: %i"), haircolor_index));
	SetBeardNumber();
}

void UCharacterCreationWidget::SetBeardNumber()
{
	facialhair_number->SetText(FText::FromString(FString::FromInt(beard_index + 1)));
}

void UCharacterCreationWidget::OnPressHairColorLeft()
{
	if(haircolor_index > 0)
		haircolor_index--;

	SetHairColor();
} 

void UCharacterCreationWidget::OnPressHairColorRight()
{
	if (haircolor_index < 4)
		haircolor_index++;
	SetHairColor();
}

void UCharacterCreationWidget::SetHairColor()
{
	ACharacterCreationGameMode* gamemode = Cast<ACharacterCreationGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	ACharacterCreationDummy* dummy = gamemode->GetCreationDummy();

	/// Male
	if (dummy->is_male)
	{
		switch (haircolor_index)
		{
		case 0:	//Brown
			haircolor_text->SetText(FText::FromString("Brown"));
			dummy->brow_mesh->SetMaterial(0, dummy->brownhair_01);
			dummy->hair_mesh->SetMaterial(0, dummy->brownhair_01);
			dummy->beard_mesh->SetMaterial(0, dummy->beard_brown);
			if (hairstyle_index == 4 && dummy->is_male)
			{
				dummy->hair_mesh->SetMaterial(0, dummy->hair_tie);
				dummy->hair_mesh->SetMaterial(1, dummy->brownhair_02);
			}
			break;
		case 1: //Black
			haircolor_text->SetText(FText::FromString("Black"));
			dummy->hair_mesh->SetMaterial(0, dummy->blackhair_01);
			dummy->brow_mesh->SetMaterial(0, dummy->blackhair_01);
			dummy->beard_mesh->SetMaterial(0, dummy->beard_black);
			if (hairstyle_index == 4 && dummy->is_male)
			{
				dummy->hair_mesh->SetMaterial(0, dummy->hair_tie);
				dummy->hair_mesh->SetMaterial(1, dummy->blackhair_02);
			}
			break;
		case 2: //Blond
			haircolor_text->SetText(FText::FromString("Blonde"));
			dummy->hair_mesh->SetMaterial(0, dummy->blondehair_01);
			dummy->brow_mesh->SetMaterial(0, dummy->brow_color);
			dummy->beard_mesh->SetMaterial(0, dummy->beard_blonde);
			if (hairstyle_index == 4 && dummy->is_male)
			{
				dummy->hair_mesh->SetMaterial(0, dummy->hair_tie);
				dummy->hair_mesh->SetMaterial(1, dummy->blondehair_02);
			}
			break;
		case 3: //Grey
			haircolor_text->SetText(FText::FromString("Grey"));
			dummy->hair_mesh->SetMaterial(0, dummy->greyhair_01);
			dummy->brow_mesh->SetMaterial(0, dummy->greyhair_01);
			dummy->beard_mesh->SetMaterial(0, dummy->beard_grey);
			if (hairstyle_index == 4 && dummy->is_male)
			{
				dummy->hair_mesh->SetMaterial(0, dummy->hair_tie);
				dummy->hair_mesh->SetMaterial(1, dummy->greyhair_02);
			}
			break;
		case 4: //Red
			haircolor_text->SetText(FText::FromString("Red"));
			dummy->hair_mesh->SetMaterial(0, dummy->redhair_01);
			dummy->brow_mesh->SetMaterial(0, dummy->redhair_01);
			dummy->beard_mesh->SetMaterial(0, dummy->beard_red);
			if (hairstyle_index == 4 && dummy->is_male)
			{
				dummy->hair_mesh->SetMaterial(0, dummy->hair_tie);
				dummy->hair_mesh->SetMaterial(1, dummy->redhair_02);
			}
			break;
		}
	}

	/// Female
	if (!dummy->is_male)
	{
		switch (haircolor_index)
		{
		case 0:	//Brown
			haircolor_text->SetText(FText::FromString("Brown"));

			if ((hairstyle_index == 0 || hairstyle_index == 2 || hairstyle_index == 3) && !dummy->is_male)
			{
				dummy->hair_mesh->SetMaterial(0, dummy->brownhair_01);
			}
			if (hairstyle_index == 1)
			{
				dummy->hair_mesh->SetMaterial(1, dummy->hair_tie);
				dummy->hair_mesh->SetMaterial(0, dummy->brownhair_01);
			}

			if ((hairstyle_index == 4 || hairstyle_index == 5) && !dummy->is_male)
			{
				dummy->hair_mesh->SetMaterial(0, dummy->brownhair_02);
			}
			if (hairstyle_index == 6)
			{
				dummy->hair_mesh->SetMaterial(0, dummy->brownhair_02);
				dummy->hair_mesh->SetMaterial(1, dummy->hair_tie);
			}
			if (hairstyle_index == 7)
			{
				dummy->hair_mesh->SetMaterial(1, dummy->brownhair_02);
				dummy->hair_mesh->SetMaterial(0, dummy->hair_tie);
			}
			break;
		case 1: //Black
			haircolor_text->SetText(FText::FromString("Black"));

			if ((hairstyle_index == 0 || hairstyle_index == 2 || hairstyle_index == 3) && !dummy->is_male)
			{
				dummy->hair_mesh->SetMaterial(0, dummy->blackhair_01);
			}
			if (hairstyle_index == 1)
			{
				dummy->hair_mesh->SetMaterial(1, dummy->hair_tie);
				dummy->hair_mesh->SetMaterial(0, dummy->blackhair_01);
			}

			if ((hairstyle_index == 4 || hairstyle_index == 5) && !dummy->is_male)
			{
				dummy->hair_mesh->SetMaterial(0, dummy->blackhair_02);
			}
			if (hairstyle_index == 6)
			{
				dummy->hair_mesh->SetMaterial(0, dummy->blackhair_02);
				dummy->hair_mesh->SetMaterial(1, dummy->hair_tie);
			}
			if (hairstyle_index == 7)
			{
				dummy->hair_mesh->SetMaterial(1, dummy->blackhair_02);
				dummy->hair_mesh->SetMaterial(0, dummy->hair_tie);
			}
			break;
		case 2: //Blond
			haircolor_text->SetText(FText::FromString("Blonde"));

			if ((hairstyle_index == 0 || hairstyle_index == 2 || hairstyle_index == 3) && !dummy->is_male)
			{
				dummy->hair_mesh->SetMaterial(0, dummy->blondehair_01);
			}
			if (hairstyle_index == 1)
			{
				dummy->hair_mesh->SetMaterial(1, dummy->hair_tie);
				dummy->hair_mesh->SetMaterial(0, dummy->blondehair_01);
			}

			if ((hairstyle_index == 4 || hairstyle_index == 5) && !dummy->is_male)
			{
				dummy->hair_mesh->SetMaterial(0, dummy->blondehair_02);
			}
			if (hairstyle_index == 6)
			{
				dummy->hair_mesh->SetMaterial(0, dummy->blondehair_02);
				dummy->hair_mesh->SetMaterial(1, dummy->hair_tie);
			}
			if (hairstyle_index == 7)
			{
				dummy->hair_mesh->SetMaterial(1, dummy->blondehair_02);
				dummy->hair_mesh->SetMaterial(0, dummy->hair_tie);
			}
			break;
		case 3: //Grey
			haircolor_text->SetText(FText::FromString("Grey"));

			if ((hairstyle_index == 0 || hairstyle_index == 2 || hairstyle_index == 3) && !dummy->is_male)
			{
				dummy->hair_mesh->SetMaterial(0, dummy->greyhair_01);
			}
			if (hairstyle_index == 1)
			{
				dummy->hair_mesh->SetMaterial(1, dummy->hair_tie);
				dummy->hair_mesh->SetMaterial(0, dummy->greyhair_01);
			}

			if ((hairstyle_index == 4 || hairstyle_index == 5) && !dummy->is_male)
			{
				dummy->hair_mesh->SetMaterial(0, dummy->greyhair_02);
			}
			if (hairstyle_index == 6)
			{
				dummy->hair_mesh->SetMaterial(0, dummy->greyhair_02);
				dummy->hair_mesh->SetMaterial(1, dummy->hair_tie);
			}
			if (hairstyle_index == 7)
			{
				dummy->hair_mesh->SetMaterial(1, dummy->greyhair_02);
				dummy->hair_mesh->SetMaterial(0, dummy->hair_tie);
			}
			break;
		case 4: //Red
			haircolor_text->SetText(FText::FromString("Red"));

			if ((hairstyle_index == 0 || hairstyle_index == 2 || hairstyle_index == 3) && !dummy->is_male)
			{
				dummy->hair_mesh->SetMaterial(0, dummy->redhair_01);
			}
			if (hairstyle_index == 1)
			{
				dummy->hair_mesh->SetMaterial(1, dummy->hair_tie);
				dummy->hair_mesh->SetMaterial(0, dummy->redhair_01);
			}

			if ((hairstyle_index == 4 || hairstyle_index == 5) && !dummy->is_male)
			{
				dummy->hair_mesh->SetMaterial(0, dummy->redhair_02);
			}
			if (hairstyle_index == 6)
			{
				dummy->hair_mesh->SetMaterial(0, dummy->redhair_02);
				dummy->hair_mesh->SetMaterial(1, dummy->hair_tie);
			}
			if (hairstyle_index == 7)
			{
				dummy->hair_mesh->SetMaterial(1, dummy->redhair_02);
				dummy->hair_mesh->SetMaterial(0, dummy->hair_tie);
			}
		}
	}
}

void UCharacterCreationWidget::OnPressEyeColorLeft()
{

	if(eyecolor_index > 0)
		eyecolor_index--;

	SetEyeColor();
}

void UCharacterCreationWidget::OnPressEyeColorRight()
{
	if(eyecolor_index  < 3)
		eyecolor_index++;

	SetEyeColor();
}

void UCharacterCreationWidget::SetEyeColor()
{

	ACharacterCreationGameMode* gamemode = Cast<ACharacterCreationGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	ACharacterCreationDummy* dummy = gamemode->GetCreationDummy();
	switch (eyecolor_index)
	{
	case 0: //Brown
		eyecolor_text->SetText(FText::FromString("Brown"));

		if (dummy->is_male)
			dummy->head_mesh->SetMaterial(0, dummy->brown_eyes);
		if (!dummy->is_male)
			dummy->head_mesh->SetMaterial(1, dummy->brown_eyes);
		break;
	case 1: //Blue
		eyecolor_text->SetText(FText::FromString("Blue"));

		if (dummy->is_male)
			dummy->head_mesh->SetMaterial(0, dummy->blue_eyes);
		if (!dummy->is_male)
			dummy->head_mesh->SetMaterial(1, dummy->blue_eyes);
		break;
	case 2:	//Green
		eyecolor_text->SetText(FText::FromString("Green"));

		if (dummy->is_male)
			dummy->head_mesh->SetMaterial(0, dummy->green_eyes);
		if (!dummy->is_male)
			dummy->head_mesh->SetMaterial(1, dummy->green_eyes);
		break;
	case 3:	//Purple
		eyecolor_text->SetText(FText::FromString("Purple"));

		if (dummy->is_male)
			dummy->head_mesh->SetMaterial(0, dummy->purple_eyes);
		if (!dummy->is_male)
			dummy->head_mesh->SetMaterial(1, dummy->purple_eyes);
		break;
	}
}

void UCharacterCreationWidget::OnPressSkinToneLeft()
{
	if(skin_index > 0)
		skin_index--;
	//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Yellow, FString::Printf(TEXT("Index %i"), skin_index));
	SetSkintone();
}

void UCharacterCreationWidget::OnPressSkinToneRight()
{
	if(skin_index < 4)
		skin_index++;
	//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Yellow, FString::Printf(TEXT("Index %i"), skin_index));
		SetSkintone();
}

void UCharacterCreationWidget::SetSkintone()
{
	ACharacterCreationGameMode* gamemode = Cast<ACharacterCreationGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	ACharacterCreationDummy* dummy = gamemode->GetCreationDummy();
	
	if (dummy->is_male)
	{
		switch (skin_index)
		{
		case 0:
			dummy->chest_mesh->SetMaterial(1, dummy->skintone_01);
			dummy->head_mesh->SetMaterial(1, dummy->skintone_01);
			dummy->chest_mesh->SetMaterial(0, dummy->male_peasant_set_01);
			dummy->legs_mesh->SetMaterial(0, dummy->male_peasant_set_01);
			break;
		case 1:
			dummy->chest_mesh->SetMaterial(1, dummy->skintone_02);
			dummy->head_mesh->SetMaterial(1, dummy->skintone_02);
			dummy->chest_mesh->SetMaterial(0, dummy->male_peasant_set_02);
			dummy->legs_mesh->SetMaterial(0, dummy->male_peasant_set_02);
			break;
		case 2:
			dummy->chest_mesh->SetMaterial(1, dummy->skintone_03);
			dummy->head_mesh->SetMaterial(1, dummy->skintone_03);
			dummy->chest_mesh->SetMaterial(0, dummy->male_peasant_set_03);
			dummy->legs_mesh->SetMaterial(0, dummy->male_peasant_set_03);
			break;
		case 3:
			dummy->chest_mesh->SetMaterial(1, dummy->skintone_04);
			dummy->head_mesh->SetMaterial(1, dummy->skintone_04);
			dummy->chest_mesh->SetMaterial(0, dummy->male_peasant_set_04);
			dummy->legs_mesh->SetMaterial(0, dummy->male_peasant_set_04);
			break;
		case 4:
			dummy->chest_mesh->SetMaterial(1, dummy->skintone_05);
			dummy->head_mesh->SetMaterial(1, dummy->skintone_05);
			dummy->chest_mesh->SetMaterial(0, dummy->male_peasant_set_05);
			dummy->legs_mesh->SetMaterial(0, dummy->male_peasant_set_05);
			break;
		}
	}
	if (!dummy->is_male)
	{
		switch (skin_index)
		{
		case 0:
			dummy->chest_mesh->SetMaterial(1, dummy->skintone_01);
			dummy->head_mesh->SetMaterial(2, dummy->skintone_01);
			dummy->chest_mesh->SetMaterial(0, dummy->female_peasant_set_01);
			dummy->legs_mesh->SetMaterial(0, dummy->female_peasant_set_01);
			break;
		case 1:
			dummy->chest_mesh->SetMaterial(1, dummy->skintone_02);
			dummy->head_mesh->SetMaterial(2, dummy->skintone_02);
			dummy->chest_mesh->SetMaterial(0, dummy->female_peasant_set_02);
			dummy->legs_mesh->SetMaterial(0, dummy->female_peasant_set_02);
			break;
		case 2:
			dummy->chest_mesh->SetMaterial(1, dummy->skintone_03);
			dummy->head_mesh->SetMaterial(2, dummy->skintone_03);
			dummy->chest_mesh->SetMaterial(0, dummy->female_peasant_set_03);
			dummy->legs_mesh->SetMaterial(0, dummy->female_peasant_set_03);
			break;
		case 3:
			dummy->chest_mesh->SetMaterial(1, dummy->skintone_04);
			dummy->head_mesh->SetMaterial(2, dummy->skintone_04);
			dummy->chest_mesh->SetMaterial(0, dummy->female_peasant_set_04);
			dummy->legs_mesh->SetMaterial(0, dummy->female_peasant_set_04);
			break;
		case 4:
			dummy->chest_mesh->SetMaterial(1, dummy->skintone_05);
			dummy->head_mesh->SetMaterial(2, dummy->skintone_05);
			dummy->chest_mesh->SetMaterial(0, dummy->female_peasant_set_05);
			dummy->legs_mesh->SetMaterial(0, dummy->female_peasant_set_05);
			break;
		}
	}
}

void UCharacterCreationWidget::OnPressCreateCharacter()
{
	ACharacterCreationGameMode* gamemode = Cast<ACharacterCreationGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	USurvivalGameInstance* game_instance = Cast<USurvivalGameInstance>(GetWorld()->GetGameInstance());
	ASurvivalPlayerController* pc = Cast<ASurvivalPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if(gamemode != nullptr && game_instance != nullptr)
	{ 
		pc->SaveNewCharacterData();
		if (gamemode->is_hosting)
		{
			//Still need a server options menu when you press host in main menu.
			game_instance->Host();
			//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Yellow, FString::Printf(TEXT("Is Hosting: %i"), gamemode->is_hosting));
		}
		if (!gamemode->is_hosting)
		{
			/*GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Yellow, FString::Printf(TEXT("Entered IP: %s"), *gamemode->GetEnteredIP()));
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Yellow, FString::Printf(TEXT("Is Hosting: %i"), gamemode->is_hosting));*/
			game_instance->Join(gamemode->GetEnteredIP());
		}
	}
		
	
		
}

void UCharacterCreationWidget::OnPressBackButton()
{
	ACharacterCreationGameMode* gamemode = Cast<ACharacterCreationGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	this->RemoveFromParent();
	gamemode->GetCameraDirector()->SetViewToCameraOne();

	FTimerHandle timerhandle;
	GetWorld()->GetTimerManager().SetTimer(timerhandle, this, &UCharacterCreationWidget::LoadMainMenu, gamemode->GetCameraDirector()->smooth_blend_time, false);
}

void UCharacterCreationWidget::LoadMainMenu()
{
	USurvivalGameInstance* game_instance = Cast<USurvivalGameInstance>(GetGameInstance());

	game_instance->LoadGameMainMenu();

}

void UCharacterCreationWidget::OnPressZoomOutButton()
{
	ACharacterCreationGameMode* gamemode = Cast<ACharacterCreationGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	gamemode->GetCameraDirector()->SetViewToCameraTwo();
}

void UCharacterCreationWidget::OnPressZoomInButton()
{
	ACharacterCreationGameMode* gamemode = Cast<ACharacterCreationGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	gamemode->GetCameraDirector()->SetViewToCameraThree();
}

void UCharacterCreationWidget::SaveCharacterData()
{
	ACharacterCreationGameMode* gamemode = Cast<ACharacterCreationGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	ACharacterCreationDummy* dummy = gamemode->GetCreationDummy();
	USaveGameBase* save_instance = Cast<USaveGameBase>(UGameplayStatics::CreateSaveGameObject(USaveGameBase::StaticClass()));
	USurvivalGameInstance* game_instance = Cast<USurvivalGameInstance>(GetWorld()->GetGameInstance());

	if(dummy != nullptr && save_instance != nullptr && gamemode != nullptr)
	{ 
		save_instance->player_save_data.player_hair = dummy->hair_mesh->SkeletalMesh; 
		FString slot_name = "Player Save";
		int32 player_index = GetWorld()->GetControllerIterator().GetIndex();
		//save_instance->player_save_data = creation_save_data;

		UGameplayStatics::SaveGameToSlot(save_instance, slot_name, 0);
	}
}

