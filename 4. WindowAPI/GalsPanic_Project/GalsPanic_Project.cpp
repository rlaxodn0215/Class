// GalsPanic_Project.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//



#include "framework.h"
#include "GameManager.h"
#include "Player.h"
#include "GalsPanic_Project.h"
#include <vector>
#include<list>
#include<iostream>
#include<math.h>

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

vector<POINT> PlayerPathPoints; //선을 그리는 점들
vector<POINT> AreaPoints; // 도형을 그리기 위한 점들

HBITMAP screen;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void DrawLines(vector<POINT> & vec, HDC hdc); //플레이어가 새로운 영역에 들어갈 때 선을 그려준다
BOOL PlayerInAreaLine(vector<POINT> & AreaPoints, Player* player, int& lineNum, bool& isVertical, int way);// 플레이어가 영역 선상에 있는지 확인
BOOL LineStart(Player* player, vector<POINT> & PlayerPathPoints, int way, bool isVertical); // 새로운 도형을 만들려고 시작 할 때 시작 위치와 선 번호를 알려준다
BOOL LineEnd(Player* player, vector<POINT> & PlayerPathPoints); // 새로운 도형을 만들려고 끝날 때 끝난 위치와 선 번호를 알려준다
BOOL PlayerDead(vector<POINT> & PlayerPathPoints, Player* player); //선 끼리 충돌하면 플레이어 사망
void MakeArea(vector<POINT>& PlayerPathPoints, vector<POINT>& AreaPoints, int startLineNum, int endLineNum); //도형을 만드는 함수
BOOL Collision(vector<POINT>& AreaPoints, Player* player);

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
    static int playerLineNum = 0;
    static int startLineNum = 0;
    static int endLineNum = 0;

    static bool isInArea=true;
    static bool isLineVertical=true;
    static bool isLineStart = false;
    


    switch (message)
    {

    case WM_CREATE:
    {
        GetClientRect(hWnd, &recView);
        SetTimer(hWnd, TIMER_FIRST, 10, NULL);
        GM->StartGame(startCenter, startWidth, startHeight, player,AreaPoints);
        cout << "Ready for Playing" << endl;

    }
    break;
    case WM_TIMER:
    {
        if (wParam == TIMER_FIRST)
        {
            POINT updatePos;

            if (GetAsyncKeyState(VK_UP) & 0x8000) //위쪽
            {
                if (isLineStart)
                {
                    PlayerDead(PlayerPathPoints, player);

                    if (player->GetWay() != 6 && player->GetWay() != 12)
                    {
                        startLineNum = playerLineNum;
                        PlayerPathPoints.push_back(player->GetCurPos());
                        cout << "add line point (up)" << endl;
                        player->PlayerPosUpdate();
                    }
                }


                player->SetWay(12);
                isInArea = PlayerInAreaLine(AreaPoints, player, playerLineNum, isLineVertical, player->GetWay());

                if (isInArea && isLineStart)
                {
                    LineEnd(player, PlayerPathPoints);
                    endLineNum = playerLineNum;
                    isLineStart = false;
                    MakeArea(PlayerPathPoints, AreaPoints,startLineNum,endLineNum);
                }

                if(!isLineStart)
                    isLineStart=LineStart(player, PlayerPathPoints, player->GetWay(), isLineVertical);


                updatePos = { player->GetCurPos().x, player->GetCurPos().y - playerVel };
                player->SetCurPos(updatePos);
            }

            else if (GetAsyncKeyState(VK_DOWN) & 0x8000) //아래쪽
            {
                if (isLineStart)
                {
                    PlayerDead(PlayerPathPoints, player);

                    if (player->GetWay() != 6 && player->GetWay() != 12)
                    {
                        startLineNum = playerLineNum;
                        PlayerPathPoints.push_back(player->GetCurPos());
                        cout << "add line point (down)" << endl;
                        player->PlayerPosUpdate();
                    }
                }

                player->SetWay(6);
                isInArea = PlayerInAreaLine(AreaPoints, player, playerLineNum, isLineVertical, player->GetWay());

                if (isInArea && isLineStart)
                {
                    LineEnd(player, PlayerPathPoints);
                    endLineNum = playerLineNum;
                    isLineStart = false;
                    MakeArea(PlayerPathPoints, AreaPoints, startLineNum, endLineNum);
                }

                if (!isLineStart)
                    isLineStart = LineStart(player, PlayerPathPoints, player->GetWay(), isLineVertical);

                updatePos = { player->GetCurPos().x, player->GetCurPos().y + playerVel };
                player->SetCurPos(updatePos);
            }

            else if (GetAsyncKeyState(VK_LEFT) & 0x8000) //왼쪽
            {
                if (isLineStart)
                {
                    PlayerDead(PlayerPathPoints, player);

                    if (player->GetWay() != 3 && player->GetWay() != 9)
                    {
                        startLineNum = playerLineNum;
                        PlayerPathPoints.push_back(player->GetCurPos());
                        cout << "add line point (left)" << endl;
                        player->PlayerPosUpdate();
                    }
                }

                player->SetWay(9);
                isInArea = PlayerInAreaLine(AreaPoints, player, playerLineNum, isLineVertical, player->GetWay());

                if (isInArea && isLineStart)
                {
                    LineEnd(player, PlayerPathPoints);
                    endLineNum = playerLineNum;
                    isLineStart = false;
                    MakeArea(PlayerPathPoints, AreaPoints, startLineNum, endLineNum);
                }

                if (!isLineStart)
                    isLineStart = LineStart(player, PlayerPathPoints, player->GetWay(), isLineVertical);

                updatePos = { player->GetCurPos().x - playerVel, player->GetCurPos().y };
                player->SetCurPos(updatePos);
            }

            else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) //오른쪽
            {
                if (isLineStart)
                {
                    PlayerDead(PlayerPathPoints, player);

                    if (player->GetWay() != 3 && player->GetWay() != 9)
                    {
                        startLineNum = playerLineNum;
                        PlayerPathPoints.push_back(player->GetCurPos());
                        cout << "add line point (right)" << endl;
                        player->PlayerPosUpdate();
                    }
                }

                player->SetWay(3);
                isInArea = PlayerInAreaLine(AreaPoints, player, playerLineNum, isLineVertical, player->GetWay());

                if (isInArea && isLineStart)
                {
                    LineEnd(player, PlayerPathPoints);
                    endLineNum = playerLineNum;
                    isLineStart = false;
                    MakeArea(PlayerPathPoints, AreaPoints, startLineNum, endLineNum);
                }

                if (!isLineStart)
                    isLineStart = LineStart(player, PlayerPathPoints, player->GetWay(), isLineVertical);

                updatePos = { player->GetCurPos().x + playerVel, player->GetCurPos().y };
                player->SetCurPos(updatePos);
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

        DrawLines(PlayerPathPoints, hMemDC);
        GM->DrawLine(hMemDC);
        GM->PaintArea(hMemDC, AreaPoints);
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

BOOL PlayerInAreaLine(vector<POINT> & AreaPoints, Player* player, int & lineNum, bool & isVertical, int way)
{
    for (int i = 0; i < AreaPoints.size(); i++)
    {

        if (player->GetCurPos().y == AreaPoints[i].y && AreaPoints[i].y == AreaPoints[(i + 1) % AreaPoints.size()].y) // y 선상
        {
            if (player->GetCurPos().x > min(AreaPoints[i].x, AreaPoints[(i + 1) % AreaPoints.size()].x) &&
                player->GetCurPos().x < max(AreaPoints[i].x, AreaPoints[(i + 1) % AreaPoints.size()].x)) // x 가 선 안에 있다
            {
                cout << "선분 " << i << " " << (i + 1) % AreaPoints.size() << " 에 플레이어가 있습니다" << endl;
                isVertical = false;
                lineNum = i;
                return TRUE;
            }
        }

        else if (player->GetCurPos().x == AreaPoints[i].x && AreaPoints[i].x == AreaPoints[(i + 1) % AreaPoints.size()].x) // x 선상
        {
            if (player->GetCurPos().y > min(AreaPoints[i].y, AreaPoints[(i + 1) % AreaPoints.size()].y) &&
                player->GetCurPos().y < max(AreaPoints[i].y, AreaPoints[(i + 1) % AreaPoints.size()].y)) // y 가 선 안에 있다
            {
                cout << "선분 " << i << " " << (i + 1) % AreaPoints.size() << " 에 플레이어가 있습니다" << endl;
                isVertical = true;
                lineNum = i;
                return TRUE;
            }
        }

        if (player->GetCurPos().x == AreaPoints[i].x && player->GetCurPos().y == AreaPoints[i].y) // 플레이어가 꼭짓점에 있다.
        {
            cout << "플레이어는 "<< i <<"번 꼭짓점에 있습니다" << endl;

            if (way == 12)
            {
                if (AreaPoints[(i + 1) % AreaPoints.size()].y < player->GetCurPos().y ||
                    AreaPoints[(i - 1 + AreaPoints.size()) % AreaPoints.size()].y < player->GetCurPos().y)
                {
                    isVertical = true;
                    return TRUE;
                }

                else
                {
                    isVertical = false;
                    return TRUE;
                }
            }

            else if (way == 6)
            {
                if (AreaPoints[(i + 1) % AreaPoints.size()].y > player->GetCurPos().y ||
                    AreaPoints[(i - 1 + AreaPoints.size()) % AreaPoints.size()].y > player->GetCurPos().y)
                {
                    isVertical = true;
                    return TRUE;
                }

                else
                {
                    isVertical = false;
                    return TRUE;
                }
            }

            else if (way == 3)
            {
                if (AreaPoints[(i + 1) % AreaPoints.size()].x < player->GetCurPos().x ||
                    AreaPoints[(i - 1 + AreaPoints.size()) % AreaPoints.size()].x < player->GetCurPos().x)
                {
                    isVertical = true;
                    return TRUE;
                }

                else
                {
                    isVertical = false;
                    return TRUE;
                }
            }

            else if (way == 9)
            {
                if (AreaPoints[(i + 1) % AreaPoints.size()].x > player->GetCurPos().x ||
                    AreaPoints[(i - 1 + AreaPoints.size()) % AreaPoints.size()].x > player->GetCurPos().x)
                {
                    isVertical = true;
                    return TRUE;
                }

                else
                {
                    isVertical = false;
                    return TRUE;
                }
            }



            
        }

    }

    //cout << "플레이어가 새로운 영역을 만들고 있습니다." << endl;
    return FALSE;
}

BOOL LineStart(Player* player, vector<POINT> & PlayerPathPoints, int way, bool isVertical) //꼭짓점이면 push할 필요 없다.
{
    if (way == 6 || way == 12) //위 아래
    {
        if (isVertical == false)
        {
            cout << "LineStart (UpDown)" << endl;
            PlayerPathPoints.push_back(player->GetCurPos());
            player->PlayerPosUpdate();
            return TRUE;
        }
    }
    
    else if(way == 3 || way == 9)//좌 우
    {
        if (isVertical == true)
        {
            cout << "LineStart (LeftRight)" << endl;
            PlayerPathPoints.push_back(player->GetCurPos());
            player->PlayerPosUpdate();
            return TRUE;
        }
    }

    return FALSE;
}

BOOL LineEnd(Player* player, vector<POINT> & PlayerPathPoints)
{
    cout << "Line End" << endl;
    PlayerPathPoints.push_back(player->GetCurPos());
    return TRUE;
}

BOOL PlayerDead(vector<POINT>& PlayerPathPoints, Player* player)
{
    if (!PlayerPathPoints.empty())
    {
        for (int i = 0; i < PlayerPathPoints.size() - 1; i++)
        {
            if (player->GetCurPos().y == PlayerPathPoints[i].y && PlayerPathPoints[i].y == PlayerPathPoints[(i + 1) % PlayerPathPoints.size()].y) // y 선상
            {
                if (player->GetCurPos().x > min(PlayerPathPoints[i].x, PlayerPathPoints[(i + 1) % PlayerPathPoints.size()].x) &&
                    player->GetCurPos().x < max(PlayerPathPoints[i].x, PlayerPathPoints[(i + 1) % PlayerPathPoints.size()].x)) // x 가 선 안에 있다
                {
                    cout << "선에 닿아서 플레이어는 사망하였습니다" << endl;
                    return TRUE;
                }
            }

            else if (player->GetCurPos().x == PlayerPathPoints[i].x && PlayerPathPoints[i].x == PlayerPathPoints[(i + 1) % PlayerPathPoints.size()].x) // x 선상
            {
                if (player->GetCurPos().y > min(PlayerPathPoints[i].y, PlayerPathPoints[(i + 1) % PlayerPathPoints.size()].y) &&
                    player->GetCurPos().y < max(PlayerPathPoints[i].y, PlayerPathPoints[(i + 1) % PlayerPathPoints.size()].y)) // y 가 선 안에 있다
                {
                    cout << "선에 닿아서 플레이어는 사망하였습니다" << endl;
                    return TRUE;
                }
            }

        }
    }

    return FALSE;
}

void MakeArea(vector<POINT>& PlayerPathPoints, vector<POINT>& AreaPoints, int startLineNum, int endLineNum)
{
    vector<POINT> newAreaPoint;

    for (int i = 0; i < PlayerPathPoints.size(); i++)
    {
        newAreaPoint.push_back(PlayerPathPoints[i]);
    }

    //외적으로 회전 방향을 구한다.

    POINT center = {0,0};
    for (int i = 0; i < AreaPoints.size(); i++)
    {
        center.x += (AreaPoints[i].x / AreaPoints.size());
        center.y += (AreaPoints[i].y / AreaPoints.size());
    }

    double totalRadius = 0;
    for (int i = 0; i < PlayerPathPoints.size() - 1; i++)
    {
        double length1 = sqrt((PlayerPathPoints[i].x - center.x) * (PlayerPathPoints[i].x - center.x) +
            (PlayerPathPoints[i].y - center.y) * (PlayerPathPoints[i].y - center.y));
        double length2 = sqrt((PlayerPathPoints[i+1].x - center.x) * (PlayerPathPoints[i+1].x - center.x) +
            (PlayerPathPoints[i+1].y - center.y) * (PlayerPathPoints[i+1].y - center.y));
        double Cross = (PlayerPathPoints[i].x - center.x) * (PlayerPathPoints[i + 1].y - center.y) -
            (PlayerPathPoints[i + 1].x - center.x) * (PlayerPathPoints[i].y - center.y);
        totalRadius += asin(Cross / (length1 * length2));
    }

    POINT startPoint = PlayerPathPoints[0];
    POINT endPoint = PlayerPathPoints[PlayerPathPoints.size()-1];

    if (totalRadius < 0) //라인 하나에 start, end있을때 구분하기
    {
        cout << "rotate counter clockwise" << endl;

        int i= endLineNum;
        while (1)
        {
            newAreaPoint.push_back(AreaPoints[i]);
            if (i == startLineNum) break;
            if (i == 0) i = AreaPoints.size();
            i--;
        }

    }

    else
    {
        cout << "rotate clockwise" << endl;

        int i = (endLineNum+1)%AreaPoints.size();
        while (1)
        {
            newAreaPoint.push_back(AreaPoints[i]);
            if (i == startLineNum) break;
            if (i == AreaPoints.size() - 1) i = -1;
            i++;
        }

    }

    AreaPoints = newAreaPoint;
    PlayerPathPoints = {};

}

BOOL Collision(vector<POINT>& AreaPoints, Player* player)
{
    
    return 0;
}

