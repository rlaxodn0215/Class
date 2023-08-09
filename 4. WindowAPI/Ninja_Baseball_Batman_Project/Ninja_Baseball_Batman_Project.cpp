// Ninja_Baseball_Batman_Project.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include"Headers.h"
#include"Timers.h"

#define MAX_LOADSTRING 100

#pragma comment(lib, "msimg32.lib")
#pragma comment(lib,"winmm.lib")

using namespace std;

//#ifdef UNICODE
//#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
//#else
//#pragma comment(linker, "entry:WinMainCRTStartup /subsystem:console")
//#endif // UNICODE

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

map<string, shared_ptr<Sprite>> all_Sprites;
map<string, shared_ptr<Animation>> all_Animations;
map<string, shared_ptr<Sound>> all_Sounds;
map<string, shared_ptr<Charactor>> all_Charactors;
map<string, vector<RECT>> all_LimitAreas;

GameManager* gameManager;
Player* curPlayer;
Stage* stage;
int curStageNum = 0;
RECT winRect;
HBITMAP Screen;

//Animation Channel
#define CHANNELS 10
int frameChannel[CHANNELS] = {};
int totalFrame[CHANNELS] = {};
int frameTime[CHANNELS] = { 500,50,100, 100,100, 100,100,100,100,100};

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
VOID CALLBACK AniProc0(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);
VOID CALLBACK AniProc1(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);
VOID CALLBACK AniProc2(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);
VOID CALLBACK AniProc3(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);
VOID CALLBACK AniProc4(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);
VOID CALLBACK AniProc5(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);
VOID CALLBACK AniProc6(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);
VOID CALLBACK AniProc7(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);
VOID CALLBACK AniProc8(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);
VOID CALLBACK AniProc9(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);

