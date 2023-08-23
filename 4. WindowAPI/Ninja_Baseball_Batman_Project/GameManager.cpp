#include "GameManager.h"

GameManager::GameManager()
{
    ///
	m_SceneNum = 3;
    m_Scene = &GameManager::EndingScene;
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

void GameManager::LoadSounds(const TCHAR dataFileName[100], map<string, shared_ptr<Sound>>& temp, HWND hWnd)
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

    static int channel = 1;
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
        temp[name] = shared_ptr<Sound>(new Sound(hWnd,uniAddress, channel));
        channel++;
        index++;
    }

    //channel = 1;
}

void GameManager::TitleScene(HWND hWnd, HDC hdc, HBITMAP & screen, RECT winRect) // SceneNum = 0
{
    screen = NULL;

    if (Sprites.empty() || Animations.empty() || Sounds.empty())
    {
        LoadSprites(_T("AniData/Datas/TitleScene_Sprites.txt"), Sprites);
        LoadAnimations(_T("AniData/Datas/TitleScene_Animations.txt"), Animations);
        LoadSounds(_T("AniData/Datas/TitleScene_Sounds.txt"), Sounds, hWnd);
        Sounds["Title_sound"]->PlayAudio();
    }


    static int totalFrame = 0;
    static int curFrame = 0;
    if (totalFrame == 0) totalFrame = Animations["Title_screen"]->GetFrameTotalCount();
    if (!(m_TimerFrame % 40))
        if (curFrame < totalFrame - 1) curFrame++;
        else curFrame = 0;

    Animations["Title_screen"]->AniPlay(hdc, { Animations["Title_screen"]->GetPivots()[0].x + 35,
        Animations["Title_screen"]->GetPivots()[0].y}, curFrame, 1.55f, 1.55f, true, winRect);

}

