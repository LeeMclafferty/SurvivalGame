
#pragma once

#include "CoreMinimal.h"
#include "Items/ItemBase.h"
#include "ConsumableItem.generated.h"


UCLASS()
class SURVIVALGAME_API UConsumableItem : public UItemBase
{
	GENERATED_BODY()

public:

	UConsumableItem();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Healing")
	float heal_amount;
	
	virtual void Use(ACharacterBase* player) override;
};
