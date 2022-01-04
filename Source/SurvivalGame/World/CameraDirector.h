
#pragma once

#include "Kismet/GameplayStatics.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CameraDirector.generated.h"


UCLASS()
class SURVIVALGAME_API ACameraDirector : public AActor
{
	GENERATED_BODY()
	
public:	
	ACameraDirector();

	void SetViewToCameraOne();
	void SetViewToCameraTwo();

	bool is_first_time_on_main_menu;
	const float smooth_blend_time = 0.75f;

protected:
	virtual void BeginPlay() override;

	float time_to_next_camera_change;

	UPROPERTY(EditAnywhere)
	class AActor* camera_one;

	UPROPERTY(EditAnywhere)
	class AActor* camera_two;



public:	
	virtual void Tick(float DeltaTime) override;

};