void GameManager::SelectScene(HWND hWnd, HDC hdc, HBITMAP & screen, RECT winRect) // SceneNum = 1
{
    screen = NULL;

    if (Sprites.empty() || Animations.empty() || Sounds.empty())
    {
        LoadSprites(_T("AniData/Datas/SelectScene_Sprites.txt"), Sprites);
        LoadAnimations(_T("AniData/Datas/SelectScene_Animations.txt"), Animations);
        LoadSounds(_T("AniData/Datas/SelectScene_Sounds.txt"), Sounds, hWnd);
        Sounds["Select_BGM"]->PlayAudio();

        // 타이머 애니 로드
        Number_ani.push_back(Animations["Num_zero"]);
        Number_ani.push_back(Animations["Num_one"]);
        Number_ani.push_back(Animations["Num_two"]);
        Number_ani.push_back(Animations["Num_three"]);
        Number_ani.push_back(Animations["Num_four"]);
        Number_ani.push_back(Animations["Num_five"]);
        Number_ani.push_back(Animations["Num_six"]);
        Number_ani.push_back(Animations["Num_seven"]);
        Number_ani.push_back(Animations["Num_eight"]);
        Number_ani.push_back(Animations["Num_nine"]);
    }

    for (int i = 20; i <= 900; i += 30)
    {
        for (int j = 0; j <= 630; j += 35)
        {
            Animations["Select_background"]->AniPlay(hdc, { Animations["Select_background"]->GetPivots()[0].x + i,
                Animations["Select_background"]->GetPivots()[0].y + j}, 0, 1.55f, 1.55f, true, winRect);
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

        Animations["1P_select"]->AniPlay(hdc, m_Cursor, curFrame, 3.0f, 3.0f, true, winRect);

        Animations["Jose_select"]->AniPlay(hdc, { Animations["Jose_select"]->GetPivots()[0].x + 20,
            Animations["Jose_select"]->GetPivots()[0].y + 250 }, 0, 3.0f, 3.0f, true, winRect);
        Animations["Ryno_select"]->AniPlay(hdc, { Animations["Ryno_select"]->GetPivots()[0].x + 262,
            Animations["Ryno_select"]->GetPivots()[0].y + 250 }, 0, 3.0f, 3.0f, true, winRect);
        Animations["Roger_select"]->AniPlay(hdc, { Animations["Roger_select"]->GetPivots()[0].x + 507,
            Animations["Roger_select"]->GetPivots()[0].y + 250 }, 0, 3.0f, 3.0f, true, winRect);
        Animations["Straw_select"]->AniPlay(hdc, { Animations["Straw_select"]->GetPivots()[0].x + 750,
           Animations["Straw_select"]->GetPivots()[0].y + 250 }, 0, 3.0f, 3.0f, true, winRect);

        ShowTimer(hdc, Number_ani,winRect);
    }

    else
    {
        if (m_Cursor.x == m_SelectPosX[0])
        {
            Animations["Jose_selected"]->AniPlay(hdc, { Animations["Jose_selected"]->GetPivots()[0].x + 20,
                Animations["Jose_selected"]->GetPivots()[0].y + 150 }, 0, 3.0f, 3.0f, true, winRect);
            Animations["Ryno_select"]->AniPlay(hdc, { Animations["Ryno_select"]->GetPivots()[0].x + 262,
           Animations["Ryno_select"]->GetPivots()[0].y + 250 }, 0, 3.0f, 3.0f, true, winRect);
            Animations["Roger_select"]->AniPlay(hdc, { Animations["Roger_select"]->GetPivots()[0].x + 507,
                Animations["Roger_select"]->GetPivots()[0].y + 250 }, 0, 3.0f, 3.0f, true, winRect);
            Animations["Straw_select"]->AniPlay(hdc, { Animations["Straw_select"]->GetPivots()[0].x + 750,
               Animations["Straw_select"]->GetPivots()[0].y + 250 }, 0, 3.0f, 3.0f, true, winRect);
        }

        else if (m_Cursor.x == m_SelectPosX[1])
        {
            Animations["Ryno_selected"]->AniPlay(hdc, { Animations["Ryno_selected"]->GetPivots()[0].x + 262,
                Animations["Ryno_selected"]->GetPivots()[0].y + 150 }, 0, 3.0f, 3.0f, true, winRect);
            Animations["Jose_select"]->AniPlay(hdc, { Animations["Jose_select"]->GetPivots()[0].x + 20,
            Animations["Jose_select"]->GetPivots()[0].y + 250 }, 0, 3.0f, 3.0f, true, winRect);
            Animations["Roger_select"]->AniPlay(hdc, { Animations["Roger_select"]->GetPivots()[0].x + 507,
            Animations["Roger_select"]->GetPivots()[0].y + 250 }, 0, 3.0f, 3.0f, true, winRect);
            Animations["Straw_select"]->AniPlay(hdc, { Animations["Straw_select"]->GetPivots()[0].x + 750,
               Animations["Straw_select"]->GetPivots()[0].y + 250 }, 0, 3.0f, 3.0f, true, winRect);
        }


        else if (m_Cursor.x == m_SelectPosX[2])
        {
            Animations["Roger_selected"]->AniPlay(hdc, { Animations["Roger_selected"]->GetPivots()[0].x + 507,
                Animations["Roger_selected"]->GetPivots()[0].y + 150 }, 0, 3.0f, 3.0f, true, winRect);
            Animations["Jose_select"]->AniPlay(hdc, { Animations["Jose_select"]->GetPivots()[0].x + 20,
             Animations["Jose_select"]->GetPivots()[0].y + 250 }, 0, 3.0f, 3.0f, true, winRect);
            Animations["Ryno_select"]->AniPlay(hdc, { Animations["Ryno_select"]->GetPivots()[0].x + 262,
           Animations["Ryno_select"]->GetPivots()[0].y + 250 }, 0, 3.0f, 3.0f, true, winRect);
            Animations["Straw_select"]->AniPlay(hdc, { Animations["Straw_select"]->GetPivots()[0].x + 750,
               Animations["Straw_select"]->GetPivots()[0].y + 250 }, 0, 3.0f, 3.0f, true, winRect);
        }

        else
        {
            Animations["Straw_selected"]->AniPlay(hdc, { Animations["Straw_selected"]->GetPivots()[0].x + 750,
                Animations["Straw_selected"]->GetPivots()[0].y + 150 }, 0, 3.0f, 3.0f, true, winRect);
            Animations["Jose_select"]->AniPlay(hdc, { Animations["Jose_select"]->GetPivots()[0].x + 20,
           Animations["Jose_select"]->GetPivots()[0].y + 250 }, 0, 3.0f, 3.0f, true, winRect);
            Animations["Ryno_select"]->AniPlay(hdc, { Animations["Ryno_select"]->GetPivots()[0].x + 262,
                Animations["Ryno_select"]->GetPivots()[0].y + 250 }, 0, 3.0f, 3.0f, true, winRect);
            Animations["Roger_select"]->AniPlay(hdc, { Animations["Roger_select"]->GetPivots()[0].x + 507,
                Animations["Roger_select"]->GetPivots()[0].y + 250 }, 0, 3.0f, 3.0f, true, winRect);
        }

    }


    Animations["Jose_tag"]->AniPlay(hdc, { Animations["Jose_tag"]->GetPivots()[0].x + 20, Animations["Jose_tag"]->GetPivots()[0].y + 560 }, 0, 3.0f, 3.0f, true, winRect);
    Animations["Ryno_tag"]->AniPlay(hdc, { Animations["Ryno_tag"]->GetPivots()[0].x + 262, Animations["Ryno_tag"]->GetPivots()[0].y + 560 }, 0, 3.0f, 3.0f, true, winRect);
    Animations["Roger_tag"]->AniPlay(hdc, { Animations["Roger_tag"]->GetPivots()[0].x + 507,Animations["Roger_tag"]->GetPivots()[0].y + 560 }, 0, 3.0f, 3.0f, true, winRect);
    Animations["Straw_tag"]->AniPlay(hdc, { Animations["Straw_tag"]->GetPivots()[0].x + 750,Animations["Straw_tag"]->GetPivots()[0].y + 560 }, 0, 3.0f, 3.0f, true, winRect);

    Animations["Player_select_deco"]->AniPlay(hdc, { Animations["Player_select_deco"]->GetPivots()[0].x + 50,Animations["Player_select_deco"]->GetPivots()[0].y + 65 }, 0, 3.0f, 3.0f, true, winRect);
    Animations["Player"]->AniPlay(hdc, { Animations["Player"]->GetPivots()[0].x + 120, Animations["Player"]->GetPivots()[0].y + 40 }, 0, 3.0f, 3.0f, true, winRect);
    Animations["Player_select_deco"]->AniPlay(hdc, { Animations["Player_select_deco"]->GetPivots()[0].x + 920, Animations["Player_select_deco"]->GetPivots()[0].y + 65 }, 0, 3.0f, 3.0f, true, winRect);
    Animations["Select"]->AniPlay(hdc, { Animations["Select"]->GetPivots()[0].x + 600, Animations["Select"]->GetPivots()[0].y + 40 }, 0, 3.0f, 3.0f, true, winRect);


}

void GameManager::PlayScene(HWND hWnd, HDC hdc, HBITMAP & screen, RECT winRect) // SceneNum = 2
{
    if (Sprites.empty() || Animations.empty() ||Sounds.empty())
    {
        LoadSprites(_T("AniData/Datas/PlayScene_Sprites.txt"),Sprites);
        LoadAnimations(_T("AniData/Datas/PlayScene_Animations_etc.txt"),Animations);
        LoadSounds(_T("AniData/Datas/PlayScene_Sounds.txt"), Sounds, hWnd);
        LoadSounds(_T("AniData/Datas/PlayScene_Sounds_Ryno.txt"), Sounds, hWnd);
        LoadSounds(_T("AniData/Datas/PlayScene_Sounds_Baseball.txt"), Sounds, hWnd);
        
        //PlayScene_BGM

        Number_ani.push_back(Animations["Pointnum_zero"]);
        Number_ani.push_back(Animations["Pointnum_one"]);
        Number_ani.push_back(Animations["Pointnum_two"]);
        Number_ani.push_back(Animations["Pointnum_three"]);
        Number_ani.push_back(Animations["Pointnum_four"]);
        Number_ani.push_back(Animations["Pointnum_five"]);
        Number_ani.push_back(Animations["Pointnum_six"]);
        Number_ani.push_back(Animations["Pointnum_seven"]);
        Number_ani.push_back(Animations["Pointnum_eight"]);
        Number_ani.push_back(Animations["Pointnum_nine"]);

        map<string, shared_ptr<Animation>> temp;
        LoadAnimations(_T("AniData/Datas/PlayScene_Animations_Ryno.txt"), temp);

        map<string, shared_ptr<Sound>> temp1;
        temp1["Ryno_attack"] = Sounds["Ryno_attack"];
        temp1["Ryno_dead"] = Sounds["Ryno_dead"];
        temp1["Ryno_dynamite"] = Sounds["Ryno_dynamite"];
        temp1["Ryno_dynamite_shooting"] = Sounds["Ryno_dynamite_shooting"];
        temp1["Ryno_dynamite2"] = Sounds["Ryno_dynamite2"];
        temp1["Ryno_hit"] = Sounds["Ryno_hit"];
        temp1["Ryno_homerun"] = Sounds["Ryno_homerun"];

        m_Player = shared_ptr<Ryno>(new Ryno(Vector3(100, 500, 500), 100,100, 10, temp, temp1));

        LoadStage(hWnd,1,winRect);

        Sounds["PlayScene_BGM"]->PlayAudio();
    }

    //if (m_Stage->GetStageFinish())
    //{
    //    Sprites.clear();
    //    Animations.clear();
    //    Sounds.clear();
    //    m_SceneNum = 3;
    //    m_Scene = &GameManager::EndingScene;
    //}
    
    m_Player->m_Bitmap = screen;
    ShowBackStage(hdc, winRect);

    m_Stage->StageUpdate(hdc, m_TimerFrame, winRect, m_Player, m_Player->GetStopMove());

    ShowUI(hdc, winRect);

}

void GameManager::LoadStage(HWND hWnd,int stageNum, RECT winRect)
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
        temp1["Baseball_attack"] = Sounds["Baseball_attack"];
        temp1["Baseball_dead"] = Sounds["Baseball_dead"];
        temp1["Baseball_hit"] = Sounds["Baseball_hit"];

        //LoadSounds(_T("AniData/Datas/PlayScene_Sounds_Baseball.txt"), temp1, hWnd);

        stageMonsters.push_back(shared_ptr<Baseball>(new Baseball(Vector3(800, 550, 550),50,50,1,temp,temp1,100)));
        //stageMonsters.push_back(shared_ptr<Baseball>(new Baseball(Vector3(800, 700, 700),50,50,1,temp,temp1,100)));
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

        m_Stage = shared_ptr<Stage>(new Stage(playArea, limitAreas, stageMonsters));
    }
}

