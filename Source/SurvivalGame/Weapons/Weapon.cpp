
#include "Weapons/Weapon.h"
#include "SurvivalGame.h"

#include "Components/StaticMeshComponent.h"
#include "Components/AudioComponent.h"
#include "Components/InventoryComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "Curves/CurveVector.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Net/UnrealNetwork.h"
#include "DrawDebugHelpers.h"
#include "TimerManager.h"

#include "Items/EquippableItem.h"
#include "Weapons/ProjectileBase.h"
#include "Player/CharacterBase.h"
#include "Player/SurvivalPlayerController.h"
#include "Components/CustomNiagaraComponent.h"
#include "Components/InteractionComponent.h"

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PrePhysics;
	bReplicates = true;
	bNetUseOwnerRelevancy = true; 

	scene_root = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Root"));
	RootComponent = scene_root;

	weapon_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon Mesh"));
	weapon_mesh->SetCollisionObjectType(ECC_WorldDynamic);
	weapon_mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	weapon_mesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	weapon_mesh->SetupAttachment(RootComponent);

	collision_box = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	collision_box->SetupAttachment(RootComponent);
	
	swing_vfx = CreateDefaultSubobject<UCustomNiagaraComponent>(TEXT("Swing VFX"));
	hit_vfx = CreateDefaultSubobject<UCustomNiagaraComponent>(TEXT("Hit VFX"));
	crit_vfx = CreateDefaultSubobject<UCustomNiagaraComponent>(TEXT("Crit VFX"));
	resisted_vfx = CreateDefaultSubobject<UCustomNiagaraComponent>(TEXT("Resisted VFX"));
	weapon_break_vfx = CreateDefaultSubobject<UCustomNiagaraComponent>(TEXT("Weapon Shatter VFX"));

	swing_sfx = CreateDefaultSubobject<UAudioComponent>(TEXT("Swing SFX"));
	hit_sfx = CreateDefaultSubobject<UAudioComponent>(TEXT("Hit SFX"));
	blocked_sfx = CreateDefaultSubobject<UAudioComponent>(TEXT("blocked SFX"));
	crit_sfx = CreateDefaultSubobject<UAudioComponent>(TEXT("Crit SFX"));
	resisted_sfx = CreateDefaultSubobject<UAudioComponent>(TEXT("Resisted SFX"));


	attack_combo = 0;
	attachment_bone = FName("Weapon_R");

	
	
}

void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Yellow, FString::Printf(TEXT("Has weapon: %i"), has_weapon));
}



void AWeapon::BeginPlay()
{
	Super::BeginPlay(); // This is begin play for when the weapon is spawned, not for when the game starts.

	if(HasAuthority())
	{ 
		pawn_owner = Cast<ACharacterBase>(GetOwner());
	}

}

void AWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(AWeapon, pawn_owner);
	
}

void AWeapon::Destroyed()
{
	Super::Destroyed();

}


void AWeapon::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

void AWeapon::GetWeaponState()
{

}

void AWeapon::PlayWeaponSound()
{

}

void AWeapon::MulticastPlayWeaponAnimation_Implementation(UAnimMontage* montage)
{
	if (&pawn_owner)
	{
		pawn_owner->PlayAnimMontage(montage);
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Yellow, FString::Printf(TEXT("PlayWeaponAnimation() call")));
	}
}

void AWeapon::AttachToPawn()
{
	if (HasAuthority())
	{
	 if(USkeletalMeshComponent* pawn_mesh = pawn_owner->GetMesh()) 
		{
				this->AttachToComponent(pawn_mesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), attachment_bone);
				GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Yellow, FString::Printf(TEXT("AttachToPawn() WEAPON")));
		}
	}
}

void AWeapon::DeattachFromPawn()
{
	if(HasAuthority())
	{ 
		this->Destroy();
	}
}

void AWeapon::OnEquip()
{

}

void AWeapon::OnUnequip()
{

} 

void AWeapon::OnAttackStart()
{
	if (pawn_owner->GetMesh()->GetAnimInstance()->Montage_IsPlaying(light_attack_anim))
	{
		attack_combo = 1;
	}
	else 
	{
		pawn_owner->GetRootMotionAnimMontageInstance();
		
	}



	//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Yellow, FString::Printf(TEXT("OnAttack() call")));
}

void AWeapon::OnAttackEnd()
{
	is_light_attack = false;
}

void AWeapon::OnHit()
{

}

