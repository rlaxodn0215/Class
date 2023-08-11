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

void GameManager::CheckCombo(Player * player)
{
    if (m_ComboFlag[0] || m_ComboFlag[1] || m_ComboFlag[2] ||
        m_ComboFlag[3] || m_ComboFlag[4] || m_ComboFlag[5])
    {
        m_TimerCount++;

        if (m_TimerCount >= 10)
        {
            m_TimerCount = 0;
            for (int i = 0; i < 6; i++)
            {
                m_ComboFlag[i] = false;
            }

            cout << "false" << endl;
        }

    }

    if (GetAsyncKeyState(VK_UP) & 0x8000)
    {
        cout << "UP" << endl;
    }

    if (GetAsyncKeyState(VK_DOWN) & 0x8000)
    {
        cout << "DOWN" << endl;
    }

    if (GetAsyncKeyState(VK_LEFT) & 0x8000)
    {
        if(m_ComboFlag[2]==false)
            cout << "LEFT" << endl;
        else
        {
            m_TimerCount = 0;
            cout << "LEFT RUN" << endl;
            
        }
    }

    if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
    {
        if (m_ComboFlag[3] == false)
             cout << "RIGHT" << endl;
        else
        {
            m_TimerCount = 0;
            cout << "RIGHT RUN" << endl;
       
        }
    }

    if (GetAsyncKeyState(0x41) & 0x8000) // a
    {
        cout << "ATTACK" << endl;
    }

    if (GetAsyncKeyState(0x53) & 0x8000) // s
    {
        cout << "JUMP" << endl;
    }
}
