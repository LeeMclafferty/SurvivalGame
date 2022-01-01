// copywrite Lee Mclafferty

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LootableActor.generated.h"

UCLASS()
class SURVIVALGAME_API ALootableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ALootableActor();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* loot_container_mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	class UInteractionComponent* loot_interaction_comp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	class UInventoryComponent* loot_inventory;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components") // lootable items that can be rolled into chest
	class UDataTable* loot_data_table;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components") // Random roll to determine what is in the chest
	FIntPoint loot_rolls;


protected:

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnInteract(class ACharacterBase* player);

private:




};
