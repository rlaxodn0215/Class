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

void GameManager::ShowTimer(HDC hdc, vector<shared_ptr<Animation>> & timerAni)
{
    int temp = m_Timer / 10;

    int tens = temp / 10;
    int ones = temp % 10;

    if (tens > 0)
    {
        timerAni[tens]->AniPlay(hdc, { 455,65 }, 0, 3.5f);
        timerAni[ones]->AniPlay(hdc, { 515,65 }, 0, 3.5f);
    }

    else
    {
        timerAni[ones]->AniPlay(hdc, { 485,65 }, 0, 3.5f);
    }
    
}

void GameManager::CheckKeyInput(Player * player, int sceneNum)
{
    if (sceneNum == 0)
    {

    }

    else if (sceneNum == 1 && m_SelectFlag==false)
    {
        static int selectNum = 0;

        if (GetAsyncKeyState(VK_LEFT) & 0x8000)
        {
            cout << "LEFT_SELECT" << endl;
            if (selectNum > 0)
                m_Cursor.x = m_SelectPosX[--selectNum];

        }

        if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
        {
            cout << "RIGHT_SELECT" << endl;
            if (selectNum < 3)
                m_Cursor.x = m_SelectPosX[++selectNum];
        }

        if (GetAsyncKeyState(0x41) & 0x8000 || GetAsyncKeyState(0x53) & 0x8000)
        {
            cout << "SELECTED!!" << endl;
            m_SelectFlag = true;
        }

        m_Timer -= 1;
    }

    else if (sceneNum == 2)
    {
        if (m_ComboFlag[0] || m_ComboFlag[1] || m_ComboFlag[2] ||
            m_ComboFlag[3] || m_ComboFlag[4] || m_ComboFlag[5])
        {
            m_ComboTimerCount++;

            if (m_ComboTimerCount >= 10)
            {
                m_ComboTimerCount = 0;
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
            if (m_ComboFlag[2] == false)
                cout << "LEFT" << endl;
            else
            {
                m_ComboTimerCount = 0;
                cout << "LEFT RUN" << endl;

            }
        }

        if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
        {
            if (m_ComboFlag[3] == false)
                cout << "RIGHT" << endl;
            else
            {
                m_ComboTimerCount = 0;
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

        if (m_ComboFlag[4] && m_ComboFlag[5])
        {
            cout << "HOME_RUN" << endl;
        }
    }
}

void GameManager::CheckKeyRelease(WPARAM wParam)
{
    if (wParam == VK_UP)
    {
        cout << "UP_release" << endl;
        m_ComboFlag[0] = true;
    }

    if (wParam == VK_DOWN)
    {
        cout << "DOWN_release" << endl;
        m_ComboFlag[1] = true;
    }

    if (wParam == VK_LEFT)
    {
        cout << "LEFT_release" << endl;
        m_ComboFlag[2] = true;
    }

    if (wParam == VK_RIGHT)
    {
        cout << "RIGHT_release" << endl;
        m_ComboFlag[3] = true;
    }

    if (wParam == 0x41)
    {
        cout << "ATTACK_release" << endl;
        m_ComboFlag[4] = true;
    }

    if (wParam == 0x53)
    {
        cout << "JUMP_release" << endl;
        m_ComboFlag[5] = true;
    }
}
