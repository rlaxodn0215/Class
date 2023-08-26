#include "GameManager.h"

extern bool PlayerEternal;
extern bool PlayerNoHitAni;

GameManager::GameManager()
{
    ///
	m_SceneNum = 2;
    m_Scene = &GameManager::PlayScene;
    ///
	m_Player = NULL;
}

GameManager::~GameManager()
{

}

void GameManager::TitleScene(HWND hWnd, HDC hdc, DataManager * dataManager) // SceneNum = 0
{
    if (m_Start)
    {
        dataManager->GetInstance()->LoadSceneDatas(m_SceneNum, hWnd);
        dataManager->m_Sounds["Title_sound"]->PlayAudio();
        m_Start = false;
    }

    if (totalFrame == 0) totalFrame = dataManager->m_Animations["Title_screen"]->GetFrameTotalCount();
    if (!(m_TimerFrame % 40))
        if (curFrame < totalFrame - 1) curFrame++;
        else curFrame = 0;

    dataManager->m_Animations["Title_screen"]->AniPlay(hdc, { dataManager->m_Animations["Title_screen"]->GetPivots()[0].x + 35,
        dataManager->m_Animations["Title_screen"]->GetPivots()[0].y}, curFrame, 1.55f, 1.55f, true, m_WinRect);

    
}

void GameManager::SelectScene(HWND hWnd, HDC hdc, DataManager* dataManager) // SceneNum = 1
{
    if (m_Start)
    {
        dataManager->LoadSceneDatas(m_SceneNum, hWnd);
        dataManager->m_Sounds["Select_BGM"]->PlayAudio();
        m_Start = false;
    }

    string name[4] = { "Jose", "Ryno", "Roger", "Straw" };
    int xOffset[4] = { 20,262,507,750 };

    for (int i = 20; i <= 900; i += 30) // Background
    {
        for (int j = 0; j <= 630; j += 35)
        {
            dataManager->m_Animations["Select_background"]->AniPlay(hdc, { dataManager->m_Animations["Select_background"]->GetPivots()[0].x + i,
                dataManager->m_Animations["Select_background"]->GetPivots()[0].y + j}, 0, 1.55f, 1.55f, true, m_WinRect);
        }
    }

    if (!m_SelectFlag && m_SelectTimer > 0)
    {
        if (totalFrame == 0) totalFrame = dataManager->m_Animations["1P_select"]->GetFrameTotalCount();
        if (curFrame < totalFrame - 1) curFrame++;
        else curFrame = 0;

        dataManager->m_Animations["1P_select"]->AniPlay(hdc, m_Cursor, curFrame, 3.0f, 3.0f, true, m_WinRect);

        for (int i = 0; i < 4; i++)
        {
            //string temp = name[i] + "_select";
            dataManager->m_Animations[ name[i] + "_select"]->AniPlay(hdc, { dataManager->m_Animations[ name[i] + "_select"]->GetPivots()[0].x + xOffset[i],
                dataManager->m_Animations[name[i] + "_select"]->GetPivots()[0].y + 250 }, 0, 3.0f, 3.0f, true, m_WinRect);
        }

        ShowTimer(hdc, dataManager->m_Number_ani);
    }

    else
    {
        for (int i = 0; i < 4; i++)
        {
            if (m_Cursor.x == m_SelectPosX[i])
            {
                dataManager->m_Animations[name[i] + "_selected"]->AniPlay(hdc, { dataManager->m_Animations[name[i] + "_selected"]->GetPivots()[0].x + xOffset[i],
                    dataManager->m_Animations[name[i] + "_selected"]->GetPivots()[0].y + 150 }, 0, 3.0f, 3.0f, true, m_WinRect);
                continue;
            }
            dataManager->m_Animations[name[i] + "_select"]->AniPlay(hdc, { dataManager->m_Animations[name[i] + "_select"]->GetPivots()[0].x + xOffset[i],
                dataManager->m_Animations[name[i] + "_select"]->GetPivots()[0].y + 250 }, 0, 3.0f, 3.0f, true, m_WinRect);
        }

    }

    for (int i = 0; i < 4; i++)
    {
        dataManager->m_Animations[name[i] + "_tag"]->AniPlay(hdc, { dataManager->m_Animations[name[i] + "_tag"]->GetPivots()[0].x
            + xOffset[i],dataManager->m_Animations[name[i] + "_tag"]->GetPivots()[0].y + 560}, 0, 3.0f, 3.0f, true, m_WinRect);
    }

    dataManager->m_Animations["Player_select_deco"]->AniPlay(hdc, { dataManager->m_Animations["Player_select_deco"]->GetPivots()[0].x + 50,dataManager->m_Animations["Player_select_deco"]->GetPivots()[0].y + 65 }, 0, 3.0f, 3.0f, true, m_WinRect);
    dataManager->m_Animations["Player"]->AniPlay(hdc, { dataManager->m_Animations["Player"]->GetPivots()[0].x + 120, dataManager->m_Animations["Player"]->GetPivots()[0].y + 40 }, 0, 3.0f, 3.0f, true, m_WinRect);
    dataManager->m_Animations["Select"]->AniPlay(hdc, { dataManager->m_Animations["Select"]->GetPivots()[0].x + 600, dataManager->m_Animations["Select"]->GetPivots()[0].y + 40 }, 0, 3.0f, 3.0f, true, m_WinRect);
    dataManager->m_Animations["Player_select_deco"]->AniPlay(hdc, { dataManager->m_Animations["Player_select_deco"]->GetPivots()[0].x + 920, dataManager->m_Animations["Player_select_deco"]->GetPivots()[0].y + 65 }, 0, 3.0f, 3.0f, true, m_WinRect);

}

void GameManager::PlayScene(HWND hWnd, HDC hdc, DataManager* dataManager) // SceneNum = 2
{
    if (m_Start)
    {
        dataManager->LoadSceneDatas(m_SceneNum, hWnd);
        dataManager->LoadWaveDatas(hWnd, m_WinRect, m_Wave);
        dataManager->LoadPlayerDatas(hWnd, m_Player);
        dataManager->m_Sounds["PlayScene_BGM"]->LoopAudio();
        m_Start = false;
    }
    
    ShowBackStage(hdc, dataManager);
    CharactorUpdate(hdc, m_TimerFrame);
    ShowUI(hdc,dataManager);

}

void GameManager::EndingScene(HWND hWnd, HDC hdc,  DataManager* dataManager) // SceneNum = 3
{
    if (m_Start)
    {
        dataManager->LoadSceneDatas(m_SceneNum, hWnd);
        dataManager->m_Sounds["Ending"]->LoopAudio();
        m_Start = false;
    }

    ShowBackStage(hdc, dataManager);

    if (m_ShowLetter[0] && m_ShowLetter[1] && m_ShowLetter[2])
    {
        ShowRanking(hdc,dataManager);
    }

    else
    {
        //GAME OVER
        char gameOver[8] = { 'G', 'A', 'M', 'E', 'O', 'V','E','R' };

        for (int i = 0; i < 4; i++)
        {
            string temp = "Blue_";
            temp.push_back(gameOver[i]);
            dataManager->m_Animations[temp]->AniPlay(hdc, { dataManager->m_Animations[temp]->GetPivots()[0].x + 70 + 100*i,
                dataManager->m_Animations[temp]->GetPivots()[0].y + 110 }, 0, 5.0f, 5.0f, true, m_WinRect);
        }

        for (int i = 4; i < 8; i++)
        {
            string temp = "Blue_";
            temp.push_back(gameOver[i]);
            dataManager->m_Animations[temp]->AniPlay(hdc, { dataManager->m_Animations[temp]->GetPivots()[0].x + 150 + 100 * i,
               dataManager->m_Animations[temp]->GetPivots()[0].y + 110 }, 0, 5.0f, 5.0f, true, m_WinRect);
        }

        //SCORE
        char score[5] = { 'S', 'C', 'O', 'R', 'E'};

        for (int i = 0; i < 5; i++)
        {
            string temp = "Orange_";
            temp.push_back(score[i]);
            dataManager->m_Animations[temp]->AniPlay(hdc, { dataManager->m_Animations[temp]->GetPivots()[0].x + 150 + 60*i,
                dataManager->m_Animations[temp]->GetPivots()[0].y + 260 }, 0, 3.5f, 3.5f, true, m_WinRect);
        }

        dataManager->m_Animations["Orange_dash"]->AniPlay(hdc, { dataManager->m_Animations["Orange_dash"]->GetPivots()[0].x + 450,
                dataManager->m_Animations["Orange_dash"]->GetPivots()[0].y + 260 }, 0, 3.5f, 3.5f, true, m_WinRect);

        ShowPlayerPoints(hdc, { 800,270 },dataManager, 3.5f, 3.5f, 12345, 60);

        MakeName(hdc,dataManager);
    }

}

void GameManager::ShowTimer(HDC hdc, vector<shared_ptr<Animation>> & timerAni)
{
    int temp = m_SelectTimer / 10;

    int tens = temp / 10;
    int ones = temp % 10;

    if (tens > 0)
    {
        timerAni[tens]->AniPlay(hdc, { 440,65 }, 0, 3.5f, 3.5f, true, m_WinRect);
        timerAni[ones]->AniPlay(hdc, { 515,65 }, 0, 3.5f, 3.5f, true, m_WinRect);
    }

    else
    {
        timerAni[ones]->AniPlay(hdc, { 477,65 }, 0, 3.5f, 3.5f, true, m_WinRect);
    }
    
}

void GameManager::Gravity(int g)
{
   if (m_Player->GetVel().m_Y <= 30 && m_Player->GetPos().m_Y <= m_Player->GetPos().m_Z)
   {
       if(m_Player->GetTakeGravity())
            m_Player->SetVel(m_Player->GetVel() + Vector3(0,g,0));
   } 
}

