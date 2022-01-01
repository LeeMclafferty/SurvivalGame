
#include "CharacterBase.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "TimerManager.h"
#include "Materials/MaterialInstance.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/DamageType.h"
#include"Kismet/GameplayStatics.h"
#include "SurvivalGame.h"
#include "Animation/AnimInstance.h"
#include "Logging/LogMacros.h"

#include "World/Pickup.h"
#include "Components/InteractionComponent.h"
#include "Components/InventoryComponent.h"
#include "Items/EquippableItem.h"
#include "Items/ArmorItem.h"
#include "Player/SurvivalPlayerController.h"
#include "Weapons/PunchDamage.h"
#include "Items/WeaponItem.h"
#include "Items/ShieldItem.h"
#include "Weapons/Weapon.h"
#include "Weapons/Shield.h"

#define LOCTEXT_NAMESPACE "CharacterBase"

ACharacterBase::ACharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	spring_arm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	spring_arm->SetupAttachment(GetMesh());
	spring_arm->bUsePawnControlRotation = true;
	spring_arm->TargetArmLength = 300.f;

	camera_component = CreateDefaultSubobject<UCameraComponent>("Camera Component");
	camera_component->SetupAttachment(spring_arm);
	camera_component->bUsePawnControlRotation = true;

	beard_mesh = player_skeletal_meshes.Add(EEquippableSlot::EIS_Beard, CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Beard Mesh")));
	ears_mesh = player_skeletal_meshes.Add(EEquippableSlot::EIS_Ears, CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Ears Mesh")));
	brow_mesh = player_skeletal_meshes.Add(EEquippableSlot::EIS_Brow, CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Brow Mesh")));
	hair_mesh = player_skeletal_meshes.Add(EEquippableSlot::EIS_Hair, CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Hair Mesh")));
	chest_mesh = player_skeletal_meshes.Add(EEquippableSlot::EIS_Chest, CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Chest Mesh")));
	bracer_mesh = player_skeletal_meshes.Add(EEquippableSlot::EIS_Bracer, CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Bracer Mesh")));
	hands_mesh = player_skeletal_meshes.Add(EEquippableSlot::EIS_Hands, CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Hands Mesh")));
	belt_mesh = player_skeletal_meshes.Add(EEquippableSlot::EIS_Belt, CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Belt Mesh")));
	legs_mesh = player_skeletal_meshes.Add(EEquippableSlot::EIS_Legs, CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Legs Mesh")));
	calves_mesh = player_skeletal_meshes.Add(EEquippableSlot::EIS_Calves, CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Calves Mesh")));
	shoes_mesh = player_skeletal_meshes.Add(EEquippableSlot::EIS_Shoes, CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Shoes_Mesh")));
	test_mesh = player_skeletal_meshes.Add(EEquippableSlot::EIS_Throwable, CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Test Mesh")));

	hat_mesh = player_static_meshes.Add(EEquippableSlot::EIS_Head, CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hat Mesh")));
	backpack_mesh = player_static_meshes.Add(EEquippableSlot::EIS_Back, CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Back Mesh")));
	weapon_mesh = player_static_meshes.Add(EEquippableSlot::EIS_Weapon, CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon Mesh")));
	shield_mesh = player_static_meshes.Add(EEquippableSlot::EIS_Shield, CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sheild Mesh")));

	for (auto& player_skeletal_mesh : player_skeletal_meshes)
	{
		USkeletalMeshComponent* skeletal_mesh_component = player_skeletal_mesh.Value;
		skeletal_mesh_component->SetupAttachment(GetMesh());
		skeletal_mesh_component->SetMasterPoseComponent(GetMesh());
	}

	for (auto& player_static_mesh : player_static_meshes)
	{
		UStaticMeshComponent* static_mesh_component = player_static_mesh.Value;
	}

	hat_mesh->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), FName("HatSocket"));
	backpack_mesh->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), FName("BackAccessorySocket"));
	weapon_mesh->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), FName("Weapon_R"));
	shield_mesh->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), FName("ShieldSocket"));

	this->GetCharacterMovement()->NavAgentProps.bCanCrouch = true;

	interaction_check_frequency = 0.f;
	interaction_check_distance = 500.f;

	player_inventory = CreateDefaultSubobject<UInventoryComponent>("PlayerInventory");
	player_inventory->SetSlotCapacity(20);
	player_inventory->SetWeightCapacity(100.f);

	loot_player_interaction = CreateDefaultSubobject<UInteractionComponent>("PlayerInteractionComponent");
	loot_player_interaction->interactable_action_text = LOCTEXT("LootPlayerText", "Search Body");
	loot_player_interaction->interactable_name_text = LOCTEXT("LootPlayerNam", "Player");
	loot_player_interaction->SetupAttachment(GetRootComponent());
	loot_player_interaction->SetActive(false, true);
	loot_player_interaction->Activate(false);


	// Stat Defaults
	max_health = 100.f;
	health = max_health;

	max_stamina = 100.f;
	stamina = max_stamina;
}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();

	loot_player_interaction->on_interact.AddDynamic(this, &ACharacterBase::BeginLootingPlayer);

	if (APlayerState* player_state = GetPlayerState())
	{
		loot_player_interaction->SetInteractableNameText(FText::FromString(player_state->GetPlayerName()));
	}
}



void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	bool is_interacting_on_server = (HasAuthority() && IsInteracting());

	//if((!HasAuthority() || is_interacting_on_server) && GetWorld()->TimeSince(interaction_data.last_interaction_check_time) > interaction_check_frequency)
	if(GetWorld()->TimeSince(interaction_data.last_interaction_check_time) > interaction_check_frequency)
	{ 
		PerformInteractionCheck();
	}


// 	FVector start = camera_component->GetComponentLocation();
// 	FVector forward_vector = camera_component->GetForwardVector();
// 
// 	FVector trace_start = start + (forward_vector * spring_arm->TargetArmLength);
// 	FVector trace_end = start + (forward_vector * (melee_attack_distance + spring_arm->TargetArmLength));
// 
// 	DrawDebugLine(GetWorld(), trace_start, trace_end, FColor::Purple, true, 5.f, 1, 3.f);
}


void ACharacterBase::Restart()
{
	Super::Restart();

	if (ASurvivalPlayerController* player_controller = Cast<ASurvivalPlayerController>(GetController()))
	{
		player_controller->ShowInGameUI();
	}
}

void ACharacterBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACharacterBase, loot_source);
	DOREPLIFETIME_CONDITION(ACharacterBase, health, COND_OwnerOnly); //CONDITION owner only is a small optimization bc other players dont need to know how much health others have. 
	DOREPLIFETIME(ACharacterBase, killer);
	DOREPLIFETIME(ACharacterBase, current_primary_weapon);
	DOREPLIFETIME(ACharacterBase, current_shield);
}

void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Move Forward", this, &ACharacterBase::MoveForward);
	PlayerInputComponent->BindAxis("Move Right", this, &ACharacterBase::MoveRight);
	PlayerInputComponent->BindAxis("Look Up", this, &ACharacterBase::LookUp);
	PlayerInputComponent->BindAxis("Turn", this, &ACharacterBase::Turn);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ACharacterBase::StartCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &ACharacterBase::StopCrouch);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ACharacterBase::BeginInteract);
	PlayerInputComponent->BindAction("Interact", IE_Released, this, &ACharacterBase::EndInteract);

	PlayerInputComponent->BindAction("Basic Attack", IE_Pressed, this, &ACharacterBase::StartBasicAttack);
	PlayerInputComponent->BindAction("Basic Attack", IE_Released, this, &ACharacterBase::StopBasicAttack);

}

