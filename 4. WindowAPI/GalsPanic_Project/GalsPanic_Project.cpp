// GalsPanic_Project.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//



#include "framework.h"
#include "GameManager.h"
#include "Player.h"
#include "GalsPanic_Project.h"
#include <vector>
#include<iostream>

#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "entry:WinMainCRTStartup /subsystem:console")
#endif // UNICODE

#define MAX_LOADSTRING 100
#define TIMER_FIRST 1

using namespace std;

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.


vector<POINT> NewPathPoints; //선을 그리는 점들
vector<vector<POINT>> ObjectPoints; // 도형을 그리기 위한 점들
vector<RECT> Colliders; // 사각형의 collider들

HBITMAP screen;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void DrawLines(vector<POINT>& vec, HDC hdc);
BOOL CheckMakeObject(vector<vector<POINT>> ObjectPoints, vector<POINT>& vec, Player* player, int& endPoint, bool & newtry);
void MakeObject(vector<POINT>& vec, Player* player, vector<vector<POINT>>& ObjectPoints, int& endPoint, bool & newtry);
BOOL NewLineStart(vector<vector<POINT>>& ObjectPoints, Player* player, int way, bool & newtry);
vector<POINT> RayCastArea(vector<vector<POINT>>& ObjectPoints, RECT window, int playerVel); //using raycast system (up, down) 

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
    LoadStringW(hInstance, IDC_GALSPANICPROJECT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GALSPANICPROJECT));

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
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GALSPANICPROJECT));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_GALSPANICPROJECT);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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

    static POINT startCenter = { 200,250 };
    static int startWidth = 150;
    static int startHeight = 100;

    static RECT recView;
    static GameManager* GM = new GameManager;
    static Player* player = GM;
    static POINT curPos = player->GetCurPos();
    static int playerVel = 5;
    static int ObjEndPoint = 0;
    static bool isNewTry = false;

    switch (message)
    {

    case WM_CREATE:
    {
        GetClientRect(hWnd, &recView);
        SetTimer(hWnd, TIMER_FIRST, 10, NULL);
        GM->StartGame(startCenter, startWidth, startHeight, player,ObjectPoints, NewPathPoints);
        cout << "Ready for Playing" << endl;

    }
    break;
    case WM_TIMER:
    {
        if (wParam == TIMER_FIRST)
        {
            POINT updatePos;
            int way;

            if (GetAsyncKeyState(VK_UP) & 0x8000) //위쪽
            {
                way = 12;
                if (player->GetWay() != 12 && player->GetWay() != 6 && NewLineStart(ObjectPoints, player, way, isNewTry))
                {
                    NewPathPoints.push_back(player->GetCurPos());
                    cout << "add line point" << endl;
                    player->PlayerPosUpdate();
                }

                updatePos = { player->GetCurPos().x, player->GetCurPos().y - playerVel };
                player->SetCurPos(updatePos);
                player->SetWay(12);
                MakeObject(NewPathPoints, player, ObjectPoints, ObjEndPoint, isNewTry);
            }

            else if (GetAsyncKeyState(VK_DOWN) & 0x8000) //아래쪽
            {
                way = 6;
                if (player->GetWay() != 6 && player->GetWay() != 12 && NewLineStart(ObjectPoints, player, way, isNewTry))
                {
                    NewPathPoints.push_back(player->GetCurPos());
                    cout << "add line point" << endl;
                    player->PlayerPosUpdate();
                }

                updatePos = { player->GetCurPos().x, player->GetCurPos().y + playerVel };
                player->SetCurPos(updatePos);
                player->SetWay(6);
                MakeObject(NewPathPoints, player, ObjectPoints, ObjEndPoint, isNewTry);
            }

            else if (GetAsyncKeyState(VK_LEFT) & 0x8000) //왼쪽
            {
                way = 9;
                if (player->GetWay() != 9 && player->GetWay() != 3 && NewLineStart(ObjectPoints, player, way, isNewTry))
                {
                    NewPathPoints.push_back(player->GetCurPos());
                    cout << "add line point" << endl;
                    player->PlayerPosUpdate();

                }

                updatePos = { player->GetCurPos().x - playerVel, player->GetCurPos().y };
                player->SetCurPos(updatePos);
                player->SetWay(9);
                MakeObject(NewPathPoints, player, ObjectPoints, ObjEndPoint, isNewTry);
            }

            else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) //오른쪽
            {
                way = 3;
                if (player->GetWay() != 3 && player->GetWay() != 9 && NewLineStart(ObjectPoints, player, way, isNewTry))
                {
                    NewPathPoints.push_back(player->GetCurPos());
                    cout << "add line point" << endl;
                    player->PlayerPosUpdate();
                }

                updatePos = { player->GetCurPos().x + playerVel, player->GetCurPos().y };
                player->SetCurPos(updatePos);
                player->SetWay(3);
                MakeObject(NewPathPoints, player, ObjectPoints, ObjEndPoint, isNewTry);
            }

            InvalidateRect(hWnd, NULL, FALSE);
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

        screen = CreateCompatibleBitmap(hdc, recView.right, recView.bottom);

        hOldBitmap = (HBITMAP)SelectObject(hMemDC, screen);

        DrawLines(NewPathPoints, hMemDC);
        GM->DrawLine(hMemDC);
        GM->PaintArea(hMemDC, ObjectPoints);
        player->PlayerCharactorUpdate(hMemDC);

        BitBlt(hdc, 0, 0, recView.right, recView.bottom, hMemDC, 0, 0, SRCCOPY);

        SelectObject(hMemDC, hOldBitmap);
        DeleteDC(hMemDC);

        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
    {
        KillTimer(hWnd, TIMER_FIRST);
        delete GM;
        PostQuitMessage(0);
    }
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

void DrawLines(vector<POINT>& vec, HDC hdc)
{
    HPEN hPen, oldPen;
    hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 255));
    oldPen = (HPEN)SelectObject(hdc, hPen);

    if (vec.size() > 1)
    {
        for (int i = 0; i < vec.size() - 1; i++)
        {
            MoveToEx(hdc, vec[i].x, vec[i].y, NULL);
            LineTo(hdc, vec[i + 1].x, vec[i + 1].y);
        }
    }

    SelectObject(hdc, oldPen);
    DeleteObject(hPen);
}