void GameManager::EndingScene(HWND hWnd, HDC hdc, HBITMAP & screen, RECT winRect) // SceneNum = 3
{
    if (Sprites.empty() || Animations.empty() || Sounds.empty())
    {
        LoadSprites(_T("AniData/Datas/EndingScene_Sprites.txt"), Sprites);
        LoadAnimations(_T("AniData/Datas/EndingScene_Animations.txt"), Animations);
        LoadSounds(_T("AniData/Datas/EndingScene_Sounds.txt"), Sounds, hWnd);
        //Sounds["Ending"]->PlayAudio();

        Number_ani.push_back(Animations["Orange_zero"]);
        Number_ani.push_back(Animations["Orange_one"]);
        Number_ani.push_back(Animations["Orange_two"]);
        Number_ani.push_back(Animations["Orange_three"]);
        Number_ani.push_back(Animations["Orange_four"]);
        Number_ani.push_back(Animations["Orange_five"]);
        Number_ani.push_back(Animations["Orange_six"]);
        Number_ani.push_back(Animations["Orange_seven"]);
        Number_ani.push_back(Animations["Orange_eight"]);
        Number_ani.push_back(Animations["Orange_nine"]);

        Alpha_ani.push_back(Animations["Green_A"]);
        Alpha_ani.push_back(Animations["Green_B"]);
        Alpha_ani.push_back(Animations["Green_C"]);
        Alpha_ani.push_back(Animations["Green_D"]);
        Alpha_ani.push_back(Animations["Green_E"]);
        Alpha_ani.push_back(Animations["Green_F"]);
        Alpha_ani.push_back(Animations["Green_G"]);
        Alpha_ani.push_back(Animations["Green_H"]);
        Alpha_ani.push_back(Animations["Green_I"]);
        Alpha_ani.push_back(Animations["Green_J"]);
        Alpha_ani.push_back(Animations["Green_K"]);
        Alpha_ani.push_back(Animations["Green_L"]);
        Alpha_ani.push_back(Animations["Green_M"]);
        Alpha_ani.push_back(Animations["Green_N"]);
        Alpha_ani.push_back(Animations["Green_O"]);
        Alpha_ani.push_back(Animations["Green_P"]);
        Alpha_ani.push_back(Animations["Green_Q"]);
        Alpha_ani.push_back(Animations["Green_R"]);
        Alpha_ani.push_back(Animations["Green_S"]);
        Alpha_ani.push_back(Animations["Green_T"]);
        Alpha_ani.push_back(Animations["Green_U"]);
        Alpha_ani.push_back(Animations["Green_V"]);
        Alpha_ani.push_back(Animations["Green_W"]);
        Alpha_ani.push_back(Animations["Green_X"]);
        Alpha_ani.push_back(Animations["Green_Y"]);
        Alpha_ani.push_back(Animations["Green_Z"]);
        Alpha_ani.push_back(Animations["Green_Underbar"]);

    }
    
    ShowBackStage(hdc, winRect);


    //if (m_ShowLetter[0] && m_ShowLetter[1] && m_ShowLetter[2])
    {
        ShowRanking(hdc,winRect, _T("AniData/Datas/PlayerRankings.txt"));
    }

    //else
    //{
    //    int xOffset = 40;
    //    int yOffset = 10;

    //    //GAME OVER
    //    Animations["Blue_G"]->AniPlay(hdc, { Animations["Blue_G"]->GetPivots()[0].x + 50 + xOffset,
    //        Animations["Blue_G"]->GetPivots()[0].y + 100 + yOffset }, 0, 5.0f, 5.0f, true, winRect);
    //    Animations["Blue_A"]->AniPlay(hdc, { Animations["Blue_A"]->GetPivots()[0].x + 150 + xOffset,
    //        Animations["Blue_A"]->GetPivots()[0].y + 100 + yOffset }, 0, 5.0f, 5.0f, true, winRect);
    //    Animations["Blue_M"]->AniPlay(hdc, { Animations["Blue_M"]->GetPivots()[0].x + 250 + xOffset,
    //        Animations["Blue_M"]->GetPivots()[0].y + 100 + yOffset }, 0, 5.0f, 5.0f, true, winRect);
    //    Animations["Blue_E"]->AniPlay(hdc, { Animations["Blue_E"]->GetPivots()[0].x + 350 + xOffset,
    //        Animations["Blue_E"]->GetPivots()[0].y + 100 + yOffset }, 0, 5.0f, 5.0f, true, winRect);

    //    Animations["Blue_O"]->AniPlay(hdc, { Animations["Blue_O"]->GetPivots()[0].x + 500 + xOffset,
    //        Animations["Blue_O"]->GetPivots()[0].y + 100 + yOffset }, 0, 5.0f, 5.0f, true, winRect);
    //    Animations["Blue_V"]->AniPlay(hdc, { Animations["Blue_V"]->GetPivots()[0].x + 600 + xOffset,
    //        Animations["Blue_V"]->GetPivots()[0].y + 100 + yOffset }, 0, 5.0f, 5.0f, true, winRect);
    //    Animations["Blue_E"]->AniPlay(hdc, { Animations["Blue_E"]->GetPivots()[0].x + 700 + xOffset,
    //        Animations["Blue_E"]->GetPivots()[0].y + 100 + yOffset }, 0, 5.0f, 5.0f, true, winRect);
    //    Animations["Blue_R"]->AniPlay(hdc, { Animations["Blue_R"]->GetPivots()[0].x + 800 + xOffset,
    //        Animations["Blue_R"]->GetPivots()[0].y + 100 + yOffset }, 0, 5.0f, 5.0f, true, winRect);

    //    int xOffset1 = 0;
    //    int yOffset1 = 10;

    //    //SCORE
    //    Animations["Orange_S"]->AniPlay(hdc, { Animations["Orange_S"]->GetPivots()[0].x + 150 + xOffset1,
    //        Animations["Orange_S"]->GetPivots()[0].y + 250 + yOffset1 }, 0, 3.5f, 3.5f, true, winRect);
    //    Animations["Orange_C"]->AniPlay(hdc, { Animations["Orange_C"]->GetPivots()[0].x + 210 + xOffset1,
    //        Animations["Orange_C"]->GetPivots()[0].y + 253 + yOffset1 }, 0, 3.5f, 3.5f, true, winRect);
    //    Animations["Orange_O"]->AniPlay(hdc, { Animations["Orange_O"]->GetPivots()[0].x + 270 + xOffset1,
    //        Animations["Orange_O"]->GetPivots()[0].y + 250 + yOffset1 }, 0, 3.5f, 3.5f, true, winRect);
    //    Animations["Orange_R"]->AniPlay(hdc, { Animations["Orange_R"]->GetPivots()[0].x + 330 + xOffset1,
    //        Animations["Orange_R"]->GetPivots()[0].y + 250 + yOffset1 }, 0, 3.5f, 3.5f, true, winRect);
    //    Animations["Orange_E"]->AniPlay(hdc, { Animations["Orange_E"]->GetPivots()[0].x + 390 + xOffset1,
    //        Animations["Orange_E"]->GetPivots()[0].y + 253 + yOffset1 }, 0, 3.5f, 3.5f, true, winRect);
    //    Animations["Orange_dash"]->AniPlay(hdc, { Animations["Orange_dash"]->GetPivots()[0].x + 450 + xOffset1,
    //        Animations["Orange_dash"]->GetPivots()[0].y + 250 + yOffset1 }, 0, 3.5f, 3.5f, true, winRect);

    //    ShowPlayerPoints(hdc, { 800,270 }, 3.5f, 3.5f, 12345, 60);

    //    MakeName(hdc, winRect);
    //}
}

void GameManager::ShowTimer(HDC hdc, vector<shared_ptr<Animation>> & timerAni,RECT winRect)
{
    int temp = m_SelectTimer / 10;

    int tens = temp / 10;
    int ones = temp % 10;

    if (tens > 0)
    {
        timerAni[tens]->AniPlay(hdc, { 440,65 }, 0, 3.5f, 3.5f, true, winRect);
        timerAni[ones]->AniPlay(hdc, { 515,65 }, 0, 3.5f, 3.5f, true, winRect);
    }

    else
    {
        timerAni[ones]->AniPlay(hdc, { 477,65 }, 0, 3.5f, 3.5f, true, winRect);
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
    if (m_SceneNum == 1)
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
            Sounds["Selected_sound"]->PlayAudio();
            m_SelectFlag = true;
        }

        if (m_SelectTimer <= -20)
        {
            Sprites.clear();
            Animations.clear();
            Sounds.clear();
            Number_ani.clear();
            m_SceneNum = 2;
            m_Scene = &GameManager::PlayScene;
        }

        m_SelectTimer--;
    }

    else if (m_SceneNum == 2)
    {

        TCHAR temp[20];
        _stprintf_s(temp, L"[%d, %d, %d]", m_Player->GetPos().m_X, m_Player->GetPos().m_Y+125, m_Player->GetPos().m_Z+125);
        TextOut(hdc, m_Player->GetPos().m_X, m_Player->GetPos().m_Y + 125, temp, _tcslen(temp)); //Sprite는 해당 값에서 확대 비율을 나눈다

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
                    m_Player->HomeRun(hdc,winRect,m_KeyFlag[5]);
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
    static int pos_X = 0; // startOffset 설정
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
        Animations["Background1_BackStage"]->GetPivots()[0].y}, 0, 3.0f, 3.0f, true, winRect);
    Animations["Background1_BackStage"]->AniPlay(hdc, { pos_X + Animations["Background1_BackStage"]->GetPivots()[0].x +
        3 * Animations["Background1_BackStage"]->GetWidths()[0], pos_Y
        + Animations["Background1_BackStage"]->GetPivots()[0].y }, 0, 3.0f, 3.0f, true, winRect);

    Animations["Stage_6_boss"]->AniPlay(hdc, { Animations["Stage_6_boss"]->GetPivots()[0].x,
        Animations["Stage_6_boss"]->GetPivots()[0].y - 3 }, 0, 3.0f, 3.0f, true, winRect);

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


    if (m_SceneNum == 3)
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
                    m_ShowLetter[m_NameCursor] = true;

                    m_PlayerData.name = m_Name;
                    m_PlayerData.score = m_Player->GetPoints();
                    //cout << "Finish" << endl;
                    //cout << m_Name[0] << ", " << m_Name[1] << ", " << m_Name[2] << endl;
                }
            }

           

        }

       // cout << m_Name[0] <<", "<< m_Name[1] << ", " << m_Name[2] << endl;
    }
    
}