void GameManager::CheckKeyInput(HWND hWnd, HDC hdc, DataManager * dataManager)
{
    if (m_SceneNum == 1)
    {

        if (GetAsyncKeyState(VK_LEFT) & 0x8000 && !m_SelectFlag)
        {
            if (m_SelectNum > 0 && !m_KeyFlag[2])
            {
                m_Cursor.x = m_SelectPosX[--m_SelectNum];
                m_KeyFlag[2] = true;
            }

        }

        if (GetAsyncKeyState(VK_RIGHT) & 0x8000 && !m_SelectFlag)
        {
            if (m_SelectNum < 3 && !m_KeyFlag[3])
            {
                m_Cursor.x = m_SelectPosX[++m_SelectNum];
                m_KeyFlag[3] = true;
            }
        }

        if (GetAsyncKeyState(0x41) & 0x8000 || GetAsyncKeyState(0x53) & 0x8000 && !m_SelectFlag)
        {
            m_SelectTimer = 0;
            dataManager->m_Sounds["Selected_sound"]->PlayAudio();
            m_SelectFlag = true;
        }

        if (m_SelectTimer <= -20)
        {
            m_SceneNum++;
            m_Scene = &GameManager::PlayScene;
            m_Start = true;
        }

        m_SelectTimer--;
    }

    else if (m_SceneNum == 2)
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
            }

        }

        if (m_Player->GetCurHP() > 0)
        {
            if (!m_Player->GetStopMove()) // 움직일 수 없는 애니 작동 여부
            {
                if (!m_Player->GetJumping() && !m_PlayerDynamite) // 점프와 필살기 사용 안 할때
                {
                    m_Player->Idle();
                    m_Player->SetVel(Vector3(0, 0, 0));
                    //cout << "Player Idle" << endl;
                }

                if (GetAsyncKeyState(VK_UP) & 0x8000 && !m_KeyFlag[4] && !m_PlayerDynamite) //공격 X, 필살기 X
                {
                    m_KeyFlag[0] = true;

                    if (!m_Player->GetJumping())
                    {
                        m_Player->SetVel(Vector3(0, -m_Player->GetMoveSpeed() / 1.5f, -m_Player->GetMoveSpeed() / 1.5f));
                        m_Player->Move();
                    }
                }

                if (GetAsyncKeyState(VK_DOWN) & 0x8000 && !m_KeyFlag[4] && !m_PlayerDynamite)
                {
                    m_KeyFlag[1] = true;

                    if (!m_Player->GetJumping())
                    {
                        m_Player->SetVel(Vector3(0, m_Player->GetMoveSpeed() / 1.5f, m_Player->GetMoveSpeed() / 1.5f));
                        m_Player->Move();
                    }
                }

                if (GetAsyncKeyState(VK_LEFT) & 0x8000 && !m_KeyFlag[4])
                {
                    m_KeyFlag[2] = true;
                    m_Player->SetLookRight(false);

                    if (m_ComboFlag[2] == false)
                    {
                        if (!m_PlayerDynamite)
                        {
                            m_Player->SetVel(Vector3(-m_Player->GetMoveSpeed(), m_Player->GetVel().m_Y, m_Player->GetVel().m_Z));

                            if (!m_Player->GetJumping())
                                m_Player->Move();
                        }
                    }
                    else
                    {
                        m_ComboTimerCount = 0;

                        if (!m_PlayerDynamite)
                        {
                            m_Player->SetVel(Vector3(-m_Player->GetMoveSpeed() * 2, m_Player->GetVel().m_Y, m_Player->GetVel().m_Z));

                            if (!m_Player->GetJumping())
                                m_Player->Run();
                        }
                    }
                }

                if (GetAsyncKeyState(VK_RIGHT) & 0x8000 && !m_KeyFlag[4])
                {
                    m_KeyFlag[3] = true;
                    m_Player->SetLookRight(true);

                    if (m_ComboFlag[3] == false)
                    {
                        if (!m_PlayerDynamite)
                        {
                            m_Player->SetVel(Vector3(m_Player->GetMoveSpeed(), m_Player->GetVel().m_Y, m_Player->GetVel().m_Z));

                            if (!m_Player->GetJumping())
                                m_Player->Move();
                        }
                    }
                    else
                    {
                        m_ComboTimerCount = 0;
                        if (!m_PlayerDynamite)
                        {
                            m_Player->SetVel(Vector3(m_Player->GetMoveSpeed() * 2, m_Player->GetVel().m_Y, m_Player->GetVel().m_Z));

                            if (!m_Player->GetJumping())
                                m_Player->Run();
                        }
                    }
                }
            }

            if (m_Player->GetStatus() != DAMAGED)
            {
                if (m_ComboFlag[4] && m_ComboFlag[5] && !m_PlayerDynamite)
                {
                    m_Player->HomeRun(hdc,m_WinRect,m_KeyFlag[5]);
                    m_Player->SetAttack(15);

                    if (m_Player->GetLookRight())
                        m_Player->SetPos(m_Player->GetPos() + Vector3(10, 0, 0));
                    else
                        m_Player->SetPos(m_Player->GetPos() + Vector3(-10, 0, 0));

                    m_Player->SetStopMove(true);
                    m_KeyFlag[5] = false;
                    m_Player->SetJumping(false);
                }

                else if (GetAsyncKeyState(0x53) & 0x8000 || (m_Player->GetJumping() && !m_KeyFlag[4]) && !m_PlayerDynamite) // s
                {
                    m_KeyFlag[5] = true;
                    m_Player->Jump(m_KeyFlag[5], m_Player->GetJumping());
                }

                if (!m_Player->GetJumping())
                {
                    if (GetAsyncKeyState(0x41) & 0x8000 && !m_PlayerDynamite) // a
                    {
                        m_KeyFlag[4] = true;
                        m_Player->SetAttack(10);
                        m_Player->SetStopMove(true);
                        m_Player->SetVel(Vector3(0, 0, 0));
                        m_Player->Attack(m_Player->GetLookRight());

                    }
                }

                if (m_ComboFlag[0] && m_ComboFlag[1] && m_ComboFlag[5] || m_PlayerDynamite)
                {
                    m_PlayerDynamite = true;
                    m_Player->SetTakeGravity(false);
                    m_Player->Dynamite(hdc, m_TimerFrame, m_WinRect, m_PlayerDynamite);
                }
            }
        }

        else
        {
            m_Player->SetVel({ 0,0,0 });
            m_Player->Dead();
            m_Player->SetDeadTimer(m_Player->GetDeadTimer()+1);
            if (m_Player->GetDeadTimer() >= 30)
            {
                m_Player->SetAlive(false);
                m_Wave->StageFinish = true;
                m_SceneNum++;
                m_Scene = &GameManager::EndingScene;
                m_Start = true;
            }

        }
    }
}

