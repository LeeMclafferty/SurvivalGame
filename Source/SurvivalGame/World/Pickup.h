
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

UCLASS()
class SURVIVALGAME_API APickup : public AActor
{
	GENERATED_BODY()
	
public:	
	APickup();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	class UItemBase* item_template; // will be used to create the pickup when spawned in

	void InitializePickcup(const TSubclassOf<class UItemBase> item_class, const int32 quantity); // Takes the item_template and constructs to an item 

	UFUNCTION(BlueprintImplementableEvent)
	void AlignWithGround(); //Rotate Pickup to align with ground when dropped. 



protected:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, ReplicatedUsing = OnRep_Item)
	class UItemBase* item;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* pickup_mesh;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	class UInteractionComponent* interaction_component;

	UFUNCTION()
	void OnRep_Item();

	UFUNCTION()
	void OnItemModified();

	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual bool ReplicateSubobjects(class UActorChannel *Channel, class FOutBunch *Bunch, FReplicationFlags *RepFlags) override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	UFUNCTION()
	void OnTakePickup(class ACharacterBase* taker); // When player takes Pickup, add it to the inventory

private:


};