void GameManager::ShowUI(HDC hdc, RECT winRect)
{
    // UI
    if (m_Player->GetCurHP() > m_Player->GetMaxHP() * 0.35f)
    {
        Animations["Player_picture_normal"]->AniPlay(hdc, { Animations["Player_picture_normal"]->GetPivots()[0].x + 25,
           Animations["Player_picture_normal"]->GetPivots()[0].y + 34 }, 0, 3.0f, 3.0f, true, winRect);
    }
    else
    {
        if (!(m_TimerFrame % 5)) m_SelectFlag = !m_SelectFlag; //변수 재활용
        Animations["Player_picture_hurt"]->AniPlay(hdc, { Animations["Player_picture_hurt"]->GetPivots()[0].x + 25,
       Animations["Player_picture_hurt"]->GetPivots()[0].y + 34 }, m_SelectFlag, 3.0f, 3.0f, true, winRect);
    }

    Animations["Player_picture_frame"]->AniPlay(hdc, { Animations["Player_picture_frame"]->GetPivots()[0].x + 20,
        Animations["Player_picture_frame"]->GetPivots()[0].y + 10 }, 0, 3.0f, 3.0f, true, winRect);

    Animations["Player_hpbar_empty"]->AniPlay(hdc, { Animations["Player_hpbar_empty"]->GetPivots()[0].x + 100,
         Animations["Player_hpbar_empty"]->GetPivots()[0].y + 80 }, 0, 3.0f, 3.0f, true, winRect);

    ShowPlayerHP(hdc, Animations["Player_hpbar_full"], { Animations["Player_hpbar_full"]->GetPivots()[0].x + 105,
       Animations["Player_hpbar_full"]->GetPivots()[0].y + 80 }, 3.0f, 3.0f,(float)(m_Player->GetMaxHP() - m_Player->GetCurHP())/ m_Player->GetMaxHP());

    ShowPlayerPoints(hdc, { 225,55 }, 3.0f, 3.0f, m_Player->GetPoints(),25);


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

void GameManager::ShowPlayerPoints(HDC hdc, POINT offset_location, float imageRatioWidth, float imageRatioHeight, const int points, int distance)
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
        int bx = Number_ani[number[i]]->GetWidths()[0];
        int by = Number_ani[number[i]]->GetHeights()[0];
        int xStart = Number_ani[number[i]]->GetOffsets()[0].x;
        int yStart = Number_ani[number[i]]->GetOffsets()[0].y;
        int posX = offset_location.x - Number_ani[number[i]]->GetPivots()[0].x;
        int posY = offset_location.y - Number_ani[number[i]]->GetPivots()[0].y;

        HDC hMemDC;
        HBITMAP holdBitmap;

        hMemDC = CreateCompatibleDC(hdc);
        holdBitmap = (HBITMAP)SelectObject(hMemDC, Number_ani[number[i]]->GetResourceSprite()->GetSpriteImage());

        TransparentBlt(hdc, posX - distance *i, posY, (int)( bx * imageRatioWidth), (int)(by * imageRatioHeight), hMemDC, xStart, yStart,
             bx, by, RGB(Number_ani[number[i]]->GetResourceSprite()->GetTransparentColor().m_X, Number_ani[number[i]]->GetResourceSprite()->GetTransparentColor().m_Y,
                 Number_ani[number[i]]->GetResourceSprite()->GetTransparentColor().m_Z));

        SelectObject(hMemDC, holdBitmap);
        DeleteDC(hMemDC);
    }
}

