// SoundTest.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "SoundTest.h"
#include<Windows.h>
#include<mmsystem.h>
#include<Digitalv.h>

#define MAX_LOADSTRING 100

#pragma comment(lib,"winmm.lib")

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
DWORD LoadWAV(HWND hWnd, LPCTSTR lpszWave);

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
    LoadStringW(hInstance, IDC_SOUNDTEST, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SOUNDTEST));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SOUNDTEST));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_SOUNDTEST);
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
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

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

MCI_OPEN_PARMS      mciOpenParms; //파일을 로드
MCI_PLAY_PARMS       mciPlayParms; //파일을 재생
MCI_STATUS_PARMS   mciStatus; //파일의 상태
UINT wDeviceID = 0;

DWORD Sound1, Sound2;

MCIDEVICEID MusicID = 0;
MCI_PLAY_PARMS Play;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {
    case WM_CREATE:
    {
        Sound1 = LoadWAV(hWnd, L"test.wav");
        Sound2 = LoadWAV(hWnd, L"Sound2.wav");

        //MCIERROR        Error;
        //MCI_OPEN_PARMS Data = {};

        //Data.lpstrDeviceType = L"WaveAudio";
        //Data.lpstrElementName = _T("test.wav");

        //Error = mciSendCommandA(
        //    0,
        //    MCI_OPEN,
        //    MCI_OPEN_TYPE | MCI_OPEN_ELEMENT,
        //    (DWORD_PTR)&Data
        //);

        //if (Error == 0)
        //{
        //    MusicID = Data.wDeviceID;
        //}
    }
        break;
    case WM_KEYDOWN:
    {
        switch (wParam)
        {
        case VK_F1:
           Sound1 = mciSendCommand(1, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlayParms);
           // Sound1 = mciSendCommand(1, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
            break;
        case VK_F2:
            Sound1 = mciSendCommand(1, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
            break;

        //case VK_F1:
        //    PlaySoundA("test.wav", nullptr, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT);
        //    break;

        //case VK_F2:
        //    PlaySoundA(nullptr, nullptr, 0);
        //    break;

        //case VK_F3:
        //   Play = {};

        //    mciSendCommandA(MusicID, MCI_PLAY, MCI_NOTIFY, (DWORD_PTR)&Play);
        //     break;
        //// 정지
        //case VK_F4:
        //    mciSendCommandA(MusicID, MCI_PAUSE, 0, 0);
        //    break;

        //// 처음으로
        //case VK_F5:
        //    mciSendCommandA(MusicID, MCI_SEEK, MCI_SEEK_TO_START, 0);
        //    break;
        default:
            break;
        }
    }

    case WM_KEYUP:
    {
        switch (wParam)
        {
        case VK_F1:
            //Sound1 = mciSendCommand(1, MCI_RESUME, 0, (DWORD)(LPVOID)NULL);
            //Sound1 = mciSendCommand(1, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
            break;
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
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        //사운드 파일 제거
        //mciSendCommandA(MusicID, MCI_CLOSE, 0, 0);
        if (wDeviceID > 0)
        {
            mciSendCommand(1, MCI_CLOSE, 0, (DWORD)(LPVOID)NULL);
            mciSendCommand(2, MCI_CLOSE, 0, (DWORD)(LPVOID)NULL);
        }
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

DWORD LoadWAV(HWND hWnd, LPCTSTR lpszWave)
{
    DWORD Result;
    //WaveAudio 대신 MPEGVideo를 사용하면 mp3 형식을 재생합니다.
    mciOpenParms.lpstrDeviceType = L"WaveAudio";
    mciOpenParms.lpstrElementName = lpszWave;
    Result = mciSendCommand(wDeviceID, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD)(LPVOID)&mciOpenParms);
    if (Result)
        return Result;
    wDeviceID = mciOpenParms.wDeviceID;
    mciPlayParms.dwCallback = (DWORD)hWnd;
    if (Result)
        return Result;
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
