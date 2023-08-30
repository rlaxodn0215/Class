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
#include"DataManager.h"
#include"Sound.h"
#include"Vector3.h"
#include<iostream>
//#include<stdlib.h>
//#include<crtdbg.h>
//#include<vld.h>

#define MAX_LOADSTRING 100
#define TIMER 1

#pragma comment(lib, "msimg32.lib")

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

GameManager* gameManager;                       // 게임 매니저 싱글톤 객체
DataManager* dataManager;                       // 데이터 매니저
HBITMAP Screen;                                 // 화면 저장용 비트맵
RECT winRect;                                   // 화면의 가로, 세로

bool PlayerEternal = false;
bool PlayerNoHitAni = false;
bool OnCollider = false;

int MonsterSpawnTime = 150;
int MonsterHp = 50; // Max & Cur
int MonsterAttack = 10;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

VOID CALLBACK Timer(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime); // 타이머 콜백으로 선언
INT_PTR CALLBACK Control(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK Setting(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

void Initalize(HWND hWnd); // 타이머 초기화, 게임 매니저 생성
void EndGame(HWND hWnd);    //타이머 해제, 게임 매니저 해제


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


    while (true) {
        if (!GetMessage(&msg, nullptr, 0, 0)) {
            DWORD dwError = GetLastError();
            if (dwError != 0) { // : 오류 발생시
                char errorString[256];
                sprintf_s(errorString, "GetMessage failed with error code %d", dwError);
                MessageBox(nullptr, (LPCWSTR)errorString, L"Error", MB_OK | MB_ICONERROR);
                break;
            }
            else {
                // : 0 - 종료
                break;
            }
        }

        // : 
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    //// 기본 메시지 루프입니다:
    //while (GetMessage(&msg, nullptr, 0, 0))
    //{
    //    if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
    //    {
    //        TranslateMessage(&msg);
    //        DispatchMessage(&msg);
    //    }
    //}

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
    HDC hdc;

    switch (message)
    {
    case WM_CREATE:
        Initalize(hWnd);
        SetTimer(hWnd, TIMER, 20, Timer);
        break;
    case WM_KEYUP:
        if(gameManager !=NULL)
            gameManager->GetInstance()->CheckKeyRelease(hWnd,wParam,dataManager);
        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case ID_CONTROL:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_HowToPlay), hWnd, Control);
                break;
            case ID_SETTING:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_Settings), hWnd, Setting);
                break;
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

            (gameManager->*(gameManager->GetInstance()->m_Scene))(hWnd, hMemDC, dataManager); // 더블 버퍼링으로 해당 씬 화면 출력

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
    if (gameManager == NULL)
    {
        DWORD dwError = GetLastError();
        MessageBox(NULL, _T("게임 매니저 객체 생성 실패"), _T("에러"), MB_OK);
        exit(1);
    }

    gameManager->GetInstance()->m_WinRect = winRect;

    dataManager = DataManager::GetInstance();
    if (dataManager == NULL)
    {
        DWORD dwError = GetLastError();
        MessageBox(NULL, _T("데이터 매니저 객체 생성 실패"), _T("에러"), MB_OK);
        exit(1);
    }
}

void EndGame(HWND hWnd)
{
    KillTimer(hWnd, TIMER);

    if(gameManager !=NULL)
        gameManager->Release();
    if (dataManager != NULL)
        dataManager->Release();
}