void GameManager::ShowBackStage(HDC hdc, DataManager * dataManager)
{
    static int pos_X = 0; // startOffset 설정
    static int pos_Y = 0;
    static bool down = true;

    if (pos_X > -3 * dataManager->m_Animations["Background1_BackStage"]->GetWidths()[0]) pos_X -= 40;
    else pos_X = 0;

    if (down)
    {
        if (pos_Y >= -(3 * dataManager->m_Animations["Background1_BackStage"]->GetHeights()[0] - m_WinRect.bottom / 2))
            pos_Y -= 2;
        else
            down = false;

    }

    else
    {
        if (pos_Y <= 0)
            pos_Y += 2;
        else
            down = true;
    }

    dataManager->m_Animations["Background1_BackStage"]->AniPlay(hdc, { pos_X + dataManager->m_Animations["Background1_BackStage"]->GetPivots()[0].x, pos_Y +
        dataManager->m_Animations["Background1_BackStage"]->GetPivots()[0].y}, 0, 3.0f, 3.0f, true, m_WinRect);
    dataManager->m_Animations["Background1_BackStage"]->AniPlay(hdc, { pos_X + dataManager->m_Animations["Background1_BackStage"]->GetPivots()[0].x +
        3 * dataManager->m_Animations["Background1_BackStage"]->GetWidths()[0], pos_Y
        + dataManager->m_Animations["Background1_BackStage"]->GetPivots()[0].y }, 0, 3.0f, 3.0f, true, m_WinRect);

    dataManager->m_Animations["Stage_6_boss"]->AniPlay(hdc, { dataManager->m_Animations["Stage_6_boss"]->GetPivots()[0].x,
        dataManager->m_Animations["Stage_6_boss"]->GetPivots()[0].y - 3 }, 0, 3.0f, 3.0f, true, m_WinRect);

}

void GameManager::CheckKeyRelease(HWND hWnd, WPARAM wParam, DataManager * dataManager)
{
    if (m_SceneNum == 0)
    {
        m_Start = true;
        m_SceneNum++;
        m_Scene = &GameManager::SelectScene;
    }

    else if (m_SceneNum==1 || m_SceneNum == 2)
    {
        if (wParam == VK_UP)
        {
            if(m_SceneNum == 2)
                m_ComboFlag[0] = true;
            m_KeyFlag[0] = false;
        }

        if (wParam == VK_DOWN)
        {
            if (m_SceneNum == 2)
                m_ComboFlag[1] = true;
            m_KeyFlag[1] = false;
        }

        if (wParam == VK_LEFT)
        {
            if (m_SceneNum == 2)
                m_ComboFlag[2] = true;
            m_KeyFlag[2] = false;
        }

        if (wParam == VK_RIGHT)
        {
            if (m_SceneNum == 2)
                m_ComboFlag[3] = true;
            m_KeyFlag[3] = false;
        }

        if (wParam == 0x41) // attack
        {
            if (m_SceneNum == 2)
                m_ComboFlag[4] = true;
            m_KeyFlag[4] = false;
        }

        if (wParam == 0x53) // jump
        {
            if (m_SceneNum == 2)
                m_ComboFlag[5] = true;
        }
    }

    else if (m_SceneNum == 3)
    {
        if (m_FirstPush)
        {
            m_FirstPush = false;
        }
        else
        {
            if (wParam == VK_UP || wParam == VK_RIGHT)
            {

                if (m_NameCount < 25)
                {
                    m_NameCount++;
                }
                else
                {
                    m_NameCount = 0;
                }

                m_Name[m_NameCursor] = m_NameCount + 'A';
            }

            else if (wParam == VK_DOWN || wParam == VK_LEFT)
            {

                if (m_NameCount > 0)
                {
                    m_NameCount--;
                }
                else
                {
                    m_NameCount = 25;
                }

                m_Name[m_NameCursor] = m_NameCount + 'A';
            }

            else
            {
                if (m_NameCursor < 2)
                {
                    m_ShowLetter[m_NameCursor++] = true;
                    m_NameCount = 0;
                    m_FirstPush = true;
                }
                else
                {
                    for(int i = 0; i < 4;i++)
                        dataManager->m_PlayerData.name[i] = m_Name[i];
                    dataManager->m_PlayerData.score = m_Player->GetPoints();
                    dataManager->MakeRanking(_T("PlayerRankings.txt"));
                    m_ShowLetter[m_NameCursor] = true;

                }
            }

        }

    }
    
}

