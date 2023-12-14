// Copyright Epic Games, Inc. All Rights Reserved.


#include "TutorialGameModeBase.h"
#include "Global.h"

ATutorialGameModeBase::ATutorialGameModeBase()
{
	CHelpers::GetClass<APawn>(&DefaultPawnClass, "Blueprint'/Game/MyCPlayer.MyCPlayer_C'");
}



