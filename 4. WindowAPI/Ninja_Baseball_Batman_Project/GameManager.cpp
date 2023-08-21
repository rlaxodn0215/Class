#include "GameManager.h"

GameManager::GameManager()
{
    ///
	m_SceneNum = 2;
    m_Scene = &GameManager::PlayScene;
    ///
    m_Stage=NULL;
	m_Player = NULL;
}


GameManager::~GameManager()
{

}

void GameManager::GetSentence(int& i, char* buff, char* sentence)
{
    int index = 0;
    while (buff[i] != '\t' && buff[i] != '\r')
    {
        if (buff[i] == '\0') return;
        sentence[index] = buff[i];
        index++; i++;
    }
    sentence[index] = '\0';
    i++;
    return;
}

void GameManager::LoadSprites(const TCHAR dataFileName[100], map<string, shared_ptr<Sprite>> & temp)
{

    HANDLE hFile = CreateFile(dataFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, 0);

    if (hFile == NULL)
    {
        MessageBox(NULL, _T("Sprite ������ ���� �ε� ����"), _T("����"), MB_OK);
    }

    DWORD rbytes;
    TCHAR buff[2000] = {};
    char chbuff[2000] = {};
    size_t convertedChars = 0;

    ReadFile(hFile, buff, sizeof(buff), &rbytes, NULL);

    if (buff[0] == 65279)
    {
        SetFilePointer(hFile, 2, NULL, FILE_BEGIN);
        ReadFile(hFile, buff, sizeof(buff), &rbytes, NULL);
    }

#ifdef UNICODE
    wcstombs_s(&convertedChars, chbuff, sizeof(chbuff), buff, _TRUNCATE); // �����ڵ带 ��Ƽ����Ʈ�� ��ȯ
#else
    strcpy_s(charStr, sizeof(charStr), tcharStr); // �̹� ��Ƽ����Ʈ ���ڿ��� ���
#endif

    int index = 0;
    while (chbuff[index++] != '\n');
    while (1)
    {
        char name[100], address[200];
        GetSentence(index, chbuff, name);
        if (buff[index] == '\0') break;
        GetSentence(index, chbuff, address);
        TCHAR uniAddress[200] = {};
        MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, address, strlen(address), uniAddress, 200);
        temp[name] = shared_ptr<Sprite>(new Sprite(uniAddress));
        index++;
    }

}

void GameManager::LoadAnimations(const TCHAR dataFileName[100], map<string, shared_ptr<Animation>> & temp)
{
    HANDLE hFile = CreateFile(dataFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, 0);

    if (hFile == NULL)
    {
        MessageBox(NULL, _T("Animation ������ ���� �ε� ����"), _T("����"), MB_OK);
    }

    DWORD rbytes;
    TCHAR buff[3000] = {};
    char chbuff[3000] = {};
    size_t convertedChars = 0;

    ReadFile(hFile, buff, sizeof(buff), &rbytes, NULL);

    if (buff[0] == 65279)
    {
        SetFilePointer(hFile, 2, NULL, FILE_BEGIN);
        ReadFile(hFile, buff, sizeof(buff), &rbytes, NULL);
    }

#ifdef UNICODE
    wcstombs_s(&convertedChars, chbuff, sizeof(chbuff), buff, _TRUNCATE); // �����ڵ带 ��Ƽ����Ʈ�� ��ȯ
#else
    strcpy_s(charStr, sizeof(charStr), tcharStr); // �̹� ��Ƽ����Ʈ ���ڿ��� ���
#endif

    int index = 0;
    while (chbuff[index++] != '\n');
    while (1)
    {
        char aniName[100], originSprite[100], address[200];
        GetSentence(index, chbuff, aniName);
        if (buff[index] == '\0') break;
        GetSentence(index, chbuff, originSprite);
        GetSentence(index, chbuff, address);
        TCHAR uniAddress[200] = {};
        MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, address, strlen(address), uniAddress, 200);
        temp[aniName]= shared_ptr<Animation>(new Animation(Sprites[originSprite], uniAddress));
        index++;
    }

}

void GameManager::LoadSounds(const TCHAR dataFileName[100])
{
}

