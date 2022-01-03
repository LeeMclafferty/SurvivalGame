
#pragma once

#include "CoreMinimal.h"
#include "Widgets/MenuBase.h"
#include "CharacterCreationWidget.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALGAME_API UCharacterCreationWidget : public UMenuBase
{
	GENERATED_BODY()

public:

protected:
		//Gender
	UPROPERTY(meta = (BindWidget))
	class UButton* gender_left_button;

	UPROPERTY(meta = (BindWidget))
	class UButton* gender_right_button;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* gender_text;

		//Hairstyles
	UPROPERTY(meta = (BindWidget))
	class UButton* hairstyle_left;

	UPROPERTY(meta = (BindWidget))
	class UButton* hairstyle_right;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* hairstyle_text;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* hairstyle_number;

		//Beard
	UPROPERTY(meta = (BindWidget))
	class USizeBox* facial_hair;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* facialhair_text;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* facialhair_number;

	UPROPERTY(meta = (BindWidget))
	class UButton* facialhair_right;

	UPROPERTY(meta = (BindWidget))
	class UButton* facialhair_left;

		//Hair Color
	UPROPERTY(meta = (BindWidget))
	class UButton* haircolor_left;

	UPROPERTY(meta = (BindWidget))
	class UButton* haircolor_right;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* haircolor_text;

		//Eye color
	UPROPERTY(meta = (BindWidget))
	class UButton* eyecolor_left;

	UPROPERTY(meta = (BindWidget))
	class UButton* eyecolor_right;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* eyecolor_text;

		//Skin Tone
	UPROPERTY(meta = (BindWidget))
	class UButton* skintone_right;

	UPROPERTY(meta = (BindWidget))
	class UButton* skintone_left;

	UPROPERTY(meta = (BindWidget))
	class UButton* create_character_button;

	virtual bool Initialize() override;

	FString male = "Male";
	FString female = "Female";
	int32 hairstyle_index;
	int32 beard_index;
	int32 haircolor_index;
	int32 eyecolor_index;
	int32 skin_index;


private:

	UFUNCTION()
	void OnPressedGenderLeft();

	UFUNCTION()
	void OnPressedGenderRight();

	UFUNCTION()
	void OnPressedHairsStyleLeft();

	UFUNCTION()
	void OnPressedHairsStyleRight();

	UFUNCTION()
	void SetHairStyleNumber();

	UFUNCTION()
	void OnPressedBeardLeft();

	UFUNCTION()
	void OnPressedBeardRight();

	UFUNCTION()
	void SetBeardNumber();

	UFUNCTION()
	void OnPressHairColorLeft();

	UFUNCTION()
	void OnPressHairColorRight();

		/* This function is made seperate so I can call it one hair syle change, this way the material will
		 update correctly when changing the hair style, but i dont want the color index to change when the style
		 changes*/
	UFUNCTION()
	void SetHairColor();

	UFUNCTION()
	void OnPressEyeColorLeft();

	UFUNCTION()
	void OnPressEyeColorRight();

	UFUNCTION()
	void SetEyeColor();

	UFUNCTION()
	void OnPressSkinToneLeft();

	UFUNCTION()
	void OnPressSkinToneRight();

	UFUNCTION()
	void SetSkintone();

	UFUNCTION()
	void OnPressCreateCharacter();
	


	
};
