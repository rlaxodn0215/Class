// Copyright Epic Games, Inc. All Rights Reserved.


#include "TutorialGameModeBase.h"
#include "Global.h"

ATutorialGameModeBase::ATutorialGameModeBase()
{
	CHelpers::GetClass<APawn>(&DefaultPawnClass, "Blueprint'/Game/Bp_CPlayer.Bp_CPlayer_C'");
}