float ACharacterBase::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	const float damage_dealt = ModifyHealth(-Damage);

	if (health <= 0.f)
	{
		if (ACharacterBase* killer_character = Cast<ACharacterBase>(DamageCauser->GetOwner()))
		{
			KilledByPlayer(DamageEvent, killer_character, DamageCauser);
		}
		else
		{
			OnSuicide(DamageEvent, DamageCauser);
		}
	}

	return damage_dealt;
}


void ACharacterBase::MoveForward(float value)
{
	if (value  != 0.f)
		 this->AddMovementInput(GetActorForwardVector(), value);
}

void ACharacterBase::MoveRight(float value)
{
	if (value != 0.f)
		this->AddMovementInput(GetActorRightVector(), value);

}

void ACharacterBase::LookUp(float value)
{
	if(value != 0)
		AddControllerPitchInput(value);
}

void ACharacterBase::Turn(float value)
{
	if (value != 0)
		AddControllerYawInput(value);
}

void ACharacterBase::StartCrouch()
{
	Crouch();
}

void ACharacterBase::StopCrouch()
{
	UnCrouch();
}

void ACharacterBase::PerformInteractionCheck()
{

	FVector start = camera_component->GetComponentLocation();
	FVector forward_vector = camera_component->GetForwardVector();

	if(GetController() == nullptr)
	{ 
		return;
	}

	interaction_data.last_interaction_check_time = GetWorld()->GetTimeSeconds();


	FVector trace_start = start + (forward_vector * spring_arm->TargetArmLength);
	FVector trace_end = start + (forward_vector * interaction_check_distance);
	FHitResult trace_hit_result;

	FCollisionQueryParams query_params;
	query_params.AddIgnoredActor(this);

	//DrawDebugLine(GetWorld(), trace_start, trace_end, FColor::Green, true, 5.f, 1, 3.f);

	if (GetWorld()->LineTraceSingleByChannel(trace_hit_result, trace_start, trace_end, ECC_Visibility, query_params)) // Cast a line
	{
		if (trace_hit_result.GetActor()) // Check if it hit an actor
		{
			if (UInteractionComponent* interaction_component = Cast<UInteractionComponent>(trace_hit_result.GetActor()->GetComponentByClass(UInteractionComponent::StaticClass()))) // Check for interaction comp
			{
				float distance = (trace_start - trace_hit_result.ImpactPoint).Size(); // Calculate how far away player is

				if (interaction_component != GetInteractable() && distance <= interaction_component->interaction_distance) // Check if we are close enough to interact
				{
					FoundNewInteractable(interaction_component);
				}
				else if (distance > interaction_component->interaction_distance && GetInteractable()) // Check if we are close enough to interact
				{
					CouldntFindInteractable();
				}

				return;
			}
		}
	}

	CouldntFindInteractable();
}