void GameManager::ShowUI(HDC hdc, DataManager * dataManager)
{
    // UI
    if (m_Player->GetCurHP() > m_Player->GetMaxHP() * 0.35f)
    {
        dataManager->m_Animations["Player_picture_normal"]->AniPlay(hdc, { dataManager->m_Animations["Player_picture_normal"]->GetPivots()[0].x + 25,
           dataManager->m_Animations["Player_picture_normal"]->GetPivots()[0].y + 34 }, 0, 3.0f, 3.0f, true, m_WinRect);
    }
    else
    {
        if (!(m_TimerFrame % 5)) m_SelectFlag = !m_SelectFlag; //변수 재활용
        dataManager->m_Animations["Player_picture_hurt"]->AniPlay(hdc, { dataManager->m_Animations["Player_picture_hurt"]->GetPivots()[0].x + 25,
       dataManager->m_Animations["Player_picture_hurt"]->GetPivots()[0].y + 34 }, m_SelectFlag, 3.0f, 3.0f, true, m_WinRect);
    }

    dataManager->m_Animations["Player_picture_frame"]->AniPlay(hdc, { dataManager->m_Animations["Player_picture_frame"]->GetPivots()[0].x + 20,
        dataManager->m_Animations["Player_picture_frame"]->GetPivots()[0].y + 10 }, 0, 3.0f, 3.0f, true, m_WinRect);

    dataManager->m_Animations["Player_hpbar_empty"]->AniPlay(hdc, { dataManager->m_Animations["Player_hpbar_empty"]->GetPivots()[0].x + 100,
         dataManager->m_Animations["Player_hpbar_empty"]->GetPivots()[0].y + 80 }, 0, 3.0f, 3.0f, true, m_WinRect);

    ShowPlayerHP(hdc, dataManager->m_Animations["Player_hpbar_full"], { dataManager->m_Animations["Player_hpbar_full"]->GetPivots()[0].x + 105,
       dataManager->m_Animations["Player_hpbar_full"]->GetPivots()[0].y + 80 }, 3.0f, 3.0f,(float)(m_Player->GetMaxHP() - m_Player->GetCurHP())/ m_Player->GetMaxHP());

    ShowPlayerPoints(hdc, { 225,55 },dataManager, 3.0f, 3.0f, m_Player->GetPoints(),25);


}

void GameManager::ShowPlayerHP(HDC hdc, shared_ptr<Animation> hpBar , POINT offset_location, float imageRatioWidth, float imageRatioHeight, float hpRatio)
{
    int bx = hpBar->GetWidths()[0];
    int by = hpBar->GetHeights()[0];
    int xStart = hpBar->GetOffsets()[0].x;
    int yStart = hpBar->GetOffsets()[0].y;
    int posX = offset_location.x - hpBar->GetPivots()[0].x;
    int posY = offset_location.y - hpBar->GetPivots()[0].y;

     HDC hMemDC;
     HBITMAP holdBitmap;

     hMemDC = CreateCompatibleDC(hdc);
     holdBitmap = (HBITMAP)SelectObject(hMemDC, hpBar->GetResourceSprite()->GetSpriteImage());

     TransparentBlt(hdc, posX, posY, (int)((1 - hpRatio) * bx * imageRatioWidth), (int)(by * imageRatioHeight), hMemDC, xStart + hpRatio * bx, yStart,
         (1 - hpRatio) * bx, by, RGB(hpBar->GetResourceSprite()->GetTransparentColor().m_X, hpBar->GetResourceSprite()->GetTransparentColor().m_Y,
             hpBar->GetResourceSprite()->GetTransparentColor().m_Z));

     SelectObject(hMemDC, holdBitmap);
     DeleteDC(hMemDC);

}

