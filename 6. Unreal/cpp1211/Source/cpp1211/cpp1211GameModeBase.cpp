// Copyright Epic Games, Inc. All Rights Reserved.


#include "cpp1211GameModeBase.h"
#include "Global.h"					// << :

Acpp1211GameModeBase::Acpp1211GameModeBase()
{
	//ConstructorHelpers::FClassFinder<APawn>pawn(L"Blueprint'/Game/BP_CPlayer.BP_CPlayer_C'"); 
	//if(pawn.Succeeded()) {}
	//블루프린트 파일의 레퍼런스를 가져올때는 _C를 ' 전에 붙여줘야함


	CHelpers::GetClass<APawn>(&DefaultPawnClass, "Blueprint'/Game/BP_CPlayer.BP_CPlayer_C'");
	//DefaultPawnClass 에다 경로에 있는걸 할당하겠다는 의미
}