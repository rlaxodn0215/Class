﻿// BrickCrash.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "BrickCrash.h"
#include "Object.h"
#include<vector>
#include<stdlib.h>
#include<crtdbg.h>
#include<time.h>

//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF || _CRTDBG_LEAK_CHECK_DF);
//_CrtDumpMemoryLeaks();

#define MAX_LOADSTRING 100
#define TIMER_FIRST 1

using namespace std;

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

HBITMAP screen;
TCHAR InBuff[1000];
TCHAR OutBuff[100];

DWORD size;


bool PlayScene = false;
bool GameStart = false;
bool gameOver = false;
bool gameWin = false;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
Vector RandomVelocity();
void StageBlockSetting(vector<Object*>& blocks, vector<Object*>& balls, int blockNum, int ballNum);
BOOL GameOver(vector<Object*>& balls, Ball * ba);
BOOL GameWin(vector<Object*>& blocks);

INT_PTR CALLBACK ID_Input_Dialogue(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK Rank_Dialogue(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK GameOver_Dialogue(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK GameWin_Dialogue(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);

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
    LoadStringW(hInstance, IDC_BRICKCRASH, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_BRICKCRASH));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_BRICKCRASH));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_BRICKCRASH);
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
      200, 100, 800, 900, nullptr, nullptr, hInstance, nullptr);

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

    static RECT rectView;
    static RECT playRectview = {200,10,755,785};
    static RECT pointBoard = { 40,100,150,120 };

    static RECT Title = { 200,200,550,250 };
    static RECT startButton = { 250,450,500,500 };
    static RECT rankButton = { 250,500,500,550 };
    static RECT exitButton = { 250,550,500,600 };
    static POINT mousePos;

    static TCHAR playerID[100];
    static TCHAR points[10]; 

    static Vector PlayerPos = { 504,750 };
    static Vector PlayerVel = { 0,0 };
    static int playerSpeed = 8;
    static int playerWidth = 100;
    static int playerHeight = 20;

    static int ballRadius = 10;
    static Vector FirstBallPos = { PlayerPos.x,PlayerPos.y - playerHeight / 2 - ballRadius };
    static Vector FirstBallVel = { 0,0 };

    static vector<Object*> Blocks;
    static vector<Object*> Balls;

    static Player* player = new Player(PlayerPos, PlayerVel, playerWidth, playerHeight, "no name", 0);
    static Ball* firstBall = new Ball(FirstBallPos, FirstBallVel, ballRadius, -1);

    static Object* play = (Object*)player;
    static Object* fBall = (Object*)firstBall;
    // static vector<Object*> Items;
    static int BlockNum = 100;
    static int hideBallNum = 5;

    switch (message)
    {
    case WM_CREATE:
    {
        GetClientRect(hWnd, &rectView);
        SetTimer(hWnd, TIMER_FIRST, 10, NULL);
        StageBlockSetting(Blocks, Balls, BlockNum, hideBallNum);
       // hFile = CreateFile(_T("Rank.txt"), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, 0);
        memset(InBuff, 0, sizeof(InBuff));
        
    }
    break;
    case WM_TIMER:
    {
        switch (wParam)
        {
        case TIMER_FIRST:
        {
            if (PlayScene)
            {
                firstBall->Update();
                firstBall->Collison(playRectview, play, Blocks);

                for (int i = 0; i < Balls.size(); i++)
                {
                    Balls[i]->Update();
                    Balls[i]->Collison(playRectview, play, Blocks);
                    Balls[i]->BallActive(Blocks, RandomVelocity());
                }


                for (int i = 0; i < Blocks.size(); i++)
                {
                    Blocks[i]->Update();
                }


                if (GetAsyncKeyState(VK_LEFT) & 0x8000) //왼쪽
                {
                    Vector newPos = { play->GetPos().x - playerSpeed,play->GetPos().y };
                    play->SetPos(newPos);
                    PlayerVel = { (double)playerSpeed,0 };
                    play->SetVel(PlayerVel);

                    player->Collison(playRectview, Balls);

                    if (GameStart == false)
                    {
                        Vector newBallpos = { newPos.x, fBall->GetPos().y };
                        fBall->SetPos(newBallpos);
                    }
                }

                if (GetAsyncKeyState(VK_RIGHT) & 0x8000) //오른쪽
                {
                    Vector newPos = { play->GetPos().x + playerSpeed,play->GetPos().y };
                    play->SetPos(newPos);

                    PlayerVel = { -(double)playerSpeed,0 };
                    play->SetVel(PlayerVel);

                    player->Collison(playRectview, Balls);

                    if (GameStart == false)
                    {
                        Vector newBallpos = { newPos.x, fBall->GetPos().y };
                        fBall->SetPos(newBallpos);
                    }
                }

                if (GameOver(Balls,firstBall))
                {
                    gameOver = true;
                    PlayScene = false;
                }

                if (GameWin(Blocks))
                {
                    gameWin = true;
                    PlayScene = false;
                }

                InvalidateRect(hWnd, NULL, FALSE);
            }
        }
        break;
        default:
            break;
        }
    }
    break;
    case WM_LBUTTONDOWN:
    {
        mousePos.x = LOWORD(lParam);
        mousePos.y = HIWORD(lParam);

        if (mousePos.x>=startButton.left && mousePos.x<=startButton.right &&
            mousePos.y >= startButton.top && mousePos.y <= startButton.bottom)
        {
            DialogBox(hInst, MAKEINTRESOURCE(ID_IDINPUT), hWnd, ID_Input_Dialogue);
        }

        else if (mousePos.x >= rankButton.left && mousePos.x <= rankButton.right &&
            mousePos.y >= rankButton.top && mousePos.y <= rankButton.bottom)
        {
            DialogBox(hInst, MAKEINTRESOURCE(ID_RankingBoard), hWnd, Rank_Dialogue);
        }

        else if (mousePos.x >= exitButton.left && mousePos.x <= exitButton.right &&
            mousePos.y >= exitButton.top && mousePos.y <= exitButton.bottom)
        {
            exit(1);
        }
    }
    case WM_KEYDOWN:
    {
        switch (wParam)
        {

        case VK_SPACE:
        {
            //공 발사 
            GameStart = true;
            Vector vec = { 0,-playerSpeed };
            fBall->SetVel(vec);


        }
        break;
        default:
            break;
        }
    }
    break;

    case WM_KEYUP:
    {
        switch (wParam)
        {
        case VK_LEFT:
        {
            PlayerVel = { 0,0 };
            play->SetVel(PlayerVel);
        }
        break;
        case VK_RIGHT:
        {
            PlayerVel = { 0,0 };
            play->SetVel(PlayerVel);
        }
        break;

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

        if (PlayScene == false && gameOver==false)
        {
            DrawText(hdc, _T("벽돌을 부숴라!!"), 9, &Title, DT_SINGLELINE |DT_CENTER| DT_VCENTER);

            Rectangle(hdc, startButton.left, startButton.top, startButton.right, startButton.bottom);
            DrawText(hdc, _T("START"), 5, &startButton, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

            Rectangle(hdc, rankButton.left, rankButton.top, rankButton.right, rankButton.bottom);
            DrawText(hdc, _T("RANK"), 4, &rankButton, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

            Rectangle(hdc, exitButton.left, exitButton.top, exitButton.right, exitButton.bottom);
            DrawText(hdc, _T("EXIT"), 4, &exitButton, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
        }
        
        else if(PlayScene==true && gameOver == false)
        {
            HDC hMemDC;
            HBITMAP hOldBitmap;

            hMemDC = CreateCompatibleDC(hdc);

            screen = CreateCompatibleBitmap(hdc, rectView.right, rectView.bottom);

            hOldBitmap = (HBITMAP)SelectObject(hMemDC, screen);

            wsprintf(points, TEXT("Points :  %d"), player->GetPoint());

            DrawText(hMemDC, points, _tcslen(points), &pointBoard, DT_SINGLELINE | DT_VCENTER);

            Rectangle(hMemDC, playRectview.left, playRectview.top, playRectview.right, playRectview.bottom);

            play->Draw(hMemDC);
            firstBall->Draw(hMemDC);

            for (int i = 0; i < BlockNum; i++)
            {
                Blocks[i]->Draw(hMemDC);
            }

            for (int i = 0; i < hideBallNum; i++)
            {
                Balls[i]->Draw(hMemDC);
            }

            BitBlt(hdc, 0, 0, rectView.right, rectView.bottom, hMemDC, 0, 0, SRCCOPY);

            SelectObject(hMemDC, hOldBitmap);
            DeleteDC(hMemDC);
        }

        if (gameOver)
        {
            DialogBox(hInst, MAKEINTRESOURCE(ID_GAMEOVER), hWnd, GameOver_Dialogue);
            //gameOver = false;
        }

        if (gameWin)
        {
            DialogBox(hInst, MAKEINTRESOURCE(ID_GAMEWIN), hWnd, GameWin_Dialogue);
        }

        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
    {
        delete player;
        delete firstBall;

        if (screen)
            DeleteObject(screen);

        for (int i = 0; i < BlockNum; i++)
        {
            Object* obj = Blocks[i];
            delete obj;
        }

        for (int i = 0; i < hideBallNum; i++)
        {
            Object* obj = Balls[i];
            delete obj;
        }

 


        KillTimer(hWnd, TIMER_FIRST);
        PostQuitMessage(0);
        //_CrtDumpMemoryLeaks();
    }
    break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
    }
}

void StageBlockSetting(vector<Object*>& blocks, vector<Object*>& balls, int blockNum, int hideballNum)
{
   // _CrtSetBreakAlloc(279);
    srand(time(NULL));

    Vector v = { 0,0 };
    int width = 10; //가로줄
    int height = 10; //세로줄
    int blockWidth = 50; //블럭 가로
    int blockHeight = 20; //블럭 세로

    Vector startP = { 250,50 };

    if (blockNum == width * height)
    {
        for (int i = 0; i < height; i++)
        {
            Vector st = startP;

            int start = st.x;
            for (int j = 0; j < width; j++)
            {
                int hp = rand() % 5 + 1;
                Block* block = new Block(st, v, blockWidth, blockHeight, hp);
                Object* B = (Object*)block;
                blocks.push_back(B);
                st.x += blockWidth;
            }
            startP.y += blockHeight;
        }
    }

    // 공 랜덤 위치, 속도 만들기
    for (int i = 0; i < hideballNum; i ++ )
    {
        int num = rand()%blockNum;

        Vector pos = blocks[num]->GetPos();
        Vector vel = { 0,0 };

        Ball* ball = new Ball(pos, vel, 10, num);
        Object* B = (Object*)ball;
        balls.push_back(B);
    }



}

BOOL GameOver(vector<Object*>& balls, Ball * ba)
{
    int count = 0;
    for (int i = 0; i < balls.size(); i++)
    {
        Ball* ball = (Ball*)balls[i];
        if (ball->GetEnable() == FALSE)
        {
            count++;
        }

        else
        {
            return FALSE;
        }

    }

    if (count == balls.size() && !(ba->GetEnable()))
    {
        return TRUE;
    }

    else
    {
        return FALSE;
    }
}

BOOL GameWin(vector<Object*>& blocks)
{
    int count = 0;

    for (int i = 0; i < blocks.size(); i++)
    {
        Block* block = (Block*)blocks[i];
        if (block->BlockDead())
        {
            count++;
        }

        else
        {
            return FALSE;
        }
        
    }

    if (count == blocks.size())
    {
        return TRUE;
    }

    else
    {
        return FALSE;

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

INT_PTR ID_Input_Dialogue(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);

    switch (iMsg)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
    {
        switch (LOWORD(wParam))
        {
        case IDOK:
        {
            EndDialog(hDlg, 0);
            PlayScene = true;
            return (INT_PTR)TRUE;
        }
        break;
        case IDCANCEL:
        {
            EndDialog(hDlg, 0);
            return (INT_PTR)TRUE;
        }
        break;
        }

    }
    break;
    }

    return (INT_PTR)FALSE;
}

INT_PTR CALLBACK Rank_Dialogue(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);

    switch (iMsg)
    {
    case WM_INITDIALOG:
    {
        DWORD size;
        HANDLE hFile = CreateFile(_T("Rank.txt"), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, 0, 0);
        if (hFile != INVALID_HANDLE_VALUE)
        {
            memset(InBuff, 0, sizeof(InBuff));
            ReadFile(hFile, InBuff, 999 * sizeof(TCHAR), &size, NULL);
            SetDlgItemText(hDlg, ID_TEXT, InBuff);
            CloseHandle(hFile);
        }
    }
        return (INT_PTR)TRUE;

    case WM_COMMAND:
    {
        switch (LOWORD(wParam))
        {
        case IDOK:
        {
            EndDialog(hDlg, 0);
            return (INT_PTR)TRUE;
        }
        break;
        }

    }
        break;
    }

    return (INT_PTR)FALSE;

}

INT_PTR CALLBACK GameOver_Dialogue(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);

    switch (iMsg)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
    {
        switch (LOWORD(wParam))
        {
        case IDOK:
        {
            EndDialog(hDlg, 0);
            exit(1);
            return (INT_PTR)TRUE;
        }
        break;
        }

    }
    break;
    }

    return (INT_PTR)FALSE;
}

INT_PTR CALLBACK GameWin_Dialogue(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);

    switch (iMsg)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
    {
        switch (LOWORD(wParam))
        {
        case IDOK:
        {
            EndDialog(hDlg, 0);
            exit(1);
            return (INT_PTR)TRUE;
        }
        break;
        }

    }
    break;
    }

    return (INT_PTR)FALSE;
}


Vector RandomVelocity()
{
    int sign1 = rand() % 2;
    int sign2 = rand() % 2;

    double x=0;
    double y=0;

    if (sign1)
    {
        if (sign2)
        {
            x = rand() % 6 + 5;
            y = rand() % 6 + 5;
        }

        else
        {
            x = rand() % 6 + 5;
            y = (rand() % 6 + 5) * (-1);
        }
    }

    else
    {
        if (sign2)
        {
            x = (rand() % 6 + 5) * (-1);
            y = (rand() % 6 + 5) * (-1);
        }

        else
        {
            x = (rand() % 6 + 5) * (-1);
            y = rand() % 6 + 5;
        }
    }

    Vector vel = { x,y };

    return vel;
}