void ACharacterBase::CouldntFindInteractable()
{
	if (GetWorldTimerManager().IsTimerActive(timerhandle_interact))
	{
		GetWorldTimerManager().ClearTimer(timerhandle_interact);
	}

	if (UInteractionComponent* interactable = GetInteractable())
	{
		interactable->EndFocus(this);

		if (interaction_data.is_interacting)
		{
			EndInteract();
		}
	}

	interaction_data.viewed_interaction_component = nullptr;
}

void ACharacterBase::FoundNewInteractable(UInteractionComponent* interactable)
{
	EndInteract();

	if (UInteractionComponent* old_interactable = GetInteractable())
	{
		old_interactable->EndFocus(this);
	}
	
	interaction_data.viewed_interaction_component = interactable;
	interactable->BeginFocus(this);
}

void ACharacterBase::BeginInteract()
{
	if (!HasAuthority())
	{
		ServerBeginInteract();
	}

	if (HasAuthority())
	{
		PerformInteractionCheck();
	}

	interaction_data.is_interacting = true;

	if (UInteractionComponent* interactable = GetInteractable()) // if player the player has an interactable
	{
		interactable->BeginInteraction(this); // then call the interactable's BeginInteraction() function

		if (FMath::IsNearlyZero(interactable->interaction_time)) // If there is no timer then interact immediately 
		{
			Interact();
		}
		else // interact based on the interactable's interaction_time variable
		{
			GetWorldTimerManager().SetTimer(timerhandle_interact, this, &ACharacterBase::Interact, interactable->interaction_time, false);
		}

	}
}