void GameManager::ShowPlayerPoints(HDC hdc, POINT offset_location, DataManager* dataManager, float imageRatioWidth, float imageRatioHeight, const int points, int distance)
{
    int number[5];
    int temp = points;
    int showNum = 4;

    for (int i = 0; i < 5; i++)
    {
        number[i] = temp % 10;
        temp /= 10;
    }

    for (int i = 4; i >=0; i--)
    {
        if (number[i] == 0) showNum--;
        else break;
    }

    if (showNum < 0) showNum = 0;

    for (int i = 0; i <= showNum; i++)
    {
        int bx = dataManager->m_Number_ani[number[i]]->GetWidths()[0];
        int by = dataManager->m_Number_ani[number[i]]->GetHeights()[0];
        int xStart = dataManager->m_Number_ani[number[i]]->GetOffsets()[0].x;
        int yStart = dataManager->m_Number_ani[number[i]]->GetOffsets()[0].y;
        int posX = offset_location.x - dataManager->m_Number_ani[number[i]]->GetPivots()[0].x;
        int posY = offset_location.y - dataManager->m_Number_ani[number[i]]->GetPivots()[0].y;

        HDC hMemDC;
        HBITMAP holdBitmap;

        hMemDC = CreateCompatibleDC(hdc);
        holdBitmap = (HBITMAP)SelectObject(hMemDC, dataManager->m_Number_ani[number[i]]->GetResourceSprite()->GetSpriteImage());

        TransparentBlt(hdc, posX - distance *i, posY, (int)( bx * imageRatioWidth), (int)(by * imageRatioHeight), hMemDC, xStart, yStart,
             bx, by, RGB(dataManager->m_Number_ani[number[i]]->GetResourceSprite()->GetTransparentColor().m_X, dataManager->m_Number_ani[number[i]]->GetResourceSprite()->GetTransparentColor().m_Y,
                 dataManager->m_Number_ani[number[i]]->GetResourceSprite()->GetTransparentColor().m_Z));

        SelectObject(hMemDC, holdBitmap);
        DeleteDC(hMemDC);
    }
}

void GameManager::MakeName(HDC hdc, DataManager* dataManager)
{
    int xOffset2 = 10;
    int yOffset2 = 10;

    if (m_NameCursor == 0)
    {
        if (m_FirstPush)
        {
            dataManager->m_Animations["Green_Underbar"]->AniPlay(hdc, { dataManager->m_Animations["Green_Underbar"]->GetPivots()[0].x + 350 + xOffset2,
                dataManager->m_Animations["Green_Underbar"]->GetPivots()[0].y + 420 + yOffset2 }, 0, 5.0f, 5.0f, true, m_WinRect);
        }

        else
        {
            dataManager->m_Alpha_ani[m_NameCount]->AniPlay(hdc, { dataManager->m_Alpha_ani[m_NameCount]->GetPivots()[0].x + 350 + xOffset2,
            dataManager->m_Alpha_ani[m_NameCount]->GetPivots()[0].y + 420 + yOffset2 }, 0, 5.0f, 5.0f, true, m_WinRect);
        }
    }

    else if (m_NameCursor == 1)
    {
        if (m_FirstPush)
        {
            dataManager->m_Animations["Green_Underbar"]->AniPlay(hdc, { dataManager->m_Animations["Green_Underbar"]->GetPivots()[0].x + 450 + xOffset2,
               dataManager->m_Animations["Green_Underbar"]->GetPivots()[0].y + 420 + yOffset2 }, 0, 5.0f, 5.0f, true, m_WinRect);
        }

        else
        {
            dataManager->m_Alpha_ani[m_NameCount]->AniPlay(hdc, { dataManager->m_Alpha_ani[m_NameCount]->GetPivots()[0].x + 450 + xOffset2,
            dataManager->m_Alpha_ani[m_NameCount]->GetPivots()[0].y + 420 + yOffset2 }, 0, 5.0f, 5.0f, true, m_WinRect);

        }
    }

    else if(m_NameCursor == 2)
    {
        if (m_FirstPush)
        {
            dataManager->m_Animations["Green_Underbar"]->AniPlay(hdc, { dataManager->m_Animations["Green_Underbar"]->GetPivots()[0].x + 550 + xOffset2,
               dataManager->m_Animations["Green_Underbar"]->GetPivots()[0].y + 420 + yOffset2 }, 0, 5.0f, 5.0f, true, m_WinRect);
        }

        else
        {
            dataManager->m_Alpha_ani[m_NameCount]->AniPlay(hdc, { dataManager->m_Alpha_ani[m_NameCount]->GetPivots()[0].x + 550 + xOffset2,
           dataManager->m_Alpha_ani[m_NameCount]->GetPivots()[0].y + 420 + yOffset2 }, 0, 5.0f, 5.0f, true, m_WinRect);
        }
    }

    if (m_ShowLetter[0])
    {
        dataManager->m_Alpha_ani[m_Name[0] - 'A']->AniPlay(hdc, { dataManager->m_Alpha_ani[m_Name[0] - 'A']->GetPivots()[0].x + 350 + xOffset2,
           dataManager->m_Alpha_ani[m_Name[0] - 'A']->GetPivots()[0].y + 420 + yOffset2 }, 0, 5.0f, 5.0f, true, m_WinRect);

        if (m_ShowLetter[1])
        {
            dataManager->m_Alpha_ani[m_Name[1] - 'A']->AniPlay(hdc, { dataManager->m_Alpha_ani[m_Name[1] - 'A']->GetPivots()[0].x + 450 + xOffset2,
                dataManager->m_Alpha_ani[m_Name[1] - 'A']->GetPivots()[0].y + 420 + yOffset2 }, 0, 5.0f, 5.0f, true, m_WinRect);

            if (m_ShowLetter[2])
            {
                dataManager->m_Alpha_ani[m_Name[2] - 'A']->AniPlay(hdc, { dataManager->m_Alpha_ani[m_Name[2] - 'A']->GetPivots()[0].x + 550 + xOffset2,
                    dataManager->m_Alpha_ani[m_Name[2] - 'A']->GetPivots()[0].y + 420 + yOffset2 }, 0, 5.0f, 5.0f, true, m_WinRect);
            }
        }

    }

}