void GameManager::MakeName(HDC hdc, RECT winRect)
{
    int xOffset2 = 10;
    int yOffset2 = 10;

    if (m_NameCursor == 0)
    {
        if (m_FirstPush)
        {
            Animations["Green_Underbar"]->AniPlay(hdc, { Animations["Green_Underbar"]->GetPivots()[0].x + 350 + xOffset2,
                Animations["Green_Underbar"]->GetPivots()[0].y + 420 + yOffset2 }, 0, 5.0f, 5.0f, true, winRect);
        }

        else
        {
            Alpha_ani[m_NameCount]->AniPlay(hdc, { Alpha_ani[m_NameCount]->GetPivots()[0].x + 350 + xOffset2,
            Alpha_ani[m_NameCount]->GetPivots()[0].y + 420 + yOffset2 }, 0, 5.0f, 5.0f, true, winRect);
        }
    }

    else if (m_NameCursor == 1)
    {
        if (m_FirstPush)
        {
            Animations["Green_Underbar"]->AniPlay(hdc, { Animations["Green_Underbar"]->GetPivots()[0].x + 450 + xOffset2,
               Animations["Green_Underbar"]->GetPivots()[0].y + 420 + yOffset2 }, 0, 5.0f, 5.0f, true, winRect);
        }

        else
        {
            Alpha_ani[m_NameCount]->AniPlay(hdc, { Alpha_ani[m_NameCount]->GetPivots()[0].x + 450 + xOffset2,
            Alpha_ani[m_NameCount]->GetPivots()[0].y + 420 + yOffset2 }, 0, 5.0f, 5.0f, true, winRect);

        }
    }

    else if(m_NameCursor == 2)
    {
        if (m_FirstPush)
        {
            Animations["Green_Underbar"]->AniPlay(hdc, { Animations["Green_Underbar"]->GetPivots()[0].x + 550 + xOffset2,
               Animations["Green_Underbar"]->GetPivots()[0].y + 420 + yOffset2 }, 0, 5.0f, 5.0f, true, winRect);
        }

        else
        {
            Alpha_ani[m_NameCount]->AniPlay(hdc, { Alpha_ani[m_NameCount]->GetPivots()[0].x + 550 + xOffset2,
           Alpha_ani[m_NameCount]->GetPivots()[0].y + 420 + yOffset2 }, 0, 5.0f, 5.0f, true, winRect);
        }
    }

    if (m_ShowLetter[0])
    {
        Alpha_ani[m_Name[0] - 'A']->AniPlay(hdc, { Alpha_ani[m_Name[0] - 'A']->GetPivots()[0].x + 350 + xOffset2,
           Alpha_ani[m_Name[0] - 'A']->GetPivots()[0].y + 420 + yOffset2 }, 0, 5.0f, 5.0f, true, winRect);

        if (m_ShowLetter[1])
        {
            Alpha_ani[m_Name[1] - 'A']->AniPlay(hdc, { Alpha_ani[m_Name[1] - 'A']->GetPivots()[0].x + 450 + xOffset2,
                Alpha_ani[m_Name[1] - 'A']->GetPivots()[0].y + 420 + yOffset2 }, 0, 5.0f, 5.0f, true, winRect);

            if (m_ShowLetter[2])
            {
                Alpha_ani[m_Name[2] - 'A']->AniPlay(hdc, { Alpha_ani[m_Name[2] - 'A']->GetPivots()[0].x + 550 + xOffset2,
                    Alpha_ani[m_Name[2] - 'A']->GetPivots()[0].y + 420 + yOffset2 }, 0, 5.0f, 5.0f, true, winRect);
            }
        }

    }

}

void GameManager::ShowRanking(HDC hdc, RECT winRect, const TCHAR rankFileName[100])
{
    vector<PlayerData> Datas(5);
    Datas.push_back(m_PlayerData);
    int num = 1;

    HANDLE hFile = CreateFile(rankFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, 0);

    if (hFile == NULL)
    {
        MessageBox(NULL, _T("Ranking 데이터 파일 로드 에러"), _T("에러"), MB_OK);
    }

    DWORD rbytes;
    TCHAR buff[100] = {};
    char chbuff[100] = {};
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
        char ranking[2], score[6], name[4];
        GetSentence(index, chbuff, ranking);
        if (buff[index] == '\0') break;
        GetSentence(index, chbuff, score);
        if (buff[index] == '\0') break;
        GetSentence(index, chbuff, name);
        int number = 0;
        int i = 0;
        while (score[i] != '\0')
        {
            number = 10 * number + (score[i] - 48);
            i++;
        }
        Datas[num].name = name;
        Datas[num].score = number;
        num++;
        index++;
    }

    sort(Datas.begin(), Datas.end());




    int xOffset = -80;
    int yOffset = -50;

    Animations["Blue_one"]->AniPlay(hdc, { Animations["Blue_one"]->GetPivots()[0].x + 150 + xOffset,
        Animations["Blue_one"]->GetPivots()[0].y + 250 + yOffset }, 0, 3.5f, 3.5f, true, winRect);

    ShowPlayerPoints(hdc, { 650 + xOffset , 260 + yOffset }, 3.0f, 3.0f, Datas[0].score, 55);

    Alpha_ani[Datas[0].name[0]-'A']->AniPlay(hdc, {Alpha_ani[Datas[0].name[0] - 'A']->GetPivots()[0].x + 800 + xOffset,
            Alpha_ani[Datas[0].name[0] - 'A']->GetPivots()[0].y + 245 + yOffset }, 0, 4.0f, 4.0f, true, winRect);
    Alpha_ani[Datas[0].name[1] - 'A']->AniPlay(hdc, { Alpha_ani[Datas[0].name[1] - 'A']->GetPivots()[0].x + 880 + xOffset,
           Alpha_ani[Datas[0].name[1] - 'A']->GetPivots()[0].y + 245 + yOffset }, 0, 4.0f, 4.0f, true, winRect);
    Alpha_ani[Datas[0].name[2] - 'A']->AniPlay(hdc, { Alpha_ani[Datas[0].name[2] - 'A']->GetPivots()[0].x + 960 + xOffset,
           Alpha_ani[Datas[0].name[2] - 'A']->GetPivots()[0].y + 245 + yOffset }, 0, 4.0f, 4.0f, true, winRect);


    Animations["Blue_two"]->AniPlay(hdc, { Animations["Blue_two"]->GetPivots()[0].x + 150 + xOffset,
        Animations["Blue_two"]->GetPivots()[0].y + 350 + yOffset }, 0, 3.5f, 3.5f, true, winRect);

    ShowPlayerPoints(hdc, { 650 + xOffset , 360 + yOffset }, 3.0f, 3.0f, Datas[1].score, 55);

    Alpha_ani[Datas[1].name[0] - 'A']->AniPlay(hdc, { Alpha_ani[Datas[1].name[0] - 'A']->GetPivots()[0].x + 800 + xOffset,
            Alpha_ani[Datas[1].name[0] - 'A']->GetPivots()[0].y + 345 + yOffset }, 0, 4.0f, 4.0f, true, winRect);
    Alpha_ani[Datas[1].name[1] - 'A']->AniPlay(hdc, { Alpha_ani[Datas[1].name[1] - 'A']->GetPivots()[0].x + 880 + xOffset,
           Alpha_ani[Datas[1].name[1] - 'A']->GetPivots()[0].y + 345 + yOffset }, 0, 4.0f, 4.0f, true, winRect);
    Alpha_ani[Datas[1].name[2] - 'A']->AniPlay(hdc, { Alpha_ani[Datas[1].name[2] - 'A']->GetPivots()[0].x + 960 + xOffset,
           Alpha_ani[Datas[1].name[2] - 'A']->GetPivots()[0].y + 345 + yOffset }, 0, 4.0f, 4.0f, true, winRect);

    Animations["Blue_three"]->AniPlay(hdc, { Animations["Blue_three"]->GetPivots()[0].x + 150 + xOffset,
        Animations["Blue_three"]->GetPivots()[0].y + 450 + yOffset }, 0, 3.5f, 3.5f, true, winRect);

    ShowPlayerPoints(hdc, { 650 + xOffset , 460 + yOffset }, 3.0f, 3.0f, Datas[2].score, 55);

    Alpha_ani[Datas[2].name[0] - 'A']->AniPlay(hdc, { Alpha_ani[Datas[2].name[0] - 'A']->GetPivots()[0].x + 800 + xOffset,
            Alpha_ani[Datas[2].name[0] - 'A']->GetPivots()[0].y + 445 + yOffset }, 0, 4.0f, 4.0f, true, winRect);
    Alpha_ani[Datas[2].name[1] - 'A']->AniPlay(hdc, { Alpha_ani[Datas[2].name[1] - 'A']->GetPivots()[0].x + 880 + xOffset,
           Alpha_ani[Datas[2].name[1] - 'A']->GetPivots()[0].y + 445 + yOffset }, 0, 4.0f, 4.0f, true, winRect);
    Alpha_ani[Datas[2].name[2] - 'A']->AniPlay(hdc, { Alpha_ani[Datas[2].name[2] - 'A']->GetPivots()[0].x + 960 + xOffset,
           Alpha_ani[Datas[2].name[2] - 'A']->GetPivots()[0].y + 445 + yOffset }, 0, 4.0f, 4.0f, true, winRect);

    Animations["Blue_four"]->AniPlay(hdc, { Animations["Blue_four"]->GetPivots()[0].x + 150 + xOffset,
        Animations["Blue_four"]->GetPivots()[0].y + 550 + yOffset }, 0, 3.5f, 3.5f, true, winRect);

    ShowPlayerPoints(hdc, { 650 + xOffset , 560 + yOffset }, 3.0f, 3.0f, Datas[3].score, 55);

    Alpha_ani[Datas[3].name[0] - 'A']->AniPlay(hdc, { Alpha_ani[Datas[3].name[0] - 'A']->GetPivots()[0].x + 800 + xOffset,
            Alpha_ani[Datas[3].name[0] - 'A']->GetPivots()[0].y + 545 + yOffset }, 0, 4.0f, 4.0f, true, winRect);
    Alpha_ani[Datas[3].name[1] - 'A']->AniPlay(hdc, { Alpha_ani[Datas[3].name[1] - 'A']->GetPivots()[0].x + 880 + xOffset,
           Alpha_ani[Datas[3].name[1] - 'A']->GetPivots()[0].y + 545 + yOffset }, 0, 4.0f, 4.0f, true, winRect);
    Alpha_ani[Datas[3].name[2] - 'A']->AniPlay(hdc, { Alpha_ani[Datas[3].name[2] - 'A']->GetPivots()[0].x + 960 + xOffset,
           Alpha_ani[Datas[3].name[2] - 'A']->GetPivots()[0].y + 545 + yOffset }, 0, 4.0f, 4.0f, true, winRect);

    Animations["Blue_five"]->AniPlay(hdc, { Animations["Blue_five"]->GetPivots()[0].x + 150 + xOffset,
        Animations["Blue_five"]->GetPivots()[0].y + 650 + yOffset }, 0, 3.5f, 3.5f, true, winRect);

    ShowPlayerPoints(hdc, { 650 + xOffset , 660 + yOffset }, 3.0f, 3.0f, Datas[4].score, 55);

    Alpha_ani[Datas[4].name[0] - 'A']->AniPlay(hdc, { Alpha_ani[Datas[4].name[0] - 'A']->GetPivots()[0].x + 800 + xOffset,
            Alpha_ani[Datas[4].name[0] - 'A']->GetPivots()[0].y + 645 + yOffset }, 0, 4.0f, 4.0f, true, winRect);
    Alpha_ani[Datas[4].name[1] - 'A']->AniPlay(hdc, { Alpha_ani[Datas[4].name[1] - 'A']->GetPivots()[0].x + 880 + xOffset,
           Alpha_ani[Datas[4].name[1] - 'A']->GetPivots()[0].y + 645 + yOffset }, 0, 4.0f, 4.0f, true, winRect);
    Alpha_ani[Datas[4].name[2] - 'A']->AniPlay(hdc, { Alpha_ani[Datas[4].name[2] - 'A']->GetPivots()[0].x + 960 + xOffset,
           Alpha_ani[Datas[4].name[2] - 'A']->GetPivots()[0].y + 645 + yOffset }, 0, 4.0f, 4.0f, true, winRect);



    //cout << "Ranking" << endl;
}
