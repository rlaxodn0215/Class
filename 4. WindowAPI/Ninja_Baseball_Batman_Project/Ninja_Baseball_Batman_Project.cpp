// Ninja_Baseball_Batman_Project.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include<Windows.h>
#include "Ninja_Baseball_Batman_Project.h"
#include"Sprite.h"
#include"Animation.h"
#include"Collider.h"
#include"Charactor.h"
#include"GameManager.h"
#include"Sound.h"
#include"Vector3.h"
#include<iostream>

#define MAX_LOADSTRING 100
#define TIMER 1

#pragma comment(lib, "msimg32.lib")

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

GameManager* gameManager;
HBITMAP Screen;
RECT winRect;
MCIDEVICEID MusicID = 0;

MCI_OPEN_PARMS      mciOpen; //파일을 로드
MCI_PLAY_PARMS       mciPlay; //파일을 재생
MCI_STATUS_PARMS   mciStatus; //파일의 상태

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
VOID CALLBACK Timer(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);

void Initalize(HWND hWnd);
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

PAINTSTRUCT ps;
HDC hdc;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {

    case WM_CREATE:
        {
            Initalize(hWnd);
            SetTimer(hWnd, TIMER, 20, Timer);
        }
        break;
    case WM_CHAR:
        if (gameManager !=NULL &&  gameManager->GetInstance()->m_SceneNum == 0)
        {
            gameManager->GetInstance()->m_Scene = &GameManager::SelectScene;
            gameManager->GetInstance()->m_SceneNum++;

            gameManager->GetInstance()->Sprites.clear();
            gameManager->GetInstance()->Animations.clear();
            gameManager->GetInstance()->Sounds.clear();
        }
        break;
    case WM_KEYUP:
    {
        gameManager->GetInstance()->CheckKeyRelease(wParam);
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

            (gameManager->*(gameManager->GetInstance()->m_Scene))(hWnd, hMemDC, Screen, winRect);

            ////////////////////////////////////////////////////////////////////
            BitBlt(hdc, 0, 0, winRect.right, winRect.bottom, hMemDC, 0, 0, SRCCOPY);

            SelectObject(hMemDC, hOldBitmap);
            DeleteDC(hMemDC);


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

void Initalize(HWND hWnd)
{
    GetClientRect(hWnd, &winRect);
    gameManager = GameManager::GetInstance(); // static 함수로 선언되어 gameManager이 nullptr이 되지 않는다.
}

void EndGame(HWND hWnd)
{
    KillTimer(hWnd, TIMER);
    gameManager->Release();
}

VOID CALLBACK Timer(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
    HDC temp = GetDC(hWnd);
    gameManager->GetInstance()->CheckKeyInput(temp, winRect);
        
    if(gameManager->GetInstance()->m_Player !=NULL)
        gameManager->GetInstance()->Gravity(2);

    if (gameManager->GetInstance()->m_TimerFrame >= 1000)
        gameManager->GetInstance()->m_TimerFrame = 0;
    gameManager->GetInstance()->m_TimerFrame++;

    InvalidateRect(hWnd, NULL, FALSE);
}

