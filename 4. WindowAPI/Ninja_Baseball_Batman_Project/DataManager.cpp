#include "DataManager.h"

DataManager::DataManager()
{
}

DataManager::~DataManager()
{
}

void DataManager::GetSentence(int& i, char* buff, char* sentence)
{
    int index = 0;
    while (buff[i] != '\t' && buff[i] != '\r' && buff[i] != '\n')
    {
        if (buff[i] == '\0') return;
        sentence[index] = buff[i];
        index++; i++;
    }
    sentence[index] = '\0';
    i++;
    return;
}

void DataManager::LoadSprites(const TCHAR dataFileName[100])
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
        m_Sprites[name] = shared_ptr<Sprite>(new Sprite(uniAddress));
        index++;
    }

}

void DataManager::LoadAnimations(const TCHAR dataFileName[100], map<string, shared_ptr<Animation>> & temp, bool isReference)
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

        if (isReference)
        {
            temp[aniName] = m_Animations[aniName];
        }
        else
        {
            TCHAR uniAddress[200] = {};
            MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, address, strlen(address), uniAddress, 200);
            temp[aniName] = shared_ptr<Animation>(new Animation(m_Sprites[originSprite], uniAddress));
        }
        index++;
    }

}

void DataManager::LoadSounds(const TCHAR dataFileName[100], map<string, shared_ptr<Sound>>& temp, HWND hWnd, bool isReference)
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

        if (isReference)
        {
            temp[name] = m_Sounds[name];
        }

        else
        {
            TCHAR uniAddress[200] = {};
            MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, address, strlen(address), uniAddress, 200);
            temp[name] = shared_ptr<Sound>(new Sound(hWnd, uniAddress, m_ChannelIndex));
            m_ChannelIndex++;
        }

        index++;
    }

}

void DataManager::LoadPlayerDatas(HWND hWnd, shared_ptr<Player> & player)
{
    map<string, shared_ptr<Animation>> temp;
    LoadAnimations(_T("AniData/Datas/PlayScene_Animations_Ryno.txt"), temp, true);

    map<string, shared_ptr<Sound>> temp1;
    LoadSounds(_T("AniData/Datas/PlayScene_Sounds_Ryno.txt"), temp1, hWnd,true);

    player = shared_ptr<Ryno>(new Ryno(Vector3(500, 500, 500), 100, 100, 10, temp, temp1));
}

void DataManager::LoadSceneDatas(int SceneNum, HWND hWnd)
{
    m_Sprites.clear();
    m_Animations.clear();
    m_Sounds.clear();
    m_Number_ani.clear();
    m_Alpha_ani.clear();

    if (SceneNum == 0)          // Title Scene
    {
        LoadSprites(_T("AniData/Datas/TitleScene_Sprites.txt"));
        LoadAnimations(_T("AniData/Datas/TitleScene_Animations.txt"),m_Animations,false);
        LoadSounds(_T("AniData/Datas/TitleScene_Sounds.txt"),m_Sounds,hWnd,false);
        m_ChannelIndex = 1;
    }

    else if (SceneNum == 1)     // Select Scene
    {
        LoadSprites(_T("AniData/Datas/SelectScene_Sprites.txt"));
        LoadAnimations(_T("AniData/Datas/SelectScene_Animations.txt"),m_Animations,false);
        LoadSounds(_T("AniData/Datas/SelectScene_Sounds.txt"),m_Sounds, hWnd, false);
        m_ChannelIndex = 1;

        for (int i = 0; i < 10; i++)
        {
            m_Number_ani.push_back(m_Animations["Num_" + to_string(i)]);
        }
    }

    else if (SceneNum == 2)     // Play Scene
    {
        LoadSprites(_T("AniData/Datas/PlayScene_Sprites.txt"));
        LoadAnimations(_T("AniData/Datas/PlayScene_Animations_Ryno.txt"),m_Animations,false);
        LoadAnimations(_T("AniData/Datas/PlayScene_Animations_etc.txt"),m_Animations,false);
        LoadAnimations(_T("AniData/Datas/PlayScene_Animations_Baseball.txt"), m_Animations,false);
        LoadSounds(_T("AniData/Datas/PlayScene_Sounds.txt"), m_Sounds, hWnd, false);
        LoadSounds(_T("AniData/Datas/PlayScene_Sounds_Ryno.txt"),m_Sounds, hWnd, false);
        LoadSounds(_T("AniData/Datas/PlayScene_Sounds_Baseball.txt"),m_Sounds, hWnd,false);
        m_ChannelIndex = 1;

        for (int i = 0; i < 10; i++)
        {
            m_Number_ani.push_back(m_Animations["Pointnum_" + to_string(i)]);
        }
    }

    else                       //Ending Scene
    {
        LoadSprites(_T("AniData/Datas/EndingScene_Sprites.txt"));
        LoadAnimations(_T("AniData/Datas/EndingScene_Animations.txt"), m_Animations, false);
        LoadSounds(_T("AniData/Datas/EndingScene_Sounds.txt"), m_Sounds, hWnd, false);


        for (int i = 0; i < 10; i++)
        {
            m_Number_ani.push_back(m_Animations["Orange_" + to_string(i)]);
        }

        for (int i = 1; i <= 5; i++)
        {
            m_Number_ani.push_back(m_Animations["Blue_" + to_string(i)]);
        }

        for (int i = 0; i < 26; i++)
        {
            string temp = "Green_";
            temp.push_back((char)(i + 65));
            m_Alpha_ani.push_back(m_Animations[temp]);
        }
       
        m_Alpha_ani.push_back(m_Animations["Green_Underbar"]);
    }
}

void DataManager::LoadWaveDatas(HWND hWnd, RECT winRect, shared_ptr<Wave> & wave)
{
    wave = shared_ptr<Wave>(new Wave);
    wave->MaxMonsterNum = 10;
    wave->LimitArea = { 415, winRect.bottom };


    for (int i = 0; i < 5; i++)
    {
        wave->SpawnArea.push_back({ -200, 425 + 20*i });
    }

    for (int i = 0; i < 5; i++)
    {
        wave->SpawnArea.push_back({ 1150, 425 + 20 * i });
    }
    
    wave->StageFinish = false;
    wave->LiveMonsters.clear();

    map<string, shared_ptr<Animation>> temp;
    LoadAnimations(_T("AniData/Datas/PlayScene_Animations_Baseball.txt"),temp,true);

    map<string, shared_ptr<Sound>> temp1;
    LoadSounds(_T("AniData/Datas/PlayScene_Sounds_Baseball.txt"),temp1, hWnd, true);

    for (int i = 0; i < wave->MaxMonsterNum; i++)
    {
        wave->DeadMonsters.push(shared_ptr<Baseball>(new Baseball(Vector3(0, 0, 0), 50, 50, 1, temp, temp1, 100)));
    }

}

void DataManager::MakeRanking(const TCHAR rankFileName[100])
{
    //m_RankingDatas.push_back(m_PlayerData);
    int num = 1;

    HANDLE hFile = CreateFile(rankFileName, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, 0);

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
    //while (chbuff[index++] != '\n');
    while (1)
    {
        PlayerData temp;
        char rank[2], score[6], name[4];
        GetSentence(index, chbuff, rank);
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
        for(int i=0;i<4;i++)
            temp.name[i] = name[i];
        temp.score = number;
        m_RankingDatas.push_back(temp);
        num++;
        index++;
    }

    sort(m_RankingDatas.begin(), m_RankingDatas.end());

    if (m_RankingDatas.size() > 5) m_RankingDatas.pop_back();

    DWORD size;
    LARGE_INTEGER curPtr;
    curPtr.QuadPart = 0;
    SetFilePointerEx(hFile,curPtr , NULL, FILE_BEGIN);

    int n = m_RankingDatas.size();
    for (int i = 0; i < n; i++)
    {
        TCHAR rank[10];
        _stprintf_s(rank, L"%d\t", i + 1);
        WriteFile(hFile, rank, (DWORD)_tcslen(rank) * sizeof(TCHAR), &size, NULL);

        TCHAR score[50];
        _stprintf_s(score, L"%d\t", m_RankingDatas[i].score);
        WriteFile(hFile, score, (DWORD)_tcslen(score) * sizeof(TCHAR), &size, NULL);

        TCHAR uniName[50] = {};
        MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, m_RankingDatas[i].name, strlen(m_RankingDatas[i].name), uniName, 200);
        WriteFile(hFile, uniName, (DWORD)_tcslen(uniName) * sizeof(TCHAR), &size, NULL);

        //\n추가
        TCHAR temp[5];
        _stprintf_s(temp, L"\n");
        WriteFile(hFile, temp, (DWORD)_tcslen(temp) * sizeof(TCHAR), &size, NULL);
    }

    CloseHandle(hFile);

}