void GameManager::TitleScene(HWND hWnd, HDC hdc, HBITMAP & screen, RECT winRect) // SceneNum = 0
{
    screen = NULL;

    //Sprites.clear();
    //Animations.clear();
    //Sounds.clear();

    LoadSprites(_T("AniData/Datas/TitleScene_Sprites.txt"),Sprites);
    LoadAnimations(_T("AniData/Datas/TitleScene_Animations.txt"),Animations);
    //��� �Ҹ� �ε�

    static int totalFrame = 0;
    static int curFrame = 0;
    if (totalFrame == 0) totalFrame = Animations["Title_screen"]->GetFrameTotalCount();
    if (!(m_TimerFrame % 50))
        if (curFrame < totalFrame - 1) curFrame++;
        else curFrame = 0;

    Animations["Title_screen"]->AniPlay(hdc, { 35, 0 }, curFrame, 1.55f, true, winRect);
    //cout << curFrame << endl;
}

void GameManager::SelectScene(HWND hWnd, HDC hdc, HBITMAP & screen, RECT winRect) // SceneNum = 1
{
    screen = NULL;

    if (Sprites.empty() || Animations.empty())
    {
        LoadSprites(_T("AniData/Datas/SelectScene_Sprites.txt"), Sprites);
        LoadAnimations(_T("AniData/Datas/SelectScene_Animations.txt"), Animations);

        // Ÿ�̸� �ִ� �ε�
        Timer_ani.push_back(Animations["Num_zero"]);
        Timer_ani.push_back(Animations["Num_one"]);
        Timer_ani.push_back(Animations["Num_two"]);
        Timer_ani.push_back(Animations["Num_three"]);
        Timer_ani.push_back(Animations["Num_four"]);
        Timer_ani.push_back(Animations["Num_five"]);
        Timer_ani.push_back(Animations["Num_six"]);
        Timer_ani.push_back(Animations["Num_seven"]);
        Timer_ani.push_back(Animations["Num_eight"]);
        Timer_ani.push_back(Animations["Num_nine"]);
    }
    for (int i = 20; i <= 900; i += 30)
    {
        for (int j = 0; j <= 630; j += 35)
        {
            Animations["Select_background"]->AniPlay(hdc, { i,j }, 0, 1.55f, true, winRect);
        }
    }


    if (!m_SelectFlag && m_SelectTimer > 0)
    {
        static int totalFrame = 0;
        static int curFrame = 0;
        if (totalFrame == 0) totalFrame = Animations["1P_select"]->GetFrameTotalCount();
        //if (!(TimerFrame % 2))
        if (curFrame < totalFrame - 1) curFrame++;
        else curFrame = 0;

        Animations["1P_select"]->AniPlay(hdc, m_Cursor, curFrame, 3.0f, true, winRect);

        Animations["Jose_select"]->AniPlay(hdc, { 20,250 }, 0, 3.0f, true, winRect);
        Animations["Ryno_select"]->AniPlay(hdc, { 262,250 }, 0, 3.0f, true, winRect);
        Animations["Roger_select"]->AniPlay(hdc, { 507,250 }, 0, 3.0f, true, winRect);
        Animations["Straw_select"]->AniPlay(hdc, { 750,250 }, 0, 3.0f, true, winRect);

        ShowTimer(hdc, Timer_ani,winRect);
    }

    else
    {
        if (m_Cursor.x == m_SelectPosX[0])
        {
            Animations["Jose_selected"]->AniPlay(hdc, { 20,150 }, 0, 3.0f, true, winRect);
            Animations["Ryno_select"]->AniPlay(hdc, { 262,250 }, 0, 3.0f, true, winRect);
            Animations["Roger_select"]->AniPlay(hdc, { 507,250 }, 0, 3.0f, true, winRect);
            Animations["Straw_select"]->AniPlay(hdc, { 750,250 }, 0, 3.0f, true, winRect);
        }

        else if (m_Cursor.x == m_SelectPosX[1])
        {
            Animations["Ryno_selected"]->AniPlay(hdc, { 262,150 }, 0, 3.0f, true, winRect);
            Animations["Jose_select"]->AniPlay(hdc, { 20,250 }, 0, 3.0f, true, winRect);
            Animations["Roger_select"]->AniPlay(hdc, { 507,250 }, 0, 3.0f, true, winRect);
            Animations["Straw_select"]->AniPlay(hdc, { 750,250 }, 0, 3.0f, true, winRect);
        }


        else if (m_Cursor.x == m_SelectPosX[2])
        {
            Animations["Roger_selected"]->AniPlay(hdc, { 507,150 }, 0, 3.0f, true, winRect);
            Animations["Jose_select"]->AniPlay(hdc, { 20,250 }, 0, 3.0f, true, winRect);
            Animations["Ryno_select"]->AniPlay(hdc, { 262,250 }, 0, 3.0f, true, winRect);
            Animations["Straw_select"]->AniPlay(hdc, { 750,250 }, 0, 3.0f, true, winRect);
        }

        else
        {
            Animations["Straw_selected"]->AniPlay(hdc, { 750,150 }, 0, 3.0f, true, winRect);
            Animations["Jose_select"]->AniPlay(hdc, { 20,250 }, 0, 3.0f, true, winRect);
            Animations["Ryno_select"]->AniPlay(hdc, { 262,250 }, 0, 3.0f, true, winRect);
            Animations["Roger_select"]->AniPlay(hdc, { 507,250 }, 0, 3.0f, true, winRect);

        }
    }


    Animations["Jose_tag"]->AniPlay(hdc, { 20,560 }, 0, 3.0f, true, winRect);
    Animations["Ryno_tag"]->AniPlay(hdc, { 262,560 }, 0, 3.0f, true, winRect);
    Animations["Roger_tag"]->AniPlay(hdc, { 507,560 }, 0, 3.0f, true, winRect);
    Animations["Straw_tag"]->AniPlay(hdc, { 750,560 }, 0, 3.0f, true, winRect);

    Animations["Player_select_deco"]->AniPlay(hdc, { 50,65 }, 0, 3.0f, true, winRect);
    Animations["Player"]->AniPlay(hdc, { 120,40 }, 0, 3.0f, true, winRect);
    Animations["Player_select_deco"]->AniPlay(hdc, { 920,65 }, 0, 3.0f, true, winRect);
    Animations["Select"]->AniPlay(hdc, { 600,40 }, 0, 3.0f, true, winRect);


}

