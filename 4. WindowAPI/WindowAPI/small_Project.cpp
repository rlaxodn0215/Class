// WindowAPI.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "WindowAPI.h"
#include "CObject.h"
#include<iostream>
#include<vector>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<commdlg.h>
#include<stdio.h>

#define MAX_LOADSTRING 100
#define TIMER_FIRST 1
#define TIMER_SECOND 2

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
void OutFormFile(TCHAR filename[], HWND hwnd);


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
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWAPI));

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

    return (int)msg.wParam;
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

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWAPI));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINDOWAPI);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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
        200, 200, 1024, 768, nullptr, nullptr, hInstance, nullptr);

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
    //LPCWCHAR str = (LPCWCHAR)_T("키 눌렸다!!");

    static RECT recView;
    static POINT mousePos;
    static vector<CObject*> obgs;
    enum OBJECT { CIRCLE, RECTANGLE, STAR, NONE };
    static int randNum = NONE, randRadius;
    static int verson = 1;

    srand(time(NULL));

    switch (message)
    {
    case WM_CREATE: //한번 만 호출(start느낌, 초기화)
    {
        GetClientRect(hWnd, &recView);
        SetTimer(hWnd, TIMER_FIRST, 30, NULL);
    }
    break;
    case WM_TIMER:
    {
        switch (wParam)
        {
        case TIMER_FIRST:
        {
            if (verson == 1)
            {
                
                for (int i = 0; i < obgs.size(); i++)
                {
                    obgs[i]->Update(hWnd);
                    obgs[i]->Collison(recView, obgs);
                }
                
            }

            else if (verson == 2)
            {
                for (int i = 0; i < obgs.size(); i++)
                    obgs[i]->Merge(recView, obgs);

                for (int i = 0; i < obgs.size(); i++)
                    obgs[i]->Update(hWnd);
            }

            else if (verson == 3)
            {

            }


        }
        break;

        }
        break;
    case WM_KEYDOWN: //눌려있는 상태 값 확인
    {
        if (wParam == 0x31) //1번 모드
        {
            verson = 1;
        }

        else if (wParam == 0x32) //2번 모드
        {
            verson = 2;
        }

        else if (wParam == 0x33) //3번 모드
        {
            verson = 3;
        }
    }
    break;
    case WM_KEYUP:
    {

    }
    break;
    case WM_LBUTTONDOWN:
    {
        mousePos.x = LOWORD(lParam);
        mousePos.y = HIWORD(lParam);

        CObject* Obj;

        if (randNum == 0) //원
        {
            CObject* Obj = new CCircle(mousePos);
            obgs.push_back(Obj);
        }

        else if (randNum == 1) //사각형
        {
            CObject* Obj = new CRectangle(mousePos);
            obgs.push_back(Obj);
        }

        else if (randNum == 2) //별
        {
            CObject* Obj = new CStar(mousePos);
            obgs.push_back(Obj);
        }


        InvalidateRect(hWnd, NULL, TRUE);
    }
    break;

    case WM_LBUTTONUP:
    {

    }
    break;
    case WM_MOUSEMOVE:
    {

    }
    break;
    case WM_CHAR: //문자 입력 확인
    {

    }
    break;

    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // 메뉴 선택을 구문 분석합니다:
        switch (wmId)
        {
        case ID_DRAW_CIRCLE:
        {
            int temp = randNum;
            int ans = MessageBox(hWnd, _T("원 그릴래?"), _T("도형선택"), MB_YESNOCANCEL);
            if (ans == IDYES)
            {
                randNum = CIRCLE;
            }

            else if (ans == IDNO)
            {
                randNum = NONE;
            }

            else
            {
                randNum = temp;
            }

        }
        break;
        case ID_DRAW_RECTANGLE:
        {
            randNum = RECTANGLE;
        }
        break;
        case ID_DRAW_STAR:
        {
            randNum = STAR;
        }
        case ID_FILEOPEN:
        {

            TCHAR filter[] = _T("Every file(*.*)\0*.*\0Text file\0*.txt;*.doc\0");
            TCHAR IpstrFile[100] = _T("");
            TCHAR str[100];

            OPENFILENAME ofn;

            memset(&ofn, 0, sizeof(OPENFILENAME));
            ofn.lStructSize = sizeof(OPENFILENAME);
            ofn.hwndOwner = hWnd;
            ofn.lpstrFilter = filter;
            ofn.lpstrFile = IpstrFile;
            ofn.nMaxFile = 100;
            ofn.lpstrInitialDir = _T(".");
            if (GetOpenFileName(&ofn) != 0)
            {
                //_stprintf_s(str,_T("%s 파일을 열겠습니까?",ofn.IpstrFile));
                OutFormFile(ofn.lpstrFile, hWnd);
                //MessageBox(hWnd, str, _T("파일선택"), MB_OK);
            }
        }
            break;
        break;
        case IDM_ABOUT: //도움말->정보
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT: //끝내기
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

        for (int i = 0; i < obgs.size(); i++)
        {
            obgs[i]->Draw(hdc);
        }

        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY: //종료버튼을 누를 때 발생하는 이벤트
    {

        KillTimer(hWnd, TIMER_FIRST);
        PostQuitMessage(0);
    }
    break;
    default:
    {
        return DefWindowProc(hWnd, message, wParam, lParam); //디폴트로 처리함
    }
    break;

    return 0;

    }
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

void OutFormFile(TCHAR filename[], HWND hWnd)
{
    FILE* fPtr;
    HDC hdc;
    int line;
    TCHAR buffer[500];
    line = 0;
    hdc = GetDC(hWnd);
#ifdef _UNICODE
    _tfopen_s(&fPtr, filename, _T("r, ccs=UNICODE"));
#else
    - _tfopen_s(&fPtr, filename, _T("r"));
#endif 
    while(_fgetts(buffer,100,fPtr)!=NULL)
    {
        if (buffer[_tcslen(buffer) - 1] == _T('\n'))
            buffer[_tcslen(buffer) - 1] = NULL;
        TextOut(hdc, 0, line * 20, buffer, _tcsclen(buffer));
        line++;
    }

    fclose(fPtr);
    ReleaseDC(hWnd, hdc);

}
