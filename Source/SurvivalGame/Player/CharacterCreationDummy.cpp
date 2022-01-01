

#include "Player/CharacterCreationDummy.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneComponent.h"
#include "UObject/ConstructorHelpers.h"


ACharacterCreationDummy::ACharacterCreationDummy()
{
	PrimaryActorTick.bCanEverTick = true;

	root_component = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	RootComponent = root_component;

	head_mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Head"));
	head_mesh->SetupAttachment(root_component);

	chest_mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Chest"));
	chest_mesh->SetupAttachment(root_component);

	brow_mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Eye Brows"));
	brow_mesh->SetupAttachment(root_component);

	legs_mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Legs"));
	legs_mesh->SetupAttachment(root_component);

	shoes_mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Boots"));
	shoes_mesh->SetupAttachment(root_component);

	belt_mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Belt"));
	belt_mesh->SetupAttachment(root_component);

	hair_mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Hair"));
	hair_mesh->SetupAttachment(root_component);

	beard_mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Beard"));
	beard_mesh->SetupAttachment(root_component);

	is_male = true;

	SetAllSkMeshFromAssets();

}

void ACharacterCreationDummy::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACharacterCreationDummy::SetAllSkMeshFromAssets()
{
		// Setting mesh to assets
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>head1(TEXT("SkeletalMesh'/Game/aa_Imports/SkeletalMesh/Male/Base/MaleCharacter_Head.MaleCharacter_Head'"));
	if (head1.Succeeded())
	{
		male_head = head1.Object;
	}
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>head2(TEXT("SkeletalMesh'/Game/aa_Imports/SkeletalMesh/Female/Base/FemCharacter_Head.FemCharacter_Head'"));
	if (head2.Succeeded())
	{
		female_head = head2.Object;
	}
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>male_def_brows(TEXT("SkeletalMesh'/Game/aa_Imports/SkeletalMesh/Male/Beard/SK_Hu_M_Brows_01.SK_Hu_M_Brows_01'"));
	if (male_def_brows.Succeeded())
	{
		male_brows = male_def_brows.Object;
	}
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>femempty(TEXT("SkeletalMesh'/Game/aa_Imports/SkeletalMesh/Female/Base/FemCharacter_Empty.FemCharacter_Empty'"));
	if (femempty.Succeeded())
	{
		female_empty = femempty.Object;
	}
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>maleempty(TEXT("SkeletalMesh'/Game/aa_Imports/SkeletalMesh/Male/Base/MaleCharacter_Empty.MaleCharacter_Empty'"));
	if (maleempty.Succeeded())
	{
		male_empty = maleempty.Object;
	}

		/// <summary>
		/// Male hair styles
		/// </summary>
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>male_hair1(TEXT("/Game/aa_Imports/SkeletalMesh/Male/Hair/MaleCharacter_Hair01"));
	if (male_hair1.Succeeded())
	{
		male_hair_01 = male_hair1.Object;
		male_hairstyles.push_back(male_hair_01);
	}
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>male_hair2(TEXT("/Game/aa_Imports/SkeletalMesh/Male/Hair/MaleCharacter_Hair02"));
	if (male_hair2.Succeeded())
	{
		male_hair_02 = male_hair2.Object;
		male_hairstyles.push_back(male_hair_02);
	}
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>male_hair3(TEXT("/Game/aa_Imports/SkeletalMesh/Male/Hair/MaleCharacter_Hair03"));
	if (male_hair3.Succeeded())
	{
		male_hair_03 = male_hair3.Object;
		male_hairstyles.push_back(male_hair_03);
	}
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>male_hair4(TEXT("/Game/aa_Imports/SkeletalMesh/Male/Hair/MaleCharacter_Hair04"));
	if (male_hair4.Succeeded())
	{
		male_hair_04 = male_hair4.Object;
		male_hairstyles.push_back(male_hair_04);
	}
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>male_hair5(TEXT("/Game/aa_Imports/SkeletalMesh/Male/Hair/MaleCharacter_Hair05"));
	if (male_hair5.Succeeded())
	{
		male_hair_05 = male_hair5.Object;
		male_hairstyles.push_back(male_hair_05);
	}
	male_hairstyles.push_back(male_empty);

		/// <summary>
		/// Female hair styles
		/// </summary>
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>fem_hair1(TEXT("SkeletalMesh'/Game/aa_Imports/SkeletalMesh/Female/Hair/FemCharacter_Hair01.FemCharacter_Hair01'"));
	if (fem_hair1.Succeeded())
	{
		female_hair_01 = fem_hair1.Object;
		female_hairstyles.push_back(female_hair_01);
	}
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>fem_hair2(TEXT("SkeletalMesh'/Game/aa_Imports/SkeletalMesh/Female/Hair/FemCharacter_Hair02.FemCharacter_Hair02'"));
	if (fem_hair2.Succeeded())
	{
		female_hair_02 = fem_hair2.Object;
		female_hairstyles.push_back(female_hair_02);
	}
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>fem_hair3(TEXT("SkeletalMesh'/Game/aa_Imports/SkeletalMesh/Female/Hair/FemCharacter_Hair03.FemCharacter_Hair03'"));
	if (fem_hair3.Succeeded())
	{
		female_hair_03 = fem_hair3.Object;
		female_hairstyles.push_back(female_hair_03);
	}
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>fem_hair4(TEXT("/Game/aa_Imports/SkeletalMesh/Female/Hair/FemCharacter_Hair04"));
	if (fem_hair4.Succeeded())
	{
		female_hair_04 = fem_hair4.Object;
		female_hairstyles.push_back(female_hair_04);
	}
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>fem_hair5(TEXT("/Game/aa_Imports/SkeletalMesh/Female/Hair/FemCharacter_Hair05"));
	if (fem_hair5.Succeeded())
	{
		female_hair_05 = fem_hair5.Object;
		female_hairstyles.push_back(female_hair_05);
	}
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>fem_hair6(TEXT("/Game/aa_Imports/SkeletalMesh/Female/Hair/FemCharacter_Hair06"));
	if (fem_hair6.Succeeded())
	{
		female_hair_06 = fem_hair6.Object;
		female_hairstyles.push_back(female_hair_06);
	}
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>fem_hair7(TEXT("/Game/aa_Imports/SkeletalMesh/Female/Hair/FemCharacter_Hair07"));
	if (fem_hair7.Succeeded())
	{
		female_hair_07 = fem_hair7.Object;
		female_hairstyles.push_back(female_hair_07);
	}
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>fem_hair8(TEXT("/Game/aa_Imports/SkeletalMesh/Female/Hair/FemCharacter_Hair08"));
	if (fem_hair8.Succeeded())
	{
		female_hair_08 = fem_hair8.Object;
		female_hairstyles.push_back(female_hair_08);
	}
	female_hairstyles.push_back(female_empty);

		/// <summary>
		/// Male peasant outfit
		/// </summary>
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>male_pes_chest(TEXT("SkeletalMesh'/Game/aa_Imports/SkeletalMesh/Male/Armor/Peasant/MaleCharacter_PeasantChest.MaleCharacter_PeasantChest'"));
	if (male_pes_chest.Succeeded())
	{
		male_peasant_chest_sk = male_pes_chest.Object;
	}
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>male_pes_legs(TEXT("SkeletalMesh'/Game/aa_Imports/SkeletalMesh/Male/Armor/Peasant/MaleCharacter_PeasantLegs.MaleCharacter_PeasantLegs'"));
	if (male_pes_legs.Succeeded())
	{
		male_peasant_legs_sk = male_pes_legs.Object;
	}
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>male_pes_belt(TEXT("SkeletalMesh'/Game/aa_Imports/SkeletalMesh/Male/Armor/Peasant/MaleCharacter_PeasantBelt.MaleCharacter_PeasantBelt'"));
	if (male_pes_belt.Succeeded())
	{
		male_peasant_belt = male_pes_belt.Object;
	}
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>male_pes_boots(TEXT("SkeletalMesh'/Game/aa_Imports/SkeletalMesh/Male/Armor/Peasant/MaleCharacter_PeasantBoots.MaleCharacter_PeasantBoots'"));
	if (male_pes_boots.Succeeded())
	{
		male_peasant_boots = male_pes_boots.Object;
	}

		/// <summary>
		/// Female peasant outfit
		/// </summary>
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>female_pes_boots(TEXT("SkeletalMesh'/Game/aa_Imports/SkeletalMesh/Female/Armor/Peasant/FemCharacter_PeasantBoots.FemCharacter_PeasantBoots'"));
	if (female_pes_boots.Succeeded())
	{
		female_peasant_boots = female_pes_boots.Object;
	}
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>female_pes_belt(TEXT("SkeletalMesh'/Game/aa_Imports/SkeletalMesh/Female/Armor/Peasant/FemCharacter_PeasantBelt.FemCharacter_PeasantBelt'"));
	if (female_pes_belt.Succeeded())
	{
		female_peasant_belt = female_pes_belt.Object;
	}
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>female_pes_chest(TEXT("SkeletalMesh'/Game/aa_Imports/SkeletalMesh/Female/Armor/Peasant/FemCharacter_PeasantChest.FemCharacter_PeasantChest'"));
	if (female_pes_chest.Succeeded())
	{
		female_peasant_chest_sk = female_pes_chest.Object;
	}
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>female_pes_legs(TEXT("SkeletalMesh'/Game/aa_Imports/SkeletalMesh/Female/Armor/Peasant/FemCharacter_PeasantLegs.FemCharacter_PeasantLegs'"));
	if (female_pes_legs.Succeeded())
	{
		female_peasant_legs_sk = female_pes_legs.Object;
	}

		/// <summary>
		/// Beards
		/// </summary>
		beards.push_back(male_empty);
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>beard1(TEXT("/Game/aa_Imports/SkeletalMesh/Male/Beard/MaleCharacter_Beard01"));
	if (beard1.Succeeded())
	{
		beard_01 = beard1.Object;
		beards.push_back(beard_01);
	}
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>beard2(TEXT("/Game/aa_Imports/SkeletalMesh/Male/Beard/MaleCharacter_Beard02"));
	if (beard2.Succeeded())
	{
		beard_02 = beard2.Object;
		beards.push_back(beard_02);
	}
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>beard3(TEXT("/Game/aa_Imports/SkeletalMesh/Male/Beard/MaleCharacter_Beard03"));
	if (beard3.Succeeded())
	{
		beard_03 = beard3.Object;
		beards.push_back(beard_03);
	}
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>beard4(TEXT("/Game/aa_Imports/SkeletalMesh/Male/Beard/MaleCharacter_Beard04"));
	if (beard4.Succeeded())
	{
		beard_04 = beard4.Object;
		beards.push_back(beard_04);
	}
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>beard5(TEXT("/Game/aa_Imports/SkeletalMesh/Male/Beard/MaleCharacter_Beard05"));
	if (beard5.Succeeded())
	{
		beard_05 = beard5.Object;
		beards.push_back(beard_05);
	}
}

void ACharacterCreationDummy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}



