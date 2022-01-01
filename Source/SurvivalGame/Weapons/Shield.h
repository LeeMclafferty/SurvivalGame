// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "shield.generated.h"


UENUM(BlueprintType)
enum class EShieldState : uint8
{
	idle,
	attacking,
	equipping,
	uneqipping,
	blocking
};

USTRUCT(BlueprintType)
struct FShieldData // Data about the shield
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = shieldStats)
	float stamina_per_attack;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = shieldStats)
	float attack_speed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = shieldStats)
	float durability;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = shieldStats)
	float crit_chance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = shieldStats)
	TSubclassOf<UDamageType> shield_damage_type;

	FShieldData()
	{
		stamina_per_attack = 20.f;
		attack_speed = 0.2f;
		durability = 100.f;
	}
};

UCLASS()
class SURVIVALGAME_API AShield : public AActor
{
	GENERATED_BODY()

		friend class ACharacterBase;

public:
	AShield();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PostInitializeComponents();
	virtual void BeginPlay() override;
	virtual void Destroyed() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = shieldStats)
		class UStaticMeshComponent* shield_mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = shieldStats)
		class UBoxComponent* collision_box;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = shieldStats)
		class USceneComponent* scene_root;

	FShieldData shield_data;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = shieldStats)
	FName attachment_bone;

	UFUNCTION(BlueprintCallable, Category = "Combat System")
	void OnAttackStart();

	UFUNCTION(BlueprintCallable, Category = "Combat System")
	void OnAttackEnd();

	//Bools for anim bp
	UPROPERTY(VisibleDefaultsOnly, Category = "Trigger Bools")
	bool is_light_attack;

	UPROPERTY(VisibleAnywhere, Category = "Combat system")
	int32 attack_combo;


protected:

	EShieldState shield_state;

	float last_attack;

	UPROPERTY(Replicated, EditDefaultsOnly, Category = "Animations")
	class UAnimMontage* light_attack_anim;

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	class UAnimMontage* heavy_attack_anim;

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	class UAnimMontage* blocking_anim;

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	class UAnimMontage* equip_anim;

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	class UAnimMontage* unequip_anim;

	UPROPERTY(EditDefaultsOnly, Category = "VFX")
	class UCustomNiagaraComponent* swing_vfx;

	UPROPERTY(EditDefaultsOnly, Category = "VFX")
	class UCustomNiagaraComponent* hit_vfx;

	UPROPERTY(EditDefaultsOnly, Category = "VFX")
	class UCustomNiagaraComponent* crit_vfx;

	UPROPERTY(EditDefaultsOnly, Category = "VFX")
	class UCustomNiagaraComponent* resisted_vfx;

	UPROPERTY(EditDefaultsOnly, Category = "VFX")
	class UCustomNiagaraComponent* shield_break_vfx;

	UPROPERTY(EditDefaultsOnly, Category = "SFX")
	class UAudioComponent* swing_sfx;

	UPROPERTY(EditDefaultsOnly, Category = "SFX")
	class UAudioComponent* hit_sfx;

	UPROPERTY(EditDefaultsOnly, Category = "SFX")
	class UAudioComponent* blocked_sfx;

	UPROPERTY(EditDefaultsOnly, Category = "SFX")
	class UAudioComponent* crit_sfx;

	UPROPERTY(EditDefaultsOnly, Category = "SFX")
	class UAudioComponent* resisted_sfx;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly)
	class ACharacterBase* pawn_owner;

	UFUNCTION(BlueprintCallable, Category = "Combat System")
	void OnHit();

	UFUNCTION(BlueprintCallable, Category = "Combat System")
	void OnEquip();

	UFUNCTION(BlueprintCallable, Category = "Combat System")
	void OnUnequip();

	UFUNCTION(BlueprintCallable, Category = "Combat System")
	void AttachToPawn();

	UFUNCTION(BlueprintCallable, Category = "Combat System")
	void DeattachFromPawn();

	UFUNCTION(BlueprintCallable, Category = "Combat System")
	void GetShieldState();

	UFUNCTION(BlueprintCallable, Category = "Combat System")
	void PlayShieldSound();

	UFUNCTION(NetMulticast, unreliable, Category = "Combat System")
	void MulticastPlayShieldAnimation(UAnimMontage* montage);

private:

	UPROPERTY(EditDefaultsOnly, Category = "Combat System") // Need to be replicated I think
	class UShieldItem* item;

};
