﻿// WindowAPI.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "WindowAPI.h"
#include<iostream>
#include<vector>
#include<commdlg.h>
#include<stdio.h>

#define MAX_LOADSTRING 100
#define TIMER_FIRST 1

using namespace std;

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
VOID CALLBACK AniProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);

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
    LoadStringW(hInstance, IDC_WINDOWAPI, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_MENU1));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0)) // 이벤트가 있어야함
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWAPI));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+3);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDR_MENU1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);//꼭 필요
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
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) //윈도우를 생성하는 부분
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, _T("szTitle"), WS_OVERLAPPEDWINDOW,
      300, 300, 1024, 768, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow); //윈도우가 보여짐
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
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) //키 입력 값은 변수 wParam에 저장됨 
//메세지 발생마다 새로운 함수 호출 (case문의 함수는 개별이다, 유지X)->할려면 static 함수 사용
{
    PAINTSTRUCT ps;
    HDC hdc;
    SIZE size;
    RECT rec = {50,40,200,60};
    //LPCWCHAR str = (LPCWCHAR)_T("키 눌렸다!!");
    static vector<LPTSTR> senList;
    static TCHAR sen[100];
    static int count,yPos,start,lines;

    switch (message)
    {
    case WM_CREATE: //한번 만 호출(start느낌, 초기화)
        CreateCaret(hWnd, NULL, 3, 15);
        ShowCaret(hWnd);
        count = 0;
        start = 0;
        lines = 0;
        yPos = 120;
        SetTimer(hWnd, TIMER_FIRST, 100, AniProc);
        break;
    case WM_KEYDOWN: //눌려있는 상태 값 확인
    {
        
    }
    break;
    case WM_KEYUP:
    {
        
    }
    break;
    case WM_CHAR: //문자 입력 확인
    {
        if (wParam == VK_BACK && count > 0)
        {
            count--;
        }

        else if (wParam == VK_RETURN)
        {
            LPTSTR temp = new TCHAR[count];
            int i = 0;
            while(sen[i] !=NULL)
            {
                temp[i] = sen[i];
                i++;
            }
            temp[count] = NULL;
            senList.push_back(temp);
            count = 0;
            lines++;
            sen[0] = '\0';
            if (lines >= 10)
            {
                start++;
            }
            
        }

        else
        {
            sen[count++] = wParam;
            sen[count] = NULL;
        }

        InvalidateRgn(hWnd, NULL, true);
    }
    break;

    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // 메뉴 선택을 구문 분석합니다:
        switch (wmId)
        {
        case ID_SAVECHAT:
        {

            TCHAR filter[] = _T("Every file(*.*)\0*.*\0Text file\0*.txt;*.doc\0");
            TCHAR IpstrFile[100] = _T("123");
            TCHAR str[100];

            OPENFILENAME ofn;

            memset(&ofn, 0, sizeof(OPENFILENAME));
            ofn.lStructSize = sizeof(OPENFILENAME);
            ofn.hwndOwner = hWnd;
            ofn.lpstrFilter = filter;
            ofn.lpstrFile = IpstrFile;
            ofn.nMaxFile = 100;
            ofn.lpstrInitialDir = _T(".");

            if (GetSaveFileName(&ofn) != 0)
            {
                _stprintf_s(str, _T("%s 파일로 저장하겠습니까?"), ofn.lpstrFile);
                MessageBox(hWnd, str, _T("저장하기 선택"), MB_OK);
            }
        }
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
    case WM_PAINT: //그림 띄우기
    {
        hdc = BeginPaint(hWnd, &ps);
        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...  
        if (!senList.empty())
        {
            for (int i = start; i < senList.size(); i++)
            {
                DrawText(hdc, senList[i], _tcslen(senList[i]), &rec, DT_SINGLELINE | DT_LEFT | DT_NOCLIP);
                rec.top += 20;
                rec.bottom += 20;
            }
        }
        
        GetTextExtentPoint(hdc, sen, _tcslen(sen), &size);
        TextOut(hdc, 50, 350, sen, _tcslen(sen));

        SetCaretPos(50+size.cx, 350);
        EndPaint(hWnd, &ps);
        break;
    case WM_DESTROY: //종료버튼을 누를 때 발생하는 이벤트
    {
        HideCaret(hWnd);
        DestroyCaret();
        PostQuitMessage(0);
    }
    break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam); //디폴트로 처리함
    }
    return 0;
    }
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

/*
    Q1. 채팅창에 문자열을 치고 엔터키를 누르면 문자열이 한 칸 올라가고 
    그 다음에 입력하는 데이터들은 다음줄에 보여지도록 코드를 작성해라.
    채팅 최대 목록은 10개로 재한 한다.


*/
