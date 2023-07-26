// A_Star.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "A_Star.h"
#include"Block.h"
#include<queue>
#include<map>

#define MAX_LOADSTRING 100
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

void DrawBlocks(HDC hdc);
void CheckClick(POINT mousePos, POINT & startPos, POINT & endPos, int& count, bool & moving);
void A_Star();
void PlayerMove();
void DrawPlayer(HDC hdc);

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
    LoadStringW(hInstance, IDC_ASTAR, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ASTAR));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ASTAR));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_ASTAR);
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
      100, 100, 1024, 1000, nullptr, nullptr, hInstance, nullptr);

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

priority_queue<Block, vector<Block>, greater<Block>> OpenList;
vector<Block> CloseList;
vector<POINT> playerMovePoint;

const int MX = 10;
Block totalBlock[MX][MX];
POINT obstacleBlcok[15] = { {7,2}, {7,7}, {4,2} ,{4,3}, {4,4},{4,5}, {4,6}, {5,6}, {5,7}, {5,8},{2,4},{3,4},{5,4},{6,4},{7,4} };
POINT checkArea[8] = { {-1,-1},{0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1},{-1,0} };
POINT startPoint = { -1, -1};
POINT passoverPoint = { -1,-1 };
POINT endPoint = { -1, -1 };

int RecLength = 70;
int offset = 80;
int line = 10;
int line2 = 14;
bool playermove = false;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
    static POINT mousePos;
    static int count = 0;
    static bool moving = false;

    switch (message)
    {
    case WM_CREATE:
    {
        for (int i = 0; i < MX; i++)
        {
            for (int j = 0; j < MX; j++)
            {
                totalBlock[i][j].SetPos({ i,j });
                totalBlock[i][j].SetStatus(MOVE_ABLE);
            }
        }

        for (int i = 0; i < 15; i++)
        {
            totalBlock[obstacleBlcok[i].x][obstacleBlcok[i].y].SetStatus(WALL);
        }

        SetTimer(hWnd, TIMER_SECOND, 500, NULL);

    }
    break;
    case WM_TIMER:
    {
        if (wParam == TIMER_SECOND)
        {
            PlayerMove();
            InvalidateRect(hWnd, NULL, TRUE);
        }
    }
            break;
    case WM_LBUTTONDOWN:
    {
        mousePos.x = LOWORD(lParam);
        mousePos.y = HIWORD(lParam);
        CheckClick(mousePos, startPoint,endPoint,count,moving);
        InvalidateRect(hWnd, NULL, TRUE);
        if (moving)
        {
            A_Star();
            playermove = true;
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
            DrawBlocks(hdc);
            DrawPlayer(hdc);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        KillTimer(hWnd, TIMER_SECOND);
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

void DrawBlocks(HDC hdc)
{

    for (int i = 0; i < MX; i++) // y
    {
        for (int j = 0; j < MX; j++) // x
        {
            HBRUSH hBrush, oldBrush;
           
            if (totalBlock[i][j].GetStatus() == WALL) // obstacle
            {
                hBrush = CreateSolidBrush(RGB(0, 0, 0));
                oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
                Rectangle(hdc, (RecLength * i + offset) - RecLength / 2, (RecLength * j + offset) - RecLength / 2,
                    (RecLength * i + offset) + RecLength / 2, (RecLength * j + offset) + RecLength / 2);
                SelectObject(hdc, oldBrush);
                DeleteObject(hBrush);
            }

            else if(totalBlock[i][j].GetStatus() == START) // 시작점
            {
                hBrush = CreateSolidBrush(RGB(255, 0, 0));
                oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
                Rectangle(hdc, (RecLength * i + offset) - RecLength / 2, (RecLength * j + offset) - RecLength / 2,
                    (RecLength * i + offset) + RecLength / 2, (RecLength * j + offset) + RecLength / 2);
                SelectObject(hdc, oldBrush);
                DeleteObject(hBrush);
            }

            else if (totalBlock[i][j].GetStatus() == END) // 도착점
            {
                hBrush = CreateSolidBrush(RGB(0, 0, 255));
                oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
                Rectangle(hdc, (RecLength * i + offset) - RecLength / 2, (RecLength * j + offset) - RecLength / 2,
                    (RecLength * i + offset) + RecLength / 2, (RecLength * j + offset) + RecLength / 2);
                SelectObject(hdc, oldBrush);
                DeleteObject(hBrush);
            }

            else
            {
                Rectangle(hdc, (RecLength * i + offset) - RecLength / 2, (RecLength * j + offset) - RecLength / 2,
                    (RecLength * i + offset) + RecLength / 2, (RecLength * j + offset) + RecLength / 2);

                //텍스트 값을 넣는다.
                TCHAR temp[10];
                _stprintf_s(temp, L"%d", totalBlock[i][j].GetG()); // G
                TextOut(hdc, (RecLength * i + offset) - RecLength / 2 + 15, (RecLength * j + offset) - RecLength / 2 + 10, temp, _tcslen(temp));
                _stprintf_s(temp, L"%d", totalBlock[i][j].GetH()); // H
                TextOut(hdc, (RecLength * i + offset) - RecLength / 2 + 45, (RecLength * j + offset) - RecLength / 2 + 10, temp, _tcslen(temp));
                _stprintf_s(temp, L"%d", totalBlock[i][j].GetF()); // F
                TextOut(hdc, (RecLength * i + offset) - RecLength / 2 + 30, (RecLength * j + offset) - RecLength / 2 + 40, temp, _tcslen(temp));
            }

            if (totalBlock[i][j].GetList() == PATH) // 경로
            {
                hBrush = CreateSolidBrush(RGB(0, 255, 0));
                oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
                Rectangle(hdc, (RecLength * i + offset) - RecLength / 2, (RecLength * j + offset) - RecLength / 2,
                    (RecLength * i + offset) + RecLength / 2, (RecLength * j + offset) + RecLength / 2);
                SelectObject(hdc, oldBrush);
                DeleteObject(hBrush);
            }

            
           
        }
    }

}

void CheckClick(POINT mousePos, POINT & startPos, POINT & endPos, int & count, bool& moving)
{

    for (int i = 0; i < MX; i++)
    {
        for (int j = 0; j < MX; j++)
        {
            if (mousePos.x >= (RecLength * i + offset) - RecLength / 2 && mousePos.x <= (RecLength * i + offset) + RecLength / 2
                && mousePos.y >= (RecLength * j + offset) - RecLength / 2 && mousePos.y <= (RecLength * j + offset) + RecLength / 2) // 클릭한 사각형 포인트
            {
                if (startPos.x == i && startPos.y == j || endPos.x ==i && endPos.y == j) return;
                if (totalBlock[i][j].GetStatus() == WALL) return;

                if (count == 0)
                {
                    startPos.x = i;
                    startPos.y = j;

                    passoverPoint = startPoint;

                    totalBlock[startPos.x][startPos.y].SetStatus(START);// 시작점

                    count++;

                    moving = false;
                }

                else
                {
                    endPos.x = i;
                    endPos.y = j;

                    totalBlock[endPos.x][endPos.y].SetStatus(END);// 도착점

                    count--;

                    moving = true;
                }

                return;
            }
        }
    }

}


void A_Star()
{
    bool findEndPoint = false;

    totalBlock[startPoint.x][startPoint.y].SetList(CLOSE_LIST);
    totalBlock[startPoint.x][startPoint.y].SetParent(NULL);
    CloseList.push_back(totalBlock[startPoint.x][startPoint.y]);

    while (1)
    {
        for (int i = 0; i < 8; i++)
        {
            if (passoverPoint.x + checkArea[i].x >= MX || passoverPoint.x + checkArea[i].x < 0 ||
                passoverPoint.y + checkArea[i].y >= MX || passoverPoint.y + checkArea[i].y < 0) //배열 범위가 벗어남
                continue;

            if (totalBlock[passoverPoint.x + checkArea[i].x][passoverPoint.y + checkArea[i].y].GetStatus() == WALL ||
                totalBlock[passoverPoint.x + checkArea[i].x][passoverPoint.y + checkArea[i].y].GetList() == CLOSE_LIST) //벽이나 closelist에 있으면
                continue;

            Block temp = totalBlock[passoverPoint.x + checkArea[i].x][passoverPoint.y + checkArea[i].y];

            int g, h;

            int x1 = abs(temp.GetPos().x - totalBlock[passoverPoint.x][passoverPoint.y].GetPos().x);
            int y1 = abs(temp.GetPos().y - totalBlock[passoverPoint.x][passoverPoint.y].GetPos().y);

            if (x1 - y1 > 0)
            {
                g = 14 * y1 + 10 * (x1 - y1);
            }

            else
            {
                g = 14 * x1 + 10 * (y1 - x1);
            }

            int x2 = abs(temp.GetPos().x - totalBlock[endPoint.x][endPoint.y].GetPos().x);
            int y2 = abs(temp.GetPos().y - totalBlock[endPoint.x][endPoint.y].GetPos().y);

            if (x2 - y2 > 0)
            {
                h = 14 * y2 + 10 * (x2 - y2);
            }

            else
            {
                h = 14 * x2 + 10 * (y2 - x2);
            }

            if (h == 0)
            {
                findEndPoint = true;
            }

            if (temp.GetList() != OPEN_LIST) //openlist에 있다면
            {
                totalBlock[passoverPoint.x + checkArea[i].x][passoverPoint.y + checkArea[i].y].
                    SetG(g + totalBlock[passoverPoint.x + checkArea[i].x][passoverPoint.y + checkArea[i].y].GetG());

                totalBlock[passoverPoint.x + checkArea[i].x][passoverPoint.y + checkArea[i].y].SetH(h);
                totalBlock[passoverPoint.x + checkArea[i].x][passoverPoint.y + checkArea[i].y].SetF();
                totalBlock[passoverPoint.x + checkArea[i].x][passoverPoint.y + checkArea[i].y].SetParent(&totalBlock[passoverPoint.x][passoverPoint.y]);
                totalBlock[passoverPoint.x + checkArea[i].x][passoverPoint.y + checkArea[i].y].SetList(OPEN_LIST);
                OpenList.push(totalBlock[passoverPoint.x + checkArea[i].x][passoverPoint.y + checkArea[i].y]);
            }
        }

        Block temp = OpenList.top();
        passoverPoint = temp.GetPos();

        if (findEndPoint) // 도착점을 찾았다.
            break;

        OpenList.pop();
        temp.SetList(CLOSE_LIST);
        CloseList.push_back(temp);

    }

    Block* temp = totalBlock[endPoint.x][endPoint.y].GetParent();

    playerMovePoint.push_back(endPoint);
    while (temp->GetParent() !=NULL)
    {
        temp->SetList(PATH);
        playerMovePoint.push_back(temp->GetPos());
        temp = temp->GetParent();
    }
    playerMovePoint.push_back(startPoint);
    

}

void PlayerMove()
{
    if(playermove && !playerMovePoint.empty())
    {      
        playerMovePoint.pop_back();
    }
}

void DrawPlayer(HDC hdc)
{
    if (playermove && !playerMovePoint.empty())
    {
        HBRUSH hBrush, oldBrush;
        hBrush = CreateSolidBrush(RGB(255, 0, 255));
        oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
        Ellipse(hdc, (RecLength * playerMovePoint.back().x + offset) - RecLength / 2, (RecLength * playerMovePoint.back().y + offset) - RecLength / 2,
            (RecLength * playerMovePoint.back().x + offset) + RecLength / 2, (RecLength * playerMovePoint.back().y + offset) + RecLength / 2);
        SelectObject(hdc, oldBrush);
        DeleteObject(hBrush);
    }
}