void ACharacterBase::ServerBeginInteract_Implementation()
{
	BeginInteract();
}

bool ACharacterBase::ServerBeginInteract_Validate()
{
	return true;
}

void ACharacterBase::EndInteract()
{
	if (!HasAuthority())
	{
		ServerEndInteract();
	}

	interaction_data.is_interacting = false;

	GetWorldTimerManager().ClearTimer (timerhandle_interact);

	if (UInteractionComponent* interactable = GetInteractable())
	{
		interactable->EndInteraction(this);
	}
}

void ACharacterBase::ServerEndInteract_Implementation()
{
	EndInteract();
}

bool ACharacterBase::ServerEndInteract_Validate()
{
	return true;
}

void ACharacterBase::Interact()
{
	GetWorldTimerManager().ClearTimer(timerhandle_interact);

	if (UInteractionComponent* interactable = GetInteractable())
	{
		interactable->Interact(this);
	}
}

bool ACharacterBase::IsInteracting() const
{
	return GetWorldTimerManager().IsTimerActive(timerhandle_interact);
}

float ACharacterBase::GetRemainingInteractTime() const
{
	return GetWorldTimerManager().GetTimerRemaining(timerhandle_interact);
}

void ACharacterBase::UseItem(class UItemBase* item)
{
	if (!HasAuthority() && item)
	{
		ServerUseItem(item);
	}

	if (HasAuthority())
	{
		if (player_inventory && !player_inventory->FindItem(item))
		{
			return;
		}
	}

	if (item)
	{
		item->Use(this);
	}
}

void ACharacterBase::ServerUseItem_Implementation(class UItemBase* item)
{
	UseItem(item);
}

bool ACharacterBase::ServerUseItem_Validate(class UItemBase* item)
{
	return true;
}

void ACharacterBase::DropItem(class UItemBase* item, const int32 quantiy)
{
	if (player_inventory && item && player_inventory->FindItem(item))
	{
		if (!HasAuthority())
		{
			ServerDropItem(item, quantiy);
			return;
		}
	}

	if (HasAuthority())
	{
		const int32 item_quantity = item->GetQuantity();
		const int32 dropped_quantity = player_inventory->ConsumeItem(item, quantiy);

		FActorSpawnParameters spawn_params;
		spawn_params.Owner = this;
		spawn_params.bNoFail = true;
		spawn_params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		FVector spawn_loction = GetActorLocation();
		spawn_loction.Z -= GetCapsuleComponent()->GetScaledCapsuleHalfHeight();

		FTransform spawn_transform(GetActorRotation(), spawn_loction);

		ensure(pickup_class);

		APickup* pickup = GetWorld()->SpawnActor<APickup>(pickup_class, spawn_transform, spawn_params);
		pickup->InitializePickcup(item->GetClass(), dropped_quantity);
		
	}
}

void ACharacterBase::ServerDropItem_Implementation(class UItemBase* item, const int32 quantity)
{
	DropItem(item, quantity);
}

bool ACharacterBase::ServerDropItem_Validate(class UItemBase* item, const int32 quantity)
{
	return true;
}

class USkeletalMeshComponent* ACharacterBase::GetSlotSkeletalMeshComponent(const EEquippableSlot slot)
{
	if (player_skeletal_meshes.Contains(slot))
	{
		return *player_skeletal_meshes.Find(slot);
	}
	return nullptr;
}

class UStaticMeshComponent* ACharacterBase::GetSlotStaticMeshComponent(const EEquippableSlot slot)
{
	if (player_static_meshes.Contains(slot))
	{
		return *player_static_meshes.Find(slot);
	}
	return nullptr;
}

bool ACharacterBase::EquipItem(UEquippableItem* item)
{
	equipped_items.Add(item->slot, item); // When and item is equipped store it in side of the equipped items TMap. ( TMap::Add(inkey, value) )
	on_equipped_items_changed.Broadcast(item->slot, item);
	return true;
}