BOOL CheckMakeObject(vector<vector<POINT>> ObjectPoints, vector<POINT>& vec, Player* player, int& endPoint, bool& newtry)
{
     if (player->GetWay() == 6 || player->GetWay() == 12) //위아래
     {
         for (int i = 0; i < ObjectPoints.size(); i++)
         {
             for (int j = 0; j < ObjectPoints[i].size() - 1; j++)
             {
                 if (player->GetCurPos().y == ObjectPoints[i][j].y && ObjectPoints[i][j].y == ObjectPoints[i][j+1].y) // y값 비교
                 {
                     if (player->GetCurPos().x >= min(ObjectPoints[i][j].x, ObjectPoints[i][j + 1].x)
                         && player->GetCurPos().x <= max(ObjectPoints[i][j].x, ObjectPoints[i][j + 1].x)) //x값 비교
                     {
                         vec.push_back(player->GetCurPos());
                         newtry = false;
                         return TRUE;
                     }
                 }
             }

         }
     }

     else if (player->GetWay() == 3 || player->GetWay() == 9)//좌우
     {
         for (int i = 0; i < ObjectPoints.size(); i++)
         {
             for (int j = 0; j < ObjectPoints[i].size() - 1; j++)
             {
                 if (player->GetCurPos().x == ObjectPoints[i][j].x && ObjectPoints[i][j].x == ObjectPoints[i][j+1].x) // x값 비교
                 {
                     if (player->GetCurPos().y >= min(ObjectPoints[i][j].y, ObjectPoints[i][j+1].y)
                         && player->GetCurPos().y <= max(ObjectPoints[i][j].y, ObjectPoints[i][j + 1].y)) //y값 비교
                     {
                         vec.push_back(player->GetCurPos());
                         newtry = false;
                         return TRUE;
                     }
                 }
             }
         }
     }

    

    return FALSE;
}

void MakeObject(vector<POINT>& vec, Player* player, vector<vector<POINT>>& ObjectPoints, int& endPoint, bool& newtry)
{
    if (CheckMakeObject(ObjectPoints, vec, player, endPoint, newtry))
    {

        for (int i = 0; i < vec.size(); i++)
        {
            ObjectPoints[0].push_back(vec[i]);
        }

        //using raycast method

        vec = {};
        vec.push_back(player->GetCurPos());

    }
}

BOOL NewLineStart(vector<vector<POINT>>& ObjectPoints, Player* player, int way, bool & newtry)
{
    if (!newtry)
    {
        for (int i = 0; i < ObjectPoints.size(); i++)
        {
            for (int j = 0; j < ObjectPoints[i].size() - 1; j++)
            {
                if (way == 6 || way == 12) //위아래 이동
                {
                    if (player->GetCurPos().y == ObjectPoints[i][j].y &&
                        player->GetCurPos().y == ObjectPoints[i][j + 1].y) // y축 동일
                    {
                        newtry = true;
                        return TRUE;
                    }

                }

                else //좌우 이동
                {
                    if (player->GetCurPos().x == ObjectPoints[i][j].x &&
                        player->GetCurPos().x == ObjectPoints[i][j + 1].x) // x축 동일
                    {
                        newtry = true;
                        return TRUE;
                    }
                }
            }
        }
        return FALSE;
    }


    else
    {
        return TRUE;
    }

  

}

vector<POINT> RayCastArea(vector<vector<POINT>>& ObjectPoints, RECT window, int playerVel)
{
    vector<POINT> vec;

    for (int i = 0; i <= window.right; i += playerVel) // x ->
    {
        for (int j = 0; j <= window.bottom; j += playerVel) // y down
        {
        }

    }

    for (int i = window.right; i >= 0; i -= playerVel) // x <-
    {
        // y up
    }

    for (int i = window.right; i >= 0; i -= playerVel) // x <-
    {
        // y up
    }

    for (int i = window.right; i >= 0; i -= playerVel) // x <-
    {
        // y up
    }

    return vec;
}

