// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/SaveGameBase.h"
#include "Kismet/GameplayStatics.h"

#include "Player/CharacterBase.h"




USaveGameBase::USaveGameBase()
{
	save_slot_name = TEXT("Test Save");
	player_index = 0;
	
}