void Initalize(HWND hWnd); // 모든 animation, sound, stage 데이터 로드하기
void PlayStage(HDC hdc, int stageNum);
void EndGame(HWND hWnd);


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
      200, 200, 700, 500, nullptr, nullptr, hInstance, nullptr);

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
    HDC hdc;

    switch (message)
    {

    case WM_CREATE:
        {
            GetClientRect(hWnd, &winRect);
            Initalize(hWnd);
        }
        break;
    case WM_CHAR:
    {
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
            PlayStage(hdc, curStageNum);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
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


void PlayStage(HDC hdc, int stageNum)
{
    HDC hMemDC;
    HBITMAP hOldBitmap;

    hMemDC = CreateCompatibleDC(hdc);

    if(Screen == NULL)
    Screen = CreateCompatibleBitmap(hdc, winRect.right, winRect.bottom);

    hOldBitmap = (HBITMAP)SelectObject(hMemDC, Screen);

    if (stageNum == 0)
    {
        POINT location = { (winRect.left + winRect.right) / 2 - 20, (winRect.top + winRect.bottom) / 2 };
        totalFrame[0] = stage->GetUI()["title_screen"]->GetFrameTotalCount();
        stage->GetUI()["title_screen"]->AniPlay(hMemDC, location, frameChannel[0], 1.0f);

        POINT location1 = { (winRect.left + winRect.right) / 2 - 35, (winRect.top + winRect.bottom) / 2 };
        totalFrame[1] = stage->GetUI()["Ryno_walk"]->GetFrameTotalCount();
        stage->GetUI()["Ryno_walk"]->AniPlay(hMemDC, location1, frameChannel[1], 1.0f);

        POINT location2 = { (winRect.left + winRect.right) / 2 + 100, (winRect.top + winRect.bottom) / 2 };
        totalFrame[2] = stage->GetUI()["Baseball_walk"]->GetFrameTotalCount();
        stage->GetUI()["Baseball_walk"]->AniPlay(hMemDC, location2, frameChannel[2], 1.0f);

        POINT location3 = { (winRect.left + winRect.right) / 2 - 50, (winRect.top + winRect.bottom) / 2 - 100 };
        totalFrame[3] = stage->GetUI()["Bat_hit"]->GetFrameTotalCount();
        stage->GetUI()["Bat_hit"]->AniPlay(hMemDC, location3, frameChannel[3], 1.0f);
    }

    BitBlt(hdc, 0, 0, winRect.right, winRect.bottom, hMemDC, 0, 0, SRCCOPY);

    SelectObject(hMemDC, hOldBitmap);
    DeleteDC(hMemDC);
}

void Initalize(HWND hWnd) // 모든 animation, sound, stage 데이터 로드하기
{
    //타이머 설정
    SetTimer(hWnd, TIMER_0, frameTime[0], AniProc0);
    SetTimer(hWnd, TIMER_1, frameTime[1], AniProc1);
    SetTimer(hWnd, TIMER_2, frameTime[2], AniProc2);
    SetTimer(hWnd, TIMER_3, frameTime[3], AniProc3);
    SetTimer(hWnd, TIMER_4, frameTime[4], AniProc4);
    SetTimer(hWnd, TIMER_5, frameTime[5], AniProc5);
    SetTimer(hWnd, TIMER_6, frameTime[6], AniProc6);
    SetTimer(hWnd, TIMER_7, frameTime[7], AniProc7);
    SetTimer(hWnd, TIMER_8, frameTime[8], AniProc8);
    SetTimer(hWnd, TIMER_9, frameTime[9], AniProc9);

    //모든 스프라이트 로드
    all_Sprites["Title_Screen"] = shared_ptr<Sprite>(new Sprite(_T("Image/UI/titlescreen.bmp")));
    all_Sprites["Player_Select"] = shared_ptr<Sprite>(new Sprite(_T("Image/UI/PlayerSelect.bmp")));
    all_Sprites["Object"] = shared_ptr<Sprite>(new Sprite(_T("Image/UI/Object.bmp")));
    all_Sprites["HUD"] = shared_ptr<Sprite>(new Sprite(_T("Image/UI/HUD.bmp")));
    all_Sprites["Ryno"] = shared_ptr<Sprite>(new Sprite(_T("Image/Player/Ryno.bmp")));
    all_Sprites["Baseball"] = shared_ptr<Sprite>(new Sprite(_T("Image/Monster/Baseball.bmp")));
    all_Sprites["Bat"] = shared_ptr<Sprite>(new Sprite(_T("Image/Monster/Bat.bmp")));
    all_Sprites["Cards"] = shared_ptr<Sprite>(new Sprite(_T("Image/Monster/Cards.bmp")));
    all_Sprites["WindyPlane"] = shared_ptr<Sprite>(new Sprite(_T("Image/Monster/WindyPlane.bmp")));
    all_Sprites["Background"] = shared_ptr<Sprite>(new Sprite(_T("Image/Background/Background.bmp")));
    all_Sprites["Background1"] = shared_ptr<Sprite>(new Sprite(_T("Image/Background/Background1.bmp")));

    //모든 애니메이션 로드
    all_Animations["title_screen"] = shared_ptr<Animation>(new Animation(all_Sprites["Title_Screen"], _T("AniData/UI/titlescreen.txt")));
    all_Animations["Ryno_walk"]= shared_ptr<Animation>(new Animation(all_Sprites["Ryno"], _T("AniData/Player/Ryno/Ryno_walk.txt")));
    all_Animations["Baseball_walk"]= shared_ptr<Animation>(new Animation(all_Sprites["Baseball"], _T("AniData/Monster/Baseball/Baseball_walk.txt")));
    all_Animations["Bat_hit"]= shared_ptr<Animation>(new Animation(all_Sprites["Bat"], _T("AniData/Monster/Bat/Bat_hit.txt")));

    //모든 소리 로드

    //모든 몬스터 로드

    //모든 제한 영역 로드

    //각stage에 필요한 데이터 넣기
    //stage0 -> 시작 화면
    Animation* stageArea = NULL;
    vector<RECT> limitArea;
    map<string, shared_ptr<Sound>> bgm;
    map<string, shared_ptr<Animation>> ui;
    ui["title_screen"] = all_Animations["title_screen"];
    ui["Ryno_walk"] = all_Animations["Ryno_walk"];
    ui["Baseball_walk"] = all_Animations["Baseball_walk"];
    ui["Bat_hit"] = all_Animations["Bat_hit"];

    map<string, shared_ptr<Animation>> background;
    vector<Charactor> stageCharactors;

    //stage1 -> 선택 화면


    //게임 매니저에 stage0 로드
    stage = new Stage(0, stageArea, limitArea, bgm, ui, background, stageCharactors);

    gameManager->GetInstance();
    gameManager->GetInstance()->m_Stage = stage;

}

void EndGame(HWND hWnd)
{
    KillTimer(hWnd, TIMER_0);
    KillTimer(hWnd, TIMER_1);
    KillTimer(hWnd, TIMER_2);
    KillTimer(hWnd, TIMER_3);
    KillTimer(hWnd, TIMER_4);
    KillTimer(hWnd, TIMER_5);
    KillTimer(hWnd, TIMER_6);
    KillTimer(hWnd, TIMER_7);
    KillTimer(hWnd, TIMER_8);
    KillTimer(hWnd, TIMER_9);
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

VOID CALLBACK AniProc1(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
    frameChannel[1]++;

    if (frameChannel[1] >= totalFrame[1])
    {
        frameChannel[1] = 0;
    }

    InvalidateRect(hWnd, NULL, FALSE);
}

VOID CALLBACK AniProc2(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
    frameChannel[2]++;

    if (frameChannel[2] >= totalFrame[2])
    {
        frameChannel[2] = 0;
    }

    InvalidateRect(hWnd, NULL, FALSE);
}

VOID CALLBACK AniProc3(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
    frameChannel[3]++;

    if (frameChannel[3] >= totalFrame[3])
    {
        frameChannel[3] = 0;
    }

    InvalidateRect(hWnd, NULL, FALSE);
}

VOID CALLBACK AniProc4(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
    frameChannel[4]++;

    if (frameChannel[4] >= totalFrame[4])
    {
        frameChannel[4] = 0;
    }

    InvalidateRect(hWnd, NULL, FALSE);
}

VOID CALLBACK AniProc5(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
    frameChannel[5]++;

    if (frameChannel[5] >= totalFrame[5])
    {
        frameChannel[5] = 0;
    }

    InvalidateRect(hWnd, NULL, FALSE);
}

VOID CALLBACK AniProc6(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
    frameChannel[6]++;

    if (frameChannel[6] >= totalFrame[6])
    {
        frameChannel[6] = 0;
    }

    InvalidateRect(hWnd, NULL, FALSE);
}

VOID CALLBACK AniProc7(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
    frameChannel[7]++;

    if (frameChannel[7] >= totalFrame[7])
    {
        frameChannel[7] = 0;
    }

    InvalidateRect(hWnd, NULL, FALSE);
}

VOID CALLBACK AniProc8(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
    frameChannel[8]++;

    if (frameChannel[8] >= totalFrame[8])
    {
        frameChannel[8] = 0;
    }

    InvalidateRect(hWnd, NULL, FALSE);
}

VOID CALLBACK AniProc9(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
    frameChannel[9]++;

    if (frameChannel[9] >= totalFrame[9])
    {
        frameChannel[9] = 0;
    }

    InvalidateRect(hWnd, NULL, FALSE);
}
