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

void DataManager::LoadAnimations(const TCHAR dataFileName[100], map<string, shared_ptr<Animation>> & temp)
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
        temp[aniName] = shared_ptr<Animation>(new Animation(m_Sprites[originSprite], uniAddress));
        index++;
    }

}

void DataManager::LoadSounds(const TCHAR dataFileName[100], map<string, shared_ptr<Sound>>& temp, HWND hWnd)
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

    int channel = 1;
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
        temp[name] = shared_ptr<Sound>(new Sound(hWnd, uniAddress, channel));
        channel++;
        index++;
    }

}

void DataManager::LoadPlayerDatas(HWND hWnd, shared_ptr<Player> player)
{
    map<string, shared_ptr<Animation>> temp;
    LoadAnimations(_T("AniData/Datas/PlayScene_Animations_Ryno.txt"), temp);

    map<string, shared_ptr<Sound>> temp1;
    LoadSounds(_T("AniData/Datas/PlayScene_Sounds_Ryno.txt"), temp1, hWnd);

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
        LoadAnimations(_T("AniData/Datas/TitleScene_Animations.txt"),m_Animations);
        LoadSounds(_T("AniData/Datas/TitleScene_Sounds.txt"),m_Sounds,hWnd);
    }

    else if (SceneNum == 1)     // Select Scene
    {
        LoadSprites(_T("AniData/Datas/SelectScene_Sprites.txt"));
        LoadAnimations(_T("AniData/Datas/SelectScene_Animations.txt"),m_Animations);
        LoadSounds(_T("AniData/Datas/SelectScene_Sounds.txt"),m_Sounds, hWnd);

        for (int i = 0; i < 10; i++)
        {
            m_Number_ani.push_back(m_Animations["Num_" + i]);
        }
    }

    else if (SceneNum == 2)     // Play Scene
    {
        LoadSprites(_T("AniData/Datas/PlayScene_Sprites.txt"));
        LoadAnimations(_T("AniData/Datas/PlayScene_Animations_etc.txt"),m_Animations);
        LoadSounds(_T("AniData/Datas/PlayScene_Sounds.txt"), m_Sounds, hWnd);
        //LoadSounds(_T("AniData/Datas/PlayScene_Sounds_Ryno.txt"), hWnd);

        for (int i = 0; i < 10; i++)
        {
            m_Number_ani.push_back(m_Animations["Pointnum_" + i]);
        }
    }

    else                       //Ending Scene
    {
        LoadSprites(_T("AniData/Datas/EndingScene_Sprites.txt"));
        LoadAnimations(_T("AniData/Datas/EndingScene_Animations.txt"), m_Animations);
        LoadSounds(_T("AniData/Datas/EndingScene_Sounds.txt"), m_Sounds, hWnd);


        for (int i = 0; i < 10; i++)
        {
            m_Number_ani.push_back(m_Animations["Orange_" + i]);
        }

        for (int i = 1; i <= 5; i++)
        {
            m_Number_ani.push_back(m_Animations["Blue_" + i]);
        }

        for (int i = 0; i < 26; i++)
        {
            m_Alpha_ani.push_back(m_Animations["Green_" + (char)(i+65)]);
        }
       
        m_Alpha_ani.push_back(m_Animations["Green_Underbar"]);
    }
}

void DataManager::LoadWaveDatas(HWND hWnd, RECT winRect, shared_ptr<Wave> wave)
{
    wave = shared_ptr<Wave>(new Wave);

    wave->Timer = 200;
    wave->MaxMonsterNum = 10;
    wave->LimitArea = { 415, winRect.bottom };
    
    wave->SpawnArea.push_back({ -200,415,-150,winRect.bottom });
    wave->SpawnArea.push_back({ 1150,415,1200,winRect.bottom });
    
    wave->StageFinish = false;
    wave->LiveMonsters.clear();

    map<string, shared_ptr<Animation>> temp;
    LoadAnimations(_T("AniData/Datas/PlayScene_Animations_Baseball.txt"),temp);

    map<string, shared_ptr<Sound>> temp1;
    LoadSounds(_T("AniData/Datas/PlayScene_Sounds_Baseball.txt"),temp1, hWnd);

    for (int i = 0; i < wave->MaxMonsterNum; i++)
    {
        wave->DeadMonsters.push(shared_ptr<Baseball>(new Baseball(Vector3(0, 0, 0), 50, 50, 1, temp, temp1, 100)));
    }

}
