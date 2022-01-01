
#include "Player/CreationCamera.h"


#include "Containers/Array.h"
#include "Engine/SkeletalMesh.h"

ACreationCamera::ACreationCamera()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACreationCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACreationCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}