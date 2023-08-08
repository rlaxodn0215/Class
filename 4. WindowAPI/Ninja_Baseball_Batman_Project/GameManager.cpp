#include "GameManager.h"

GameManager::GameManager()
{
	m_CurStage = NULL;
	m_Player = NULL;
	m_Cam = NULL;
}


GameManager::~GameManager()
{
	if(m_CurStage !=NULL)
	delete m_CurStage;

	if (m_Player != NULL)
	delete m_Player;

	if (m_Cam != NULL)
	delete m_Cam;
}

void GameManager::SetInstance(Stage* curStage, Player* player, Camera* cam)
{
	m_CurStage = curStage;
	m_Player = player;
	m_Cam = cam;
}