bool ACharacterBase::UnEquipItem(UEquippableItem* item)
{
	if (item)
	{
		if(equipped_items.Contains(item->slot))
		{ 
			if (item == *equipped_items.Find(item->slot))
			{
				equipped_items.Remove(item->slot);
				on_equipped_items_changed.Broadcast(item->slot, item);
				return true;
			}
		}
	}
	return false;
}

void ACharacterBase::EquipArmor(class UArmorItem* armor)
{
	if(armor->skeletal_mesh != nullptr && armor->material_instance != nullptr)
	{ 
			
		if (USkeletalMeshComponent* skeletal_armor_mesh = *player_skeletal_meshes.Find(armor->slot))
		{
			if(skeletal_armor_mesh != nullptr)
			{ 
				skeletal_armor_mesh->SetSkeletalMesh(armor->skeletal_mesh);
				skeletal_armor_mesh->SetMaterial(skeletal_armor_mesh->GetMaterials().Num() - 1, armor->material_instance);
			}
		}
	}
	
	if(armor->static_mesh != nullptr)
	{ 
		if(UStaticMeshComponent* static_armor_mesh = *player_static_meshes.Find(armor->slot))
		{
			if(static_armor_mesh != nullptr)
			{ 
				static_armor_mesh->SetStaticMesh(armor->static_mesh);
			}
		}
	}
}

void ACharacterBase::UnequipArmor(const EEquippableSlot slot)
{

		if(GetSlotStaticMeshComponent(slot) == nullptr)
		{ 
			if (GetSlotSkeletalMeshComponent(slot)->SkeletalMesh != nullptr)
			{
				GetSlotSkeletalMeshComponent(slot)->SetSkeletalMesh(nullptr);
			}
			else
			{
				return;
			}
		}

		if(GetSlotSkeletalMeshComponent(slot) == nullptr && GetSlotStaticMeshComponent(slot) != nullptr)
		{
			GetSlotStaticMeshComponent(slot)->SetStaticMesh(nullptr);
		}
			
	

}

void ACharacterBase::SetLootSource(class UInventoryComponent* new_loot_source)
{
	
	if(new_loot_source && new_loot_source->GetOwner())
	{
		new_loot_source->GetOwner()->OnDestroyed.AddUniqueDynamic(this, &ACharacterBase::OnLootSourceOwnerDestroyed); // If the item we are looting is destroyed then remove the loot screen. (body disappearing after death ect.)
	}

	if (HasAuthority())
	{
		if(new_loot_source)
		{ 
			if (ACharacterBase* character_being_looted = Cast<ACharacterBase>(new_loot_source->GetOwner()))
			{
				character_being_looted->SetLifeSpan(120.f); // If a players inventory is opened to be looted, add 2 mins to loot life. (So it does not disappear while looting)
			}
		}

		loot_source = new_loot_source; // If you are the server set loot source
		OnRep_LootSource();
	}
	else
	{
		ServerSetLootSource(new_loot_source); // If you are not the server then ask the server to set the loot source
	}
}

bool ACharacterBase::IsLooting() const
{
	return loot_source != nullptr;
}

void ACharacterBase::LootItem(class UItemBase* item_to_give)
{
	if(HasAuthority())
	{ 
		if (player_inventory && loot_source && item_to_give && loot_source->HasItem(item_to_give->GetClass(), item_to_give->GetQuantity()))
		{
			const FItemAddResult add_result = player_inventory->TryAddItem(item_to_give);

			if (add_result.actual_amount_given > 0)
			{
				loot_source->ConsumeItem(item_to_give, add_result.actual_amount_given); 
			}
			else
			{
				if (ASurvivalPlayerController* player_character = Cast<ASurvivalPlayerController>(GetController()))
				{
					player_character->ClientShowNotification(add_result.error_text);
				}
			}
		}
	}
	else
	{ 
		ServerLootItem(item_to_give);
	}
}