void GameManager::PlayScene(HWND hWnd, HDC hdc, HBITMAP & screen, RECT winRect) // SceneNum = 2
{
    if (Sprites.empty() || Animations.empty())
    {
        map<string, shared_ptr<Animation>> temp;
        LoadSprites(_T("AniData/Datas/PlayScene_Sprites.txt"),Sprites);
        LoadAnimations(_T("AniData/Datas/PlayScene_Animations_etc.txt"),Animations);
        LoadAnimations(_T("AniData/Datas/PlayScene_Animations_Ryno.txt"), temp);

        map<string, shared_ptr<Sound>> temp1;

        m_Player = shared_ptr<Ryno>(new Ryno(Vector3(100, 500, 500), 100, 10, temp, temp1));

        LoadStage(1,winRect);
    }

    m_Player->m_Bitmap = screen;
    ShowBackStage(hdc, winRect);

    Animations["Stage_6_boss"]->AniPlay(hdc, { Animations["Stage_6_boss"]->GetPivots()[0].x,
        Animations["Stage_6_boss"]->GetPivots()[0].y - 3 },0, 3.0f, true, winRect);

    m_Stage->StageUpdate(hdc, m_TimerFrame, winRect, m_Player, m_Player->GetStopMove());

    ShowUI(hdc, winRect);

 

}

void GameManager::LoadStage(int stageNum, RECT winRect)
{
    if (stageNum == 1)
    {
        RECT playArea = { 0,0,326,233 };
        vector<RECT> limitAreas;
        limitAreas.push_back({ 0,0,winRect.right,415 });

        list<shared_ptr<Monster>> stageMonsters;

        map<string, shared_ptr<Animation>> temp;
        LoadAnimations(_T("AniData/Datas/PlayScene_Animations_Baseball.txt"), temp);

        map<string, shared_ptr<Sound>> temp1;

        stageMonsters.push_back(shared_ptr<Baseball>(new Baseball(Vector3(800, 550, 550),50,1,temp,temp1)));
        //stageMonsters.push_back(shared_ptr<Baseball>(new Baseball(Vector3(800, 550, 550),50,1,temp,temp1)));
        //stageMonsters.push_back(shared_ptr<Baseball>(new Baseball(Vector3(700, 450, 450),50,1,temp,temp1)));
        //stageMonsters.push_back(shared_ptr<Baseball>(new Baseball(Vector3(700, 550, 550),50,1,temp,temp1)));
        //stageMonsters.push_back(shared_ptr<Baseball>(new Baseball(Vector3(600, 450, 450),50,1,temp,temp1)));
        //stageMonsters.push_back(shared_ptr<Baseball>(new Baseball(Vector3(600, 550, 550),50,1,temp,temp1)));
        //stageMonsters.push_back(shared_ptr<Baseball>(new Baseball(Vector3(500, 450, 450),50,1,temp,temp1)));
        //stageMonsters.push_back(shared_ptr<Baseball>(new Baseball(Vector3(500, 550, 550),50,1,temp,temp1)));

        //stageMonsters.push_back(shared_ptr<Baseball>(new Baseball(Vector3(850, 400, 400), 50, 1, temp, temp1)));
        //stageMonsters.push_back(shared_ptr<Baseball>(new Baseball(Vector3(850, 550, 550), 50, 1, temp, temp1)));
        //stageMonsters.push_back(shared_ptr<Baseball>(new Baseball(Vector3(750, 450, 450), 50, 1, temp, temp1)));
        //stageMonsters.push_back(shared_ptr<Baseball>(new Baseball(Vector3(750, 550, 550), 50, 1, temp, temp1)));
        //stageMonsters.push_back(shared_ptr<Baseball>(new Baseball(Vector3(650, 450, 450), 50, 1, temp, temp1)));
        //stageMonsters.push_back(shared_ptr<Baseball>(new Baseball(Vector3(650, 550, 550), 50, 1, temp, temp1)));
        //stageMonsters.push_back(shared_ptr<Baseball>(new Baseball(Vector3(550, 450, 450), 50, 1, temp, temp1)));
        //stageMonsters.push_back(shared_ptr<Baseball>(new Baseball(Vector3(550, 550, 550), 50, 1, temp, temp1)));

        m_Stage =shared_ptr<Stage>(new Stage(playArea, limitAreas, stageMonsters));
    }
}

void GameManager::EndingScene(HWND hWnd, HDC hdc, HBITMAP & screen, RECT winRect) // SceneNum = 3
{

    

}

void GameManager::ShowTimer(HDC hdc, vector<shared_ptr<Animation>> & timerAni,RECT winRect)
{
    int temp = m_SelectTimer / 10;

    int tens = temp / 10;
    int ones = temp % 10;

    if (tens > 0)
    {
        timerAni[tens]->AniPlay(hdc, { 440,65 }, 0, 3.5f, true, winRect);
        timerAni[ones]->AniPlay(hdc, { 515,65 }, 0, 3.5f, true, winRect);
    }

    else
    {
        timerAni[ones]->AniPlay(hdc, { 477,65 }, 0, 3.5f, true, winRect);
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

void GameManager::CheckKeyInput(HDC hdc, RECT winRect)
{
    if (m_SceneNum == 0)
    {

    }

    else if (m_SceneNum == 1)
    {
        static int selectNum = 0;

        if (GetAsyncKeyState(VK_LEFT) & 0x8000 && !m_SelectFlag)
        {
            if (selectNum > 0 && !m_KeyFlag[2])
            {
                m_Cursor.x = m_SelectPosX[--selectNum];
                m_KeyFlag[2] = true;
            }

        }

        if (GetAsyncKeyState(VK_RIGHT) & 0x8000 && !m_SelectFlag)
        {
            if (selectNum < 3 && !m_KeyFlag[3])
            {
                m_Cursor.x = m_SelectPosX[++selectNum];
                m_KeyFlag[3] = true;
            }
        }

        if (GetAsyncKeyState(0x41) & 0x8000 || GetAsyncKeyState(0x53) & 0x8000 && !m_SelectFlag)
        {
            m_SelectTimer = 0;
            m_SelectFlag = true;
        }

        if (m_SelectTimer <= -20)
        {
            m_SceneNum = 2;
            m_Scene = &GameManager::PlayScene;
            Sprites.clear();
            Animations.clear();
            Sounds.clear();
        }

        m_SelectTimer--;
    }

    else if (m_SceneNum == 2)
    {

        TCHAR temp[20];
        _stprintf_s(temp, L"[%d, %d, %d]", m_Player->GetPos().m_X, m_Player->GetPos().m_Y+125, m_Player->GetPos().m_Z+125);
        TextOut(hdc, m_Player->GetPos().m_X, m_Player->GetPos().m_Y + 125, temp, _tcslen(temp)); //Sprite�� �ش� ������ Ȯ�� ������ ������

        //cout << m_Player->GetPos() << endl;
        //cout << m_Player->GetVel() << endl;

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

        if (m_Player->GetHP() > 0)
        {
            if (!m_Player->GetStopMove()) // ������ �� ���� �ִ� �۵� ����
            {
                if (!m_Player->GetJumping() && !m_PlayerDynamite) // ������ �ʻ�� ��� �� �Ҷ�
                {
                    m_Player->Idle();
                    m_Player->SetVel(Vector3(0, 0, 0));
                    //cout << "Player Idle" << endl;
                }

                if (GetAsyncKeyState(VK_UP) & 0x8000 && !m_KeyFlag[4] && !m_PlayerDynamite) //���� X, �ʻ�� X
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
                    m_Player->HomeRun();
                    m_Player->SetAttack(10);

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
                    m_Player->Dynamite(hdc, m_TimerFrame, winRect, m_PlayerDynamite);
                }
            }
        }

        else
        {
            m_Player->SetVel({ 0,0,0 });
            m_Player->Dead();
            m_Player->SetTempTimer(m_Player->GetTempTimer()+1);
            if (m_Player->GetTempTimer() == m_Player->GetCurAni()->GetFrameTotalCount())
            {
                m_Player->SetAlive(false);
            }

        }
    }
}

void GameManager::ShowBackStage(HDC hdc, RECT winRect)
{
    static int pos_X = 0; // startOffset ����
    static int pos_Y = 0;
    static bool down = true;

    if (pos_X > -3 * Animations["Background1_BackStage"]->GetWidths()[0]) pos_X -= 40;
    else pos_X = 0;

    if (down)
    {
        if (pos_Y >= -(3 * Animations["Background1_BackStage"]->GetHeights()[0] - winRect.bottom / 2))
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

    Animations["Background1_BackStage"]->AniPlay(hdc, { pos_X + Animations["Background1_BackStage"]->GetPivots()[0].x, pos_Y +
        Animations["Background1_BackStage"]->GetPivots()[0].y}, 0, 3.0f, true, winRect);
    Animations["Background1_BackStage"]->AniPlay(hdc, { pos_X + Animations["Background1_BackStage"]->GetPivots()[0].x +
        3 * Animations["Background1_BackStage"]->GetWidths()[0], pos_Y
        + Animations["Background1_BackStage"]->GetPivots()[0].y }, 0, 3.0f, true, winRect);

}

void GameManager::CheckKeyRelease(WPARAM wParam)
{

    if (wParam == VK_UP)
    {
        m_ComboFlag[0] = true;
        m_KeyFlag[0] = false;
    }

    if (wParam == VK_DOWN)
    {
        m_ComboFlag[1] = true;
        m_KeyFlag[1] = false;
    }

    if (wParam == VK_LEFT)
    {
        m_ComboFlag[2] = true;
        m_KeyFlag[2] = false;

    }

    if (wParam == VK_RIGHT)
    {
        m_ComboFlag[3] = true;
        m_KeyFlag[3] = false;
    }

    if (wParam == 0x41)
    {
        m_ComboFlag[4] = true;
        m_KeyFlag[4] = false;
    }

    if (wParam == 0x53)
    {
        m_ComboFlag[5] = true;
    }
    
}

void GameManager::ShowUI(HDC hdc, RECT winRect)
{
    // UI
    Animations["Player_picture_normal"]->AniPlay(hdc, { Animations["Player_picture_normal"]->GetPivots()[0].x + 25,
       Animations["Player_picture_normal"]->GetPivots()[0].y + 34 }, 0, 3.0f, true, winRect);

    Animations["Player_picture_frame"]->AniPlay(hdc, { Animations["Player_picture_frame"]->GetPivots()[0].x + 20,
        Animations["Player_picture_frame"]->GetPivots()[0].y + 10 }, 0, 3.0f, true, winRect);

    Animations["Player_hpbar_full"]->AniPlay(hdc, { Animations["Player_hpbar_full"]->GetPivots()[0].x + 100,
       Animations["Player_hpbar_full"]->GetPivots()[0].y + 80 }, 0, 3.0f, true, winRect);
}



void GameManager::GameOver()
{
}
