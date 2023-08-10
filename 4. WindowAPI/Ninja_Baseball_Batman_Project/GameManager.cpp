#include "GameManager.h"

GameManager::GameManager()
{
	m_SceneNum = 0;
	m_Stage = NULL;
	m_Player = NULL;
	m_Cam = NULL;
}


GameManager::~GameManager()
{
	if(m_Stage !=NULL)
	delete m_Stage;

	if (m_Player != NULL)
	delete m_Player;

	if (m_Cam != NULL)
	delete m_Cam;
}