void ACharacterBase::ServerLootItem_Implementation(class UItemBase* item_to_give)
{
	LootItem(item_to_give);
}

bool ACharacterBase::ServerLootItem_Validate(class UItemBase* item_to_give)
{
	return true;
}

void ACharacterBase::BeginLootingPlayer(class ACharacterBase* player)
{
	if (player)
	{
		player->SetLootSource(player_inventory);
	}
}

void ACharacterBase::ServerSetLootSource_Implementation(class UInventoryComponent* new_loot_source)
{
	SetLootSource(new_loot_source);
}

bool ACharacterBase::ServerSetLootSource_Validate(class UInventoryComponent* new_loot_source)
{
	return true;
}

void ACharacterBase::OnLootSourceOwnerDestroyed(AActor* destroyed_actor)
{
	if (HasAuthority() && loot_source && destroyed_actor == loot_source->GetOwner())
	{
		ServerSetLootSource(nullptr);
	}
}

void ACharacterBase::OnRep_LootSource()
{
	if (ASurvivalPlayerController* player_character = Cast<ASurvivalPlayerController>(GetController()))
	{
		if (player_character->IsLocalController()) // If local controller is trying to access then open the replicated loot UI
		{
			if (loot_source)
			{
				player_character->ShowLootMenu(loot_source);
			}
			else
			{
				player_character->HideLootMenu();
			}
		}
	}
}

float ACharacterBase::ModifyHealth(const float delta)
{
	const float old_health = health;								// Figure out how much health we have
	
	health = FMath::Clamp<float>(health + delta, 0.f, max_health);	// Modify the health we have

	return health - old_health;										// Get the new health
}

void ACharacterBase::OnRep_Health(float old_health)
{
	OnHealthModified(health - old_health);	// Call BlueprintImplementable event to replicate. 
}

void ACharacterBase::OnSuicide(struct FDamageEvent const& DamageEvent, const AActor* damage_causer)
{
	killer = this;
	OnRep_Killer();
}

void ACharacterBase::KilledByPlayer(struct FDamageEvent const& DamageEvent, class ACharacterBase* character, const AActor* damage_causer)
{
	killer = character;
	OnRep_Killer();
}

void ACharacterBase::OnRep_Killer() 
{
	SetLifeSpan(60.f);

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);
	this->SetReplicateMovement(false);

	loot_player_interaction->Activate();
	
	if (HasAuthority())
	{
		TArray<UEquippableItem*> equippables;
		equipped_items.GenerateValueArray(equippables);

		for (auto& equipped_item : equippables) // unequipped all items
		{
			equipped_item->SetIsEquipped(false);
		}
	}

	if (IsLocallyControlled())
	{
		spring_arm->bUsePawnControlRotation = true;

		if(ASurvivalPlayerController* player_controller = Cast<ASurvivalPlayerController>(GetController()))
		{
			player_controller->ShowDeathScreen(killer);
		}
	}
}

void ACharacterBase::StartBasicAttack()
{

		if(current_primary_weapon)
		{ 
			current_primary_weapon->OnAttackStart();
		}
		if(!current_primary_weapon)
		{
			BeginMeleeAttack();
		}
}

void ACharacterBase::StopBasicAttack()
{

}