VOID CALLBACK Timer(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
    if (gameManager == NULL)
    {
        DWORD dwError = GetLastError();
        MessageBox(NULL, _T("게임 매니저 초기화 에러"), _T("에러"), MB_OK);
        return;
    }

    if (dataManager == NULL)
    {
        DWORD dwError = GetLastError();
        MessageBox(NULL, _T("데이터 매니저 초기화 에러"), _T("에러"), MB_OK);
        return;
    }

    GameManager* gameInstance = gameManager->GetInstance();
    DataManager* dataInstance = dataManager->GetInstance();

    HDC temp = GetDC(hWnd);

    gameInstance->GetInstance()->CheckKeyInput(hWnd, temp, dataInstance); //키 입력 선언
        
    if(gameInstance->GetInstance()->m_Player !=NULL)
        gameInstance->GetInstance()->Gravity(2); // 중력 만들기

    if (gameInstance->GetInstance()->m_TimerFrame >= 10000)
        gameInstance->GetInstance()->m_TimerFrame = 0;
    else
        gameInstance->GetInstance()->m_TimerFrame++; //타이머 작동

    InvalidateRect(hWnd, NULL, FALSE); // 화면 갱신
    ReleaseDC(hWnd, temp);
}

INT_PTR CALLBACK Control(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
    {
        TCHAR control[200] = {};

        HANDLE hFile = CreateFile(_T("Control.txt"), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, 0);

        if (hFile == NULL)
        {
            MessageBox(NULL, _T("조작법 데이터 파일 로드 에러"), _T("에러"), MB_OK);
        }

        DWORD rbytes;
        size_t convertedChars = 0;

        if (ReadFile(hFile, control, sizeof(control), &rbytes, NULL))
        {
            if (control[0] == 0xFEFF)
            {
                _LARGE_INTEGER temp;
                temp.QuadPart = 2;
                if(SetFilePointerEx(hFile, temp, NULL, FILE_BEGIN))
                    ReadFile(hFile, control, sizeof(control), &rbytes, NULL);
                else
                {
                    MessageBox(NULL, _T("파일 커서 이동 에러"), _T("에러"), MB_OK);
                    CloseHandle(hFile); // << :핸들 닫기
                    return (INT_PTR)TRUE;
                }
            }
        }

        else
        {
            MessageBox(NULL, _T("파일 읽기 에러"), _T("에러"), MB_OK);
            CloseHandle(hFile); // << :핸들 닫기
            return (INT_PTR)TRUE;
        }

        SetDlgItemText(hDlg, IDC_CONTROL, control);
        CloseHandle(hFile);
    }
    return (INT_PTR)TRUE;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDOK:
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

INT_PTR CALLBACK Setting(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
    {
        CheckDlgButton(hDlg,IDC_CHECKPLAYERHP, PlayerEternal);
        CheckDlgButton(hDlg, IDC_CHECKPLAYERNOHIT, PlayerNoHitAni);
        CheckDlgButton(hDlg, IDC_ONCOLLIDER, OnCollider);
        SetDlgItemInt(hDlg, IDC_EDIT_SPAWN, MonsterSpawnTime*20, FALSE);
        SetDlgItemInt(hDlg, IDC_EDIT_MONSTER_HP, MonsterHp, FALSE);
        SetDlgItemInt(hDlg, IDC_EDIT_ATTACK, MonsterAttack, FALSE);
    }
    return (INT_PTR)TRUE;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_CHECKPLAYERHP:
            PlayerEternal = !PlayerEternal;
            break;
        case IDC_CHECKPLAYERNOHIT:
            PlayerNoHitAni = !PlayerNoHitAni;
            break;
        case IDC_ONCOLLIDER:
            OnCollider = !OnCollider;
            break;
        case IDOK:
            MonsterSpawnTime = (GetDlgItemInt(hDlg, IDC_EDIT_SPAWN, NULL, FALSE))/20;
            MonsterHp = GetDlgItemInt(hDlg, IDC_EDIT_MONSTER_HP, NULL, FALSE);
            MonsterAttack = GetDlgItemInt(hDlg, IDC_EDIT_ATTACK, NULL, FALSE);

            GameManager* gm = gameManager->GetInstance();

            if (gm && gm->m_Wave)
            {
                gm->m_Wave->TimeInterval = MonsterSpawnTime;

                for (auto iter : gm->m_Wave->WaveMonsters)
                {
                    iter->SetCurHP(MonsterHp);
                    iter->SetMaxHP(MonsterHp);
                    iter->SetAttack(MonsterAttack);
                }
            }

            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

