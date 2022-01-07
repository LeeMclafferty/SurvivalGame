
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
	void SetViewToCameraThree();
	void SnapToCameraOne();

	
	const float smooth_blend_time = 2.f;

protected:
	virtual void BeginPlay() override;

	float time_to_next_camera_change;

	UPROPERTY(EditAnywhere)
	class AActor* camera_one;

	UPROPERTY(EditAnywhere)
	class AActor* camera_two;

	UPROPERTY(EditAnywhere)
	class AActor* camera_three;



public:	
	virtual void Tick(float DeltaTime) override;

};
