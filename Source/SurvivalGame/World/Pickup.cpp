
#include "World/Pickup.h"
#include "Components/ActorComponent.h"
#include "Components/InteractionComponent.h"
#include "Components/InventoryComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Items/ItemBase.h"
#include "Items/Itembase.h"
#include "Engine.h"
#include "Net/UnrealNetwork.h"
#include "Engine/ActorChannel.h"
#include "Player/CharacterBase.h"
#include "Player/SurvivalPlayerController.h"

APickup::APickup()
{
	PrimaryActorTick.bCanEverTick = true;

	pickup_mesh = CreateDefaultSubobject<UStaticMeshComponent>("Pickup Mesh");
	pickup_mesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);

	SetRootComponent(pickup_mesh);

	interaction_component = CreateDefaultSubobject<UInteractionComponent>("Interaction Component");
	interaction_component->interaction_time = 0.5f;
	interaction_component->interaction_distance = 200.f;
	interaction_component->interactable_name_text = FText::FromString("Pickup");
	interaction_component->interactable_action_text = FText::FromString("Take");
	interaction_component->on_interact.AddDynamic(this, &APickup::OnTakePickup);
	interaction_component->SetupAttachment(pickup_mesh);

	SetReplicates(true);
}

void APickup::BeginPlay()
{
	Super::BeginPlay();

	if(HasAuthority() && item_template && bNetStartup)
	{
		InitializePickcup(item_template->GetClass(), item_template->GetQuantity());
	}
	
	if (!bNetStartup)
	{
		AlignWithGround();
	}

	if (item)
	{
		item->MarkDirtyForReplication();
	}
}

void APickup::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APickup, item);
}

bool APickup::ReplicateSubobjects(class UActorChannel* Channel, class FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool has_wrote_something = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	if (item && Channel->KeyNeedsToReplicate(item->GetUniqueID(), item->rep_key))
	{
		has_wrote_something |= Channel->ReplicateSubobject(item, *Bunch, *RepFlags);
	}

	return has_wrote_something;
}


void APickup::InitializePickcup(const TSubclassOf<class UItemBase> item_class, const int32 quantity)
{
	if (HasAuthority() && item_class && quantity > 0)
	{
		item = NewObject<UItemBase>(this, item_class);
		item->SetQuantity(quantity);
	  /*GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Yellow, FString::Printf(TEXT("init pickup")));*/

		OnRep_Item();

		item->MarkDirtyForReplication();
	}
}

void APickup::OnRep_Item()
{
	if (item)
	{
		pickup_mesh->SetStaticMesh(item->pickup_mesh);

		interaction_component->interactable_name_text = item->item_display_name;
		item->OnItemModified.AddDynamic(this, &APickup::OnItemModified); //Client binds to this refresh interaction widget
	}
	interaction_component->RefreshWidget();
}

void APickup::OnItemModified()
{
	if(interaction_component)
	{
		interaction_component->RefreshWidget();
	}
}

#if WITH_EDITOR
void APickup::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	FName property_name = (PropertyChangedEvent.Property != NULL) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	if (property_name == GET_MEMBER_NAME_CHECKED(APickup, item_template))
	{
		if (item_template)
		{
			pickup_mesh->SetStaticMesh(item_template->pickup_mesh);
		}

	}
}
#endif

void APickup::OnTakePickup(class ACharacterBase* taker)
{

	if (!taker)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player was not vaild"));
	}

	if (HasAuthority() && !IsPendingKillPending() && item)
	{
		if (UInventoryComponent* player_inventory = taker->player_inventory)
		{
			const FItemAddResult add_result = player_inventory->TryAddItem(item);

			if (add_result.actual_amount_given < item->GetQuantity())
			{
				item->SetQuantity(item->GetQuantity() - add_result.actual_amount_given);

				/*GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Yellow, FString::Printf(TEXT("actual add amount %i"), add_result.actual_amount_given));
				GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Yellow, FString::Printf(TEXT("item->quantity %i"), item->GetQuantity()));*/
			}
			else if (add_result.actual_amount_given >= item->GetQuantity())
			{
				Destroy();
			}

		}
	}
}
