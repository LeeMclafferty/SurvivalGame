

#include "World/CameraDirector.h"
#include "Camera/CameraComponent.h"

#include "Player/SurvivalPlayerController.h"

ACameraDirector::ACameraDirector()
{
	PrimaryActorTick.bCanEverTick = true;
	
}

void ACameraDirector::SetViewToCameraOne()
{
	ASurvivalPlayerController* pc = Cast<ASurvivalPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	pc->SetViewTargetWithBlend(camera_one, smooth_blend_time);
}

void ACameraDirector::SetViewToCameraTwo()
{
	ASurvivalPlayerController* pc = Cast<ASurvivalPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	
	pc->SetViewTargetWithBlend(camera_two, smooth_blend_time);
}

void ACameraDirector::BeginPlay()
{
	Super::BeginPlay();

}

void ACameraDirector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*const float time_between_camera_changes = 2.f;
	const float smooth_blend_time = 0.75f;
	time_to_next_camera_change -= DeltaTime;
	
	if (time_to_next_camera_change <= 0.f)
	{
		time_to_next_camera_change += time_between_camera_changes;

		ASurvivalPlayerController* pc = Cast<ASurvivalPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
		if(pc)
		{ 
			if ((pc->GetViewTarget() != camera_one) && (camera_one != nullptr))
			{
				pc->SetViewTarget(camera_one);
			}
			else if ((pc->GetViewTarget() != camera_two) && (camera_two != nullptr))
			{
				pc->SetViewTargetWithBlend(camera_two, smooth_blend_time);
			}
		}

	}*/

}

