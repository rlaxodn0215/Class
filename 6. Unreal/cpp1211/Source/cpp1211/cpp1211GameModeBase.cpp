// Copyright Epic Games, Inc. All Rights Reserved.


#include "cpp1211GameModeBase.h"
#include "Global.h"					// << :

Acpp1211GameModeBase::Acpp1211GameModeBase()
{
	//ConstructorHelpers::FClassFinder<APawn>pawn(L"Blueprint'/Game/BP_CPlayer.BP_CPlayer_C'"); 
	//if(pawn.Succeeded()) {}
	//�������Ʈ ������ ���۷����� �����ö��� _C�� ' ���� �ٿ������


	CHelpers::GetClass<APawn>(&DefaultPawnClass, "Blueprint'/Game/BP_CPlayer.BP_CPlayer_C'");
	//DefaultPawnClass ���� ��ο� �ִ°� �Ҵ��ϰڴٴ� �ǹ�
}