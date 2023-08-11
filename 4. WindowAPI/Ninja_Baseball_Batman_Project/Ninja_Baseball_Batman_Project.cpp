// Ninja_Baseball_Batman_Project.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include"Headers.h"
#include"Timers.h"

#define MAX_LOADSTRING 100

#pragma comment(lib, "msimg32.lib")
#pragma comment(lib,"winmm.lib")

using namespace std;

#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "entry:WinMainCRTStartup /subsystem:console")
#endif // UNICODE

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

map<string, shared_ptr<Sprite>> Sprites;
map<string, shared_ptr<Animation>> Animations;
map<string, shared_ptr<Sound>> Sounds;

GameManager* gameManager;
Player* curPlayer;
RECT winRect;
HBITMAP Screen;

//Animation Channel
#define CHANNELS 10
int frameChannel[CHANNELS] = {};
int totalFrame[CHANNELS] = {};
int frameTime[CHANNELS] = { 500,};

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
VOID CALLBACK AniProc0(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);
VOID CALLBACK ComboCheck(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);

void SettingTimers(HWND hWnd);
void GetSentence(int& i, char* buff, char* sentence);

void LoadSprites(const TCHAR dataFileName[100]);
void LoadAnimations(const TCHAR dataFileName[100]);
void LoadSounds(const TCHAR dataFileName[100]);

void TitleScene(HDC hdc);
void SelectScene(HDC hdc);
void PlayScene(HDC hdc);
void EndingScene(HDC hdc);

void Initalize(HWND hWnd);
void EndGame(HWND hWnd);

void (*SceneIndex)(HDC);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_NINJABASEBALLBATMANPROJECT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_NINJABASEBALLBATMANPROJECT));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}


//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_NINJABASEBALLBATMANPROJECT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_NINJABASEBALLBATMANPROJECT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      200, 200, 1024, 768, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;;

    switch (message)
    {

    case WM_CREATE:
        {
            Initalize(hWnd);
            curPlayer = new Ryno();
        }
        break;
    case WM_CHAR:
    {
        if (gameManager->GetInstance()->m_SceneNum == 0)
        {
            SceneIndex = SelectScene;
            gameManager->GetInstance()->m_SceneNum++;
        }
    }
        break;
    case WM_KEYUP:
    {
        if (wParam == VK_UP)
        {
            cout << "UP_release" << endl;
            gameManager->GetInstance()->m_ComboFlag[0] = true;
        }

        if (wParam == VK_DOWN)
        {
            cout << "DOWN_release" << endl;
            gameManager->GetInstance()->m_ComboFlag[1] = true;
        }

        if (wParam == VK_LEFT)
        {
            cout << "LEFT_release" << endl;
            gameManager->GetInstance()->m_ComboFlag[2] = true;
        }

        if (wParam == VK_RIGHT)
        {
            cout << "RIGHT_release" << endl;
            gameManager->GetInstance()->m_ComboFlag[3] = true;
        }

        if (wParam == 0x41)
        {
            cout << "ATTACK_release" << endl;
            gameManager->GetInstance()->m_ComboFlag[4] = true;
        }

        if (wParam == 0x53)
        {
            cout << "JUMP_release" << endl;
            gameManager->GetInstance()->m_ComboFlag[5] = true;
        }
    }
    break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            HDC hMemDC;
            HBITMAP hOldBitmap;

            hMemDC = CreateCompatibleDC(hdc);

            if (Screen == NULL)
                Screen = CreateCompatibleBitmap(hdc, winRect.right, winRect.bottom);

            hOldBitmap = (HBITMAP)SelectObject(hMemDC, Screen);
            /////////////////////////////////////////////////////////////////////

            SceneIndex(hMemDC);

            ////////////////////////////////////////////////////////////////////
            BitBlt(hdc, 0, 0, winRect.right, winRect.bottom, hMemDC, 0, 0, SRCCOPY);

            SelectObject(hMemDC, hOldBitmap);
            DeleteDC(hMemDC);

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        delete curPlayer;
        EndGame(hWnd);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;

}

void GetSentence(int & i, char * buff, char * sentence)
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

void SettingTimers(HWND hWnd)
{
    SetTimer(hWnd, TIMER_0, frameTime[0], AniProc0);
    SetTimer(hWnd, TIMER_1, 20, ComboCheck);
}

void LoadSprites(const TCHAR dataFileName[100])
{

    HANDLE hFile = CreateFile(dataFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, 0);

    if (hFile == NULL)
    {
        MessageBox(NULL, _T("Sprite 데이터 파일 로드 에러"), _T("에러"), MB_OK);
    }

    DWORD rbytes;
    TCHAR buff[1000] = {};
    char chbuff[1000] = {};
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
    int length = strlen(chbuff);
    while (chbuff[index++] != '\n');
    while (1)
    {
        char name[100], address[200];
        GetSentence(index, chbuff,name);
        if (buff[index] == '\0') break;
        GetSentence(index, chbuff,address);
        TCHAR uniAddress[200] = {};
        MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, address, strlen(address), uniAddress, 200);
        Sprites[name] = shared_ptr<Sprite>(new Sprite(uniAddress));
        index++;
    }

}

void LoadAnimations(const TCHAR dataFileName[100])
{
    HANDLE hFile = CreateFile(dataFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, 0);

    if (hFile == NULL)
    {
        MessageBox(NULL, _T("Animation 데이터 파일 로드 에러"), _T("에러"), MB_OK);
    }

    DWORD rbytes;
    TCHAR buff[1000] = {};
    char chbuff[1000] = {};
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
    int length = strlen(chbuff);
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
        Animations[aniName] = shared_ptr<Animation>(new Animation(Sprites[originSprite], uniAddress));
        index++;
    }

}

void LoadSounds(const TCHAR dataFileName[100])
{
}

void Initalize(HWND hWnd) // 모든 animation, sound, stage 데이터 로드하기
{
    SettingTimers(hWnd);

    GetClientRect(hWnd, &winRect);

    //게임 매니저 생성
    gameManager->GetInstance();

    //함수 포인터를 TitleSceen으로
    SceneIndex = TitleScene;

}

void TitleScene(HDC hdc) // SceneNum = 0
{
    Screen = NULL;

    Sprites.clear();
    Animations.clear();
    Sounds.clear();

    LoadSprites(_T("AniData/Datas/TitleScene_Sprites.txt"));
    LoadAnimations(_T("AniData/Datas/TitleScene_Animations.txt"));
    //모든 소리 로드

    POINT location = { 35, 0 };
    totalFrame[0] = Animations["Title_screen"]->GetFrameTotalCount();
    Animations["Title_screen"]->AniPlay(hdc, location, frameChannel[0], 1.55f);
}

void SelectScene(HDC hdc) // SceneNum = 1
{
    Screen = NULL;

    Sprites.clear();
    Animations.clear();
    Sounds.clear();

    LoadSprites(_T("AniData/Datas/SelectScene_Sprites.txt"));
    LoadAnimations(_T("AniData/Datas/SelectScene_Animations.txt"));

    for (int i = 20; i <= 900; i += 30)
    {
        for (int j = 0; j <= 630; j += 35)
        {
            Animations["Select_background"]->AniPlay(hdc, {i,j}, 0, 1.55f);
        }
    }


}

void PlayScene(HDC hdc) // SceneNum = 2
{

}

void EndingScene(HDC hdc) // SceneNum = 3
{
}


void EndGame(HWND hWnd)
{
    KillTimer(hWnd, TIMER_0);
    KillTimer(hWnd, TIMER_1);
    gameManager->Release();
}

VOID CALLBACK AniProc0(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
    frameChannel[0]++;

    if (frameChannel[0] >= totalFrame[0])
    {
        frameChannel[0] = 0;
    }

    InvalidateRect(hWnd, NULL, FALSE);
}

VOID CALLBACK ComboCheck(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
    gameManager->GetInstance()->CheckCombo(curPlayer);
}