void GameManager::ShowRanking(HDC hdc, DataManager* dataManager)
{

    char title[13] = { 'R','A','N','K','S','C','O','R','E','N','A','M','E' };

    for (int i = 0; i < 4; i++) //RANK
    {
        string temp = "Pink_";
        temp.push_back(title[i]);
        dataManager->m_Animations[temp]->AniPlay(hdc, { dataManager->m_Animations[temp]->GetPivots()[0].x + 20 + 50 * i,
            dataManager->m_Animations[temp]->GetPivots()[0].y + 100 }, 0, 2.5f, 2.5f, true, m_WinRect);
    }

    for (int i = 4; i < 9;i++ ) //SCORE
    {
        string temp = "Pink_";
        temp.push_back(title[i]);
        dataManager->m_Animations[temp]->AniPlay(hdc, { dataManager->m_Animations[temp]->GetPivots()[0].x + 180 + 50 * i,
            dataManager->m_Animations[temp]->GetPivots()[0].y + 100 }, 0, 2.5f, 2.5f, true, m_WinRect);
    }

    for (int i = 9; i < 13; i++) //NAME
    {
        string temp = "Pink_";
        temp.push_back(title[i]);
        dataManager->m_Animations[temp]->AniPlay(hdc, { dataManager->m_Animations[temp]->GetPivots()[0].x + 310 + 50 * i,
            dataManager->m_Animations[temp]->GetPivots()[0].y + 100 }, 0, 2.5f, 2.5f, true, m_WinRect);
    }



    for (int i = 0; i < dataManager->m_RankingDatas.size(); i++)
    {
        dataManager->m_Number_ani[10 + i]->AniPlay(hdc, { dataManager->m_Number_ani[10 + i]->GetPivots()[0].x + 70,
        dataManager->m_Number_ani[10 + i]->GetPivots()[0].y + 200 + 100*i }, 0, 3.5f, 3.5f, true, m_WinRect);

        ShowPlayerPoints(hdc, { 570 , 210 + 100 * i },dataManager, 3.0f, 3.0f, dataManager->m_RankingDatas[i].score, 55);

        dataManager->m_Alpha_ani[dataManager->m_RankingDatas[i].name[0] - 'A']->AniPlay(hdc, { dataManager->m_Alpha_ani[dataManager->m_RankingDatas[i].name[0] - 'A']->GetPivots()[0].x + 720,
                dataManager->m_Alpha_ani[dataManager->m_RankingDatas[i].name[0] - 'A']->GetPivots()[0].y + 195 + 100 * i }, 0, 4.0f, 4.0f, true, m_WinRect);
        dataManager->m_Alpha_ani[dataManager->m_RankingDatas[i].name[1] - 'A']->AniPlay(hdc, { dataManager->m_Alpha_ani[dataManager->m_RankingDatas[i].name[1] - 'A']->GetPivots()[0].x + 800,
               dataManager->m_Alpha_ani[dataManager->m_RankingDatas[i].name[1] - 'A']->GetPivots()[0].y + 195 + 100 * i }, 0, 4.0f, 4.0f, true, m_WinRect);
        dataManager->m_Alpha_ani[dataManager->m_RankingDatas[i].name[2] - 'A']->AniPlay(hdc, { dataManager->m_Alpha_ani[dataManager->m_RankingDatas[i].name[2] - 'A']->GetPivots()[0].x + 880,
               dataManager->m_Alpha_ani[dataManager->m_RankingDatas[i].name[2] - 'A']->GetPivots()[0].y + 195 + 100 * i }, 0, 4.0f, 4.0f, true, m_WinRect);
    }
}