void ACharacterBase::BeginMeleeAttack()
{
	if (GetWorld()->TimeSince(last_melee_attack) > melee_attack_montage->GetPlayLength()) // is the time since last attack > the length of the meleee animation
	{

		FHitResult hit_result;
		FCollisionShape shape = FCollisionShape::MakeSphere(15.f); //Make 15 Unit sphere to do trace with 


		FVector start = camera_component->GetComponentLocation();
		FVector forward_vector = camera_component->GetForwardVector();

		FVector trace_start = start + (forward_vector * spring_arm->TargetArmLength);
		FVector trace_end = start + (forward_vector * (melee_attack_distance + spring_arm->TargetArmLength));

		DrawDebugLine(GetWorld(), trace_start, trace_end, FColor::Purple, true, 5.f, 1, 3.f);

		FCollisionQueryParams query_params = FCollisionQueryParams("MeleeSweep", false, this);

		PlayAnimMontage(melee_attack_montage); // Was not playing due to Preblend slot space not being in anim graph. (Will rework later with better animation)

		if (GetWorld()->SweepSingleByChannel(hit_result, trace_start, trace_end, FQuat(), COLLISION_WEAPON, shape, query_params)) // If Line trace hits something
		{
			if (ACharacterBase* hit_player = Cast<ACharacterBase>(hit_result.GetActor())) // Get the person you hit
			{
				if (ASurvivalPlayerController* player_controller = Cast<ASurvivalPlayerController>(GetController()))
				{
					player_controller->OnHitPlayer(); // BlueprintImplementableEvent for when you hit a player (Like show hit marker ect.)
				}
			}
		}

		ServerProcessMeleeHit(hit_result);

		last_melee_attack = GetWorld()->GetTimeSeconds();

	}
}

void ACharacterBase::ServerProcessMeleeHit_Implementation(const FHitResult& melee_hit)
{
		MulticastPlayMeleeFX();

	if (GetWorld()->TimeSince(last_melee_attack) > melee_attack_montage->GetPlayLength() && (GetActorLocation() - melee_hit.ImpactPoint).Size() <= melee_attack_distance)
	{
		UGameplayStatics::ApplyPointDamage(melee_hit.GetActor(), melee_attack_dmg, (melee_hit.TraceStart - melee_hit.TraceEnd).GetSafeNormal(), melee_hit, GetController(), this, UPunchDamage::StaticClass());
	}
		last_melee_attack = GetWorld()->GetTimeSeconds();
}

void ACharacterBase::MulticastPlayMeleeFX_Implementation()
{
	if(!HasAuthority())
	{ 
		PlayAnimMontage(melee_attack_montage);
	}
}

void ACharacterBase::EquipWeapon(class UWeaponItem* weapon_item)
{
	if (HasAuthority() && weapon_item->weapon_class)
	{
		if (current_primary_weapon)
		{
			current_primary_weapon->DeattachFromPawn();
		}

		FActorSpawnParameters spawn_params;
		spawn_params.bNoFail = true;
		spawn_params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		spawn_params.Owner = spawn_params.Instigator = this;

		if (weapon_item->weapon_class)
		{
			if (AWeapon* weapon = GetWorld()->SpawnActor<AWeapon>(weapon_item->weapon_class, GetMesh()->GetSocketLocation("Weapon_R"), GetMesh()->GetSocketRotation("Weapon_R"), spawn_params))
			{
				if (weapon->Owner)
				{
					current_primary_weapon = weapon;
					current_primary_weapon->AttachToPawn();
					current_primary_weapon->item = weapon_item;
				}
			}
		}
	}
}


void ACharacterBase::EquipShield(class UShieldItem* shield_item)
{
	if (HasAuthority() && shield_item->shield_class)
	{
		if (current_shield)
		{
			current_shield->DeattachFromPawn();
		}

		FActorSpawnParameters spawn_params;
		spawn_params.bNoFail = true;
		spawn_params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		spawn_params.Owner = spawn_params.Instigator = this;

		if (shield_item->shield_class)
		{
			if (AShield* shield = GetWorld()->SpawnActor<AShield>(shield_item->shield_class, GetMesh()->GetSocketLocation("ShieldSocket"), GetMesh()->GetSocketRotation("ShieldSocket"), spawn_params))
			{
				if (shield->Owner)
				{
					current_shield = shield;
					current_shield->AttachToPawn();
					current_shield->item = shield_item;
				}
			}
		}
	}
}

void ACharacterBase::UnequipWeapon()
{
	if (HasAuthority())
	{		
		if(current_primary_weapon)
			current_primary_weapon->DeattachFromPawn();
	}
}

void ACharacterBase::UnequipShield()
{
	if (HasAuthority())
	{
		if (current_shield)
			current_shield->DeattachFromPawn();
	}
}

#undef LOCTEXT_NAMESPACE