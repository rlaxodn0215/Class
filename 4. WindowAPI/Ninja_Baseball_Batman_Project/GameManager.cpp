#include "GameManager.h"

GameManager::GameManager()
{
    ///
	m_SceneNum = 2;
    m_Scene = &GameManager::PlayScene;
    ///
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
        MessageBox(NULL, _T("Sprite 데이터 파일 로드 에러"), _T("에러"), MB_OK);
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
    wcstombs_s(&convertedChars, chbuff, sizeof(chbuff), buff, _TRUNCATE); // 유니코드를 멀티바이트로 변환
#else
    strcpy_s(charStr, sizeof(charStr), tcharStr); // 이미 멀티바이트 문자열인 경우
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
        MessageBox(NULL, _T("Animation 데이터 파일 로드 에러"), _T("에러"), MB_OK);
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
    wcstombs_s(&convertedChars, chbuff, sizeof(chbuff), buff, _TRUNCATE); // 유니코드를 멀티바이트로 변환
#else
    strcpy_s(charStr, sizeof(charStr), tcharStr); // 이미 멀티바이트 문자열인 경우
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

void GameManager::TitleScene(HDC hdc, HBITMAP & screen) // SceneNum = 0
{
    screen = NULL;

    //Sprites.clear();
    //Animations.clear();
    //Sounds.clear();

    LoadSprites(_T("AniData/Datas/TitleScene_Sprites.txt"),Sprites);
    LoadAnimations(_T("AniData/Datas/TitleScene_Animations.txt"),Animations);
    //모든 소리 로드

    static int totalFrame = 0;
    static int curFrame = 0;
    if (totalFrame == 0) totalFrame = Animations["Title_screen"]->GetFrameTotalCount();
    if (!(m_TimerFrame % 50))
        if (curFrame < totalFrame - 1) curFrame++;
        else curFrame = 0;

    Animations["Title_screen"]->AniPlay(hdc, { 35, 0 }, curFrame, 1.55f, true, screen);
    //cout << curFrame << endl;
}

void GameManager::SelectScene(HDC hdc, HBITMAP & screen) // SceneNum = 1
{
    screen = NULL;

    if (Sprites.empty() || Animations.empty())
    {
        LoadSprites(_T("AniData/Datas/SelectScene_Sprites.txt"), Sprites);
        LoadAnimations(_T("AniData/Datas/SelectScene_Animations.txt"), Animations);

        // 타이머 애니 로드
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
            Animations["Select_background"]->AniPlay(hdc, { i,j }, 0, 1.55f, true, screen);
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

        Animations["1P_select"]->AniPlay(hdc, m_Cursor, curFrame, 3.0f, true, screen);

        Animations["Jose_select"]->AniPlay(hdc, { 20,250 }, 0, 3.0f, true, screen);
        Animations["Ryno_select"]->AniPlay(hdc, { 262,250 }, 0, 3.0f, true, screen);
        Animations["Roger_select"]->AniPlay(hdc, { 507,250 }, 0, 3.0f, true, screen);
        Animations["Straw_select"]->AniPlay(hdc, { 750,250 }, 0, 3.0f, true, screen);

        ShowTimer(hdc, Timer_ani,screen);
    }

    else
    {
        if (m_Cursor.x == m_SelectPosX[0])
        {
            Animations["Jose_selected"]->AniPlay(hdc, { 20,150 }, 0, 3.0f, true, screen);
            Animations["Ryno_select"]->AniPlay(hdc, { 262,250 }, 0, 3.0f, true, screen);
            Animations["Roger_select"]->AniPlay(hdc, { 507,250 }, 0, 3.0f, true, screen);
            Animations["Straw_select"]->AniPlay(hdc, { 750,250 }, 0, 3.0f, true, screen);
        }

        else if (m_Cursor.x == m_SelectPosX[1])
        {
            Animations["Ryno_selected"]->AniPlay(hdc, { 262,150 }, 0, 3.0f, true, screen);
            Animations["Jose_select"]->AniPlay(hdc, { 20,250 }, 0, 3.0f, true, screen);
            Animations["Roger_select"]->AniPlay(hdc, { 507,250 }, 0, 3.0f, true, screen);
            Animations["Straw_select"]->AniPlay(hdc, { 750,250 }, 0, 3.0f, true, screen);
        }


        else if (m_Cursor.x == m_SelectPosX[2])
        {
            Animations["Roger_selected"]->AniPlay(hdc, { 507,150 }, 0, 3.0f, true, screen);
            Animations["Jose_select"]->AniPlay(hdc, { 20,250 }, 0, 3.0f, true, screen);
            Animations["Ryno_select"]->AniPlay(hdc, { 262,250 }, 0, 3.0f, true, screen);
            Animations["Straw_select"]->AniPlay(hdc, { 750,250 }, 0, 3.0f, true, screen);
        }

        else
        {
            Animations["Straw_selected"]->AniPlay(hdc, { 750,150 }, 0, 3.0f, true, screen);
            Animations["Jose_select"]->AniPlay(hdc, { 20,250 }, 0, 3.0f, true, screen);
            Animations["Ryno_select"]->AniPlay(hdc, { 262,250 }, 0, 3.0f, true, screen);
            Animations["Roger_select"]->AniPlay(hdc, { 507,250 }, 0, 3.0f, true, screen);

        }
    }


    Animations["Jose_tag"]->AniPlay(hdc, { 20,560 }, 0, 3.0f, true, screen);
    Animations["Ryno_tag"]->AniPlay(hdc, { 262,560 }, 0, 3.0f, true, screen);
    Animations["Roger_tag"]->AniPlay(hdc, { 507,560 }, 0, 3.0f, true, screen);
    Animations["Straw_tag"]->AniPlay(hdc, { 750,560 }, 0, 3.0f, true, screen);

    Animations["Player_select_deco"]->AniPlay(hdc, { 50,65 }, 0, 3.0f, true, screen);
    Animations["Player"]->AniPlay(hdc, { 120,40 }, 0, 3.0f, true, screen);
    Animations["Player_select_deco"]->AniPlay(hdc, { 920,65 }, 0, 3.0f, true, screen);
    Animations["Select"]->AniPlay(hdc, { 600,40 }, 0, 3.0f, true, screen);


}

void GameManager::PlayScene(HDC hdc, HBITMAP & screen) // SceneNum = 2
{
    //screen = NULL;

    if (Sprites.empty() || Animations.empty())
    {
        map<string, shared_ptr<Animation>> temp;
        LoadSprites(_T("AniData/Datas/PlayScene_Sprites.txt"),Sprites);
        LoadAnimations(_T("AniData/Datas/PlayScene_Animations_etc.txt"),Animations);
        LoadAnimations(_T("AniData/Datas/PlayScene_Animations_Ryno.txt"), temp);

        map<string, shared_ptr<Sound>> temp1;

        m_Player = new Ryno(Vector3(100, 500, 500), 100, 5, temp, temp1);
    }

   Animations["Background1_stage1"]->AniPlay(hdc, { 0,0 }, 0, 3.0f,true, screen);
   Animations["Stage_1_2_3"]->AniPlay(hdc, { 0,0 }, 0, 3.0f, true, screen);

    m_Player->ShowCharactor(hdc,m_Player->GetAniSpeed(), m_TimerFrame,m_AniWait,screen);
    Ryno* temp = (Ryno*)m_Player;
    temp->GetBodyCollider().ShowCollider(hdc);
    temp->GetAttackCollider().ShowCollider(hdc);

}

void GameManager::EndingScene(HDC hdc, HBITMAP & screen) // SceneNum = 3
{



}

void GameManager::ShowTimer(HDC hdc, vector<shared_ptr<Animation>> & timerAni,HBITMAP & bitmap)
{
    int temp = m_SelectTimer / 10;

    int tens = temp / 10;
    int ones = temp % 10;

    if (tens > 0)
    {
        timerAni[tens]->AniPlay(hdc, { 440,65 }, 0, 3.5f, true, bitmap);
        timerAni[ones]->AniPlay(hdc, { 515,65 }, 0, 3.5f, true, bitmap);
    }

    else
    {
        timerAni[ones]->AniPlay(hdc, { 477,65 }, 0, 3.5f, true, bitmap);
    }
    
}

void GameManager::Gravity(int g)
{
   if (m_Player->GetVel().m_Y <= 30 && m_Player->GetPos().m_Y <= m_Player->GetPos().m_Z)
   {
       m_Player->SetVel(m_Player->GetVel() + Vector3(0,g,0));
   }
    
}

void GameManager::CheckKeyInput()
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
        m_Player->Update();

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
        if (!m_AniWait && !m_Jumping)
        {
            m_Player->Idle();
            m_Player->SetVel(Vector3(0, 0, 0));
        }

        if (GetAsyncKeyState(VK_UP) & 0x8000 && !m_AniWait && !m_KeyFlag[4])
        {
            m_KeyFlag[0] = true;

            if (!m_Jumping)
            {
                m_Player->SetVel(Vector3(0, -m_Player->GetMoveSpeed() / 1.5f, -m_Player->GetMoveSpeed() / 1.5f));
                m_Player->Move();
            }
        }

        if (GetAsyncKeyState(VK_DOWN) & 0x8000 && !m_AniWait && !m_KeyFlag[4])
        {
            m_KeyFlag[1] = true;

            if (!m_Jumping)
            {
                m_Player->SetVel(Vector3(0, m_Player->GetMoveSpeed() / 1.5f, m_Player->GetMoveSpeed() / 1.5f));
                m_Player->Move();
            }
        }

        if (GetAsyncKeyState(VK_LEFT) & 0x8000 && !m_AniWait && !m_KeyFlag[4])
        {
            m_KeyFlag[2] = true;
            m_Player->SetLookRight(false);

            if (m_ComboFlag[2] == false)
            {
                m_Player->SetVel(Vector3(-m_Player->GetMoveSpeed(), m_Player->GetVel().m_Y, m_Player->GetVel().m_Z));

                if (!m_Jumping)
                m_Player->Move();
            }
            else
            {
                m_ComboTimerCount = 0;
                m_Player->SetVel(Vector3(-m_Player->GetMoveSpeed() * 2, m_Player->GetVel().m_Y, m_Player->GetVel().m_Z));

                if (!m_Jumping)
                m_Player->Run();

            }
        }

        if (GetAsyncKeyState(VK_RIGHT) & 0x8000 && !m_AniWait && !m_KeyFlag[4])
        {
            m_KeyFlag[3] = true;
            m_Player->SetLookRight(true);

            if (m_ComboFlag[3] == false)
            {
                m_Player->SetVel(Vector3(m_Player->GetMoveSpeed(), m_Player->GetVel().m_Y, m_Player->GetVel().m_Z));

                if (!m_Jumping)
                m_Player->Move();
            }
            else
            {
                m_ComboTimerCount = 0;
                m_Player->SetVel(Vector3(m_Player->GetMoveSpeed()*2, m_Player->GetVel().m_Y, m_Player->GetVel().m_Z));

                if (!m_Jumping)
                m_Player->Run();

            }
        }   

        if (m_ComboFlag[4] && m_ComboFlag[5])
        {
            m_Player->HomeRun();

            if (m_Player->GetLookRight())
                m_Player->SetPos(m_Player->GetPos() + Vector3(10, 0, 0));
            else
                m_Player->SetPos(m_Player->GetPos() + Vector3(-10, 0, 0));

            m_AniWait = true;
            m_KeyFlag[5] = false;
            m_Jumping = false;
        }

        else if (GetAsyncKeyState(0x53) & 0x8000 || (m_Jumping && !m_KeyFlag[4])) // s
        {
            m_KeyFlag[5] = true;
            m_Player->Jump(m_KeyFlag[5], m_Jumping);
        }

        if (GetAsyncKeyState(0x41) & 0x8000) // a
        {
            m_KeyFlag[4] = true;
            m_Player->NormalAttack();
        }

       
    }
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

void GameManager::ShowPlayerLife(const Charactor& player)
{
}

void GameManager::ShowPlayerHPbar(const Charactor& player)
{
}

void GameManager::ShowBossHPbar(const Charactor& Boss)
{
}

void GameManager::ShowPlayerStateUI(const Charactor& player)
{
}

void GameManager::ShowPlayerPoints(const Charactor& player)
{
}

void GameManager::MoveNextStage()
{
}

void GameManager::SlowMotion()
{
}

void GameManager::GameOver()
{
}