void GameManager::CharactorUpdate(HDC hdc, int Timer)
{
    MonsterInstantiate(m_Wave->TimeInterval, Timer);

    for (auto iter = m_Wave->LiveMonsters.begin(); iter != m_Wave->LiveMonsters.end(); iter++) // 플레이어 attack 콜라이더와 몬스터의 body Collider이 접촉 확인
    {
        CircleCollider temp = iter->get()->GetBodyCircleCollider();
        BoxCollider temp1 = m_Player->GetBodyCollider();

        if (m_Player->GetAttackCollider().OnTrigger(temp, 10)) //플레이어 공격
        {
            m_Player->SetAttackTimer(m_Player->GetAttackTimer() + 1); //공격 타이밍 측정

            if (m_Player->GetAttackTimer() == m_Player->GetAttackTiming())
            {
                iter->get()->SetCurHP(iter->get()->GetCurHP() - m_Player->GetAttack());
                iter->get()->Damaged(hdc, m_WinRect);
            }
        }

        if (iter->get()->GetAttackCollider().OnTrigger(temp1, 500)) //몬스터 공격
        {
            iter->get()->SetAttackTimer(iter->get()->GetAttackTimer() + 1); //공격 타이밍 측정

            if (iter->get()->GetAttackTimer() == iter->get()->GetAttackTiming() && !PlayerEternal)
            {
                m_Player->SetCurHP(m_Player->GetCurHP() - iter->get()->GetAttack());

                if (m_Player->GetAlive())
                {
                    if(!PlayerNoHitAni)
                        m_Player->Damaged(hdc, m_WinRect);
                }


            }
        }

        if (iter->get()->GetPos().m_Z <= 413) //이동 영역 (몬스터)
        {
            iter->get()->SetPos({ iter->get()->GetPos().m_X, 413, 413 });
        }

        else if (iter->get()->GetPos().m_Z >= m_WinRect.bottom)
        {
            iter->get()->SetPos({ iter->get()->GetPos().m_X, m_WinRect.bottom, m_WinRect.bottom });
        }
    }

    for (auto iter = m_Wave->LiveMonsters.begin(); iter != m_Wave->LiveMonsters.end();) //몬스터 이동 처리
    {
        iter->get()->ShowCharactor(hdc, iter->get()->GetAniSpeed(), Timer, m_WinRect);
        iter->get()->ShowColliders(hdc);

        TCHAR temp[20];
        _stprintf_s(temp, L"[%d, %d, %d]", iter->get()->GetPos().m_X, iter->get()->GetPos().m_Y, iter->get()->GetPos().m_Z);
        TextOut(hdc, iter->get()->GetPos().m_X, iter->get()->GetPos().m_Y, temp, _tcslen(temp));

        iter->get()->MonsterAI(hdc, m_WinRect, m_Player, 3);
        iter->get()->Update(true);

        if (iter->get()->GetAlive() == false)
        {
            m_Player->SetPoints(m_Player->GetPoints() + iter->get()->GetDeadPoints());
            m_Wave->DeadMonsters.push(*iter);
            iter = m_Wave->LiveMonsters.erase(iter);
        }
        else ++iter;
    }

    if (m_Player->GetPos().m_X < 25) //이동 영역 (플레이어)
    {
        m_Player->SetPos({ 25, m_Player->GetPos().m_Y,m_Player->GetPos().m_Z });
    }

    else if (m_Player->GetPos().m_X > m_WinRect.right - 110)
    {
        m_Player->SetPos({ m_WinRect.right - 110,m_Player->GetPos().m_Y, m_Player->GetPos().m_Z });
    }

    if (m_Player->GetPos().m_Z < 335)
    {
        m_Player->SetPos({ m_Player->GetPos().m_X, 335, 335 });
    }

    else if (m_Player->GetPos().m_Z > m_WinRect.bottom - 100)
    {
        m_Player->SetPos({ m_Player->GetPos().m_X, m_WinRect.bottom - 100, m_WinRect.bottom - 100 });
    }

    m_Player->ShowCharactor(hdc, m_Player->GetAniSpeed(), Timer, m_WinRect);
    m_Player->ShowColliders(hdc);
    m_Player->Update(true);

    TCHAR temp[20];
    _stprintf_s(temp, L"[%d, %d, %d]", m_Player->GetPos().m_X, m_Player->GetPos().m_Y+125, m_Player->GetPos().m_Z+125);
    TextOut(hdc, m_Player->GetPos().m_X, m_Player->GetPos().m_Y + 125, temp, _tcslen(temp)); //Sprite는 해당 값에서 확대 비율을 나눈다
}

void GameManager::MonsterInstantiate(int timeInterval, int timer)
{
    if (!(timer % timeInterval) && !m_Wave->DeadMonsters.empty()) //시간이 다 되고, 죽은 몬스터 리스트가 비어있지 않다면 
    {
        m_Wave->DeadMonsters.front()->SetAlive(true);
        m_Wave->DeadMonsters.front()->SetCurHP(m_Wave->DeadMonsters.front()->GetMaxHP());
        m_Wave->DeadMonsters.front()->SetStatus(IDLE);

        // spawn 지역에 랜덤으로 소환
        int n = rand() % 10;
        m_Wave->DeadMonsters.front()->SetPos(Vector3(m_Wave->SpawnArea[n].x, m_Wave->SpawnArea[n].y, m_Wave->SpawnArea[n].y));

        m_Wave->LiveMonsters.push_back(m_Wave->DeadMonsters.front());
        m_Wave->DeadMonsters.pop();
    }
}
