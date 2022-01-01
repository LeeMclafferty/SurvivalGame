// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

class UEquippableItem;

USTRUCT()
struct FInteractionData // Store data about the interaction 
{
	GENERATED_BODY()	

		FInteractionData()
	{
		viewed_interaction_component = nullptr;
		last_interaction_check_time = 0.f;
		is_interacting = false;
	}

	UPROPERTY()
	class UInteractionComponent* viewed_interaction_component; //current interaction component being looked at

	UPROPERTY()
	float last_interaction_check_time; // the time when last checked for and interactable

	UPROPERTY()
	bool is_interacting;

};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEquippedItemsChanged, const EEquippableSlot, slot, const UEquippableItem*, item);

UCLASS()
class SURVIVALGAME_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ACharacterBase();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Interaction
	bool IsInteracting() const;

	UFUNCTION(BlueprintCallable, Category = "Items")
	void UseItem(class UItemBase* item);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerUseItem(class UItemBase* item);

	UFUNCTION(BlueprintCallable, Category = "Items")
	void DropItem(class UItemBase* item, const int32 quantiy);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerDropItem(class UItemBase* item, const int32 quantity);

	UPROPERTY(EditDefaultsOnly, Category = "Items")
	TSubclassOf<class APickup> pickup_class; // reference to BP_PickupBase

	float GetRemainingInteractTime() const;


	// Components
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	class UInventoryComponent* player_inventory;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	class UInteractionComponent* loot_player_interaction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UCameraComponent* camera_component;

	UPROPERTY(EditAnywhere, Category = "Components")
	class USpringArmComponent* spring_arm;

	UPROPERTY(EditAnywhere, Category = "Components")
	class USkeletalMeshComponent* ears_mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class USkeletalMeshComponent* beard_mesh;

	UPROPERTY(EditAnywhere, Category = "Components")
	class USkeletalMeshComponent* brow_mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class USkeletalMeshComponent* hair_mesh;

	UPROPERTY(EditAnywhere, Category = "Components")
	class UStaticMeshComponent* hat_mesh;

	UPROPERTY(EditAnywhere, Category = "Components")
	class UStaticMeshComponent* weapon_mesh;

	UPROPERTY(EditAnywhere, Category = "Components")
	class UStaticMeshComponent* shield_mesh;

	UPROPERTY(EditAnywhere, Category = "Components")
	class USkeletalMeshComponent* chest_mesh;

	UPROPERTY(EditAnywhere, Category = "Components")
	class USkeletalMeshComponent* shoes_mesh;

	UPROPERTY(EditAnywhere, Category = "Components")
	class USkeletalMeshComponent* bracer_mesh;

	UPROPERTY(EditAnywhere, Category = "Components")
	class UStaticMeshComponent* backpack_mesh;

	UPROPERTY(EditAnywhere, Category = "Components")
	class USkeletalMeshComponent* hands_mesh;

	UPROPERTY(EditAnywhere, Category = "Components")
	class USkeletalMeshComponent* belt_mesh;

	UPROPERTY(EditAnywhere, Category = "Components")
	class USkeletalMeshComponent* legs_mesh;

	UPROPERTY(EditAnywhere, Category = "Components")
	class USkeletalMeshComponent* calves_mesh;

	UPROPERTY(EditAnywhere, Category = "Components")
	class USkeletalMeshComponent* test_mesh;

	UPROPERTY(BlueprintAssignable, Category = "Items")
	FOnEquippedItemsChanged on_equipped_items_changed;


	// Stats
	UPROPERTY(BlueprintReadOnly, Category = "Stats")
	float stamina;\

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "health")
	float max_stamina;

	UPROPERTY(ReplicatedUsing = OnRep_Health, BlueprintReadOnly, Category = "health")
	float health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "health")
	float max_health;


	// Stat Modifiers
	float ModifyHealth(const float delta);

	UFUNCTION()
		void OnRep_Health(float old_health);

	UFUNCTION(BlueprintImplementableEvent)
		void OnHealthModified(const float health_delta);


	// Equippable Items
	bool EquipItem(UEquippableItem* item);
	bool UnEquipItem(UEquippableItem* item);

	void EquipArmor(class UArmorItem* armor);
	void UnequipArmor(const EEquippableSlot slot);

	void EquipWeapon(class UWeaponItem* weapon_item);
	void EquipShield(class UShieldItem* shield_item);
	void UnequipWeapon();
	void UnequipShield();

	UFUNCTION(BlueprintPure)
	class USkeletalMeshComponent* GetSlotSkeletalMeshComponent(const EEquippableSlot slot);

	UFUNCTION(BlueprintPure)
	class UStaticMeshComponent* GetSlotStaticMeshComponent(const EEquippableSlot slot);

	UFUNCTION(BlueprintPure)
	FORCEINLINE TMap<EEquippableSlot, UEquippableItem*> GetEquippedItems() const { return equipped_items; }

	UPROPERTY(BlueprintReadOnly, Category = Mesh)
	TMap<EEquippableSlot, USkeletalMesh*> naked_skeletal_mesh; // Base mesh that will be reset to if clothing is removed. 

	UPROPERTY(BlueprintReadOnly, Category = Mesh)
	TMap<EEquippableSlot, UStaticMesh*> naked_static_mesh; // Base mesh that will be reset to if clothing is removed. 

	UPROPERTY(BlueprintReadOnly, Category = Mesh)
	TMap<EEquippableSlot, USkeletalMeshComponent*> player_skeletal_meshes;

	UPROPERTY(BlueprintReadOnly, Category = Mesh)
	TMap<EEquippableSlot, UStaticMeshComponent*> player_static_meshes;
	
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	class AWeapon* current_primary_weapon;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	class AShield* current_shield;

	// Looting
	UFUNCTION(BlueprintCallable)
	void SetLootSource(class UInventoryComponent* new_loot_source); // inventory being looted

	UFUNCTION(BlueprintPure,Category = "Looting")
	bool IsLooting() const;

	UFUNCTION(BlueprintCallable, Category = "Looting")
	void LootItem(class UItemBase* item_to_give);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerLootItem(class UItemBase* item_to_give);

protected:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Restart() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	// Death
	void OnSuicide(struct FDamageEvent const& DamageEvent, const AActor* damage_causer);
	void KilledByPlayer(struct FDamageEvent const& DamageEvent, class ACharacterBase* character, const AActor* damage_causer);

	UFUNCTION()
	void OnRep_Killer();

	UPROPERTY(ReplicatedUsing = OnRep_Killer)
	class ACharacterBase* killer;

	UFUNCTION(BlueprintImplementableEvent)
	void OnDeath();


	// Basic Attack
	void StartBasicAttack(); // Press LMB
	void StopBasicAttack(); // Release LMB

	void BeginMeleeAttack(); // BeginMeleeAttack() in ref

	UFUNCTION(Server, Reliable)
	void ServerProcessMeleeHit(const FHitResult& melee_hit);

	UFUNCTION(NetMulticast, Unreliable)
	void MulticastPlayMeleeFX();

	UPROPERTY()
	float last_melee_attack;

	UPROPERTY(EditDefaultsOnly, Category = "Melee")
	float melee_attack_distance;

	UPROPERTY(EditDefaultsOnly, Category = "Melee")
	float melee_attack_dmg;

	UPROPERTY(EditDefaultsOnly, Category = "Melee")
	class UAnimMontage* melee_attack_montage;


	// Looting
	UFUNCTION()
	void BeginLootingPlayer(class ACharacterBase* player);

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable)
	void ServerSetLootSource(class UInventoryComponent* new_loot_source);

	UPROPERTY(ReplicatedUsing = OnRep_LootSource, BlueprintReadOnly) // Allow server to replicate the inventory (so client cannot generate them)
	 UInventoryComponent* loot_source;

	UFUNCTION()
	void OnLootSourceOwnerDestroyed(AActor* destroyed_actor);

	UFUNCTION()
	void OnRep_LootSource(); // Help update UI


	// Equippable Items
	UPROPERTY(VisibleAnywhere, Category = "Items")
	TMap<EEquippableSlot, UEquippableItem*> equipped_items; // Track currently equipped items


	// Movment
	void MoveForward(float value);
	void MoveRight(float value);

	void LookUp(float value);
	void Turn(float value);

	void StartCrouch();
	void StopCrouch();


	// Interaction
	void PerformInteractionCheck(); // Main function of interaction system (Preforms line trace and determines if the actor hit is interactable)
	void CouldntFindInteractable();
	void FoundNewInteractable( UInteractionComponent* interactable);

	void BeginInteract();
	void EndInteract();

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerBeginInteract(); //RPC
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerEndInteract(); //RPC

	void Interact();

	FORCEINLINE class UInteractionComponent* GetInteractable() const { return interaction_data.viewed_interaction_component; } // I am lazy and don't want to type interaction_data.viewed_interaction_component x100

	FTimerHandle timerhandle_interact;

	UPROPERTY()
	FInteractionData interaction_data; // Uses created struct to store data about the interaction

	UPROPERTY(EditDefaultsOnly, Category = "Interaction")
	float interaction_check_frequency;

	UPROPERTY(EditDefaultsOnly, Category = "Interaction")
	float interaction_check_distance;


private:	
	


};
