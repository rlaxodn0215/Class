// WindowAPI.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "WindowAPI.h"
#include<iostream>
#include<vector>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<commdlg.h>
#include<stdio.h>

//>>
#pragma comment(lib, "msimg32.lib")

HBITMAP hBackImage;
BITMAP bitBack;

HBITMAP hFrontImage;
BITMAP bitFront;

HBITMAP hTransparentImage;
BITMAP bitTransparent;


HBITMAP hAniImage;
BITMAP bitAni;
const int SPRITE_SIZE_X = 57;
const int SPRITE_SIZE_Y = 52;

int RUN_FRAME_MAX = 0;
int RUN_FRAME_MIN = 0;
int curframe = RUN_FRAME_MIN;

int SPRITE_FRAME_COUNT_X = 0;
int SPRITE_FRAME_COUNT_Y = 0;
//<< : Ani

//>>: text
RECT recView;
//
//>> Func
void CreateBitmap();
void DrawBitmap(HWND hWnd, HDC hdc);
void DeleteBitmap();
void UpdateFrame(HWND hWnd);
void DrawRectText(HDC hdc);
void Update();

VOID CALLBACK AniProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);

//>> double buffering

HBITMAP hDoubleBufferImage;
void DrwaBitmapDoubleBuffering(HWND hWnd, HDC hdc);



BOOL CALLBACK Dialog_Test1_Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);

//<<

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

void DrawCircle(HDC hdc, POINT center, int radius)
{
    int left = center.x - radius;
    int top = center.y - radius;
    int right = center.x + radius;
    int bottom = center.y + radius;

    Ellipse(hdc, left, top, right, bottom);
}


double Length(int x1, int y1, int x2, int y2)
{
    return(sqrt((double)(x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

BOOL InCircle(int x, int y, int mx, int my, int radius)
{
    if (Length(x, y, mx, my) <= radius) return true;
    else return false;
}


//>>: split windows
HWND Chidwnd[3];
LRESULT CALLBACK    ClidWndWndProc1(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    ClidWndWndProc2(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    ClidWndWndProc3(HWND, UINT, WPARAM, LPARAM);
//<<:




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
    //while (GetMessage(&msg, nullptr, 0, 0)) // 이벤트가 있어야함
    //{
    //    if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
    //    {
    //        TranslateMessage(&msg);
    //        DispatchMessage(&msg);
    //    }
    //}

    while (true) // 이벤트가 있어야함
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                break;
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }

        }
        else
        {
            //Update();
            //Render();
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
    RegisterClassExW(&wcex);//꼭 필요



    wcex.lpfnWndProc = ClidWndWndProc1;
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = _T("Child Window Class 1");
    RegisterClassExW(&wcex);

    wcex.lpfnWndProc = ClidWndWndProc2;
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = _T("Child Window Class 2");
    RegisterClassExW(&wcex);

    wcex.lpfnWndProc = ClidWndWndProc3;
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = _T("Child Window Class 3");
    RegisterClassExW(&wcex);



    return NULL;
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

    //static RECT recView;
    static POINT center = { 300,300 };
    static int radius = 50;

    static BOOL isPasted = false;
    static POINT bufferCenter = {};
    static int bufferRadius;


    static POINT mousePos;
    enum OBJECT { CIRCLE, RECTANGLE, STAR, NONE };
    static int randNum = NONE, randRadius;
    static int verson = 1;
    static int wnd3Len = 300;

    static HMENU hMenu, hSubMenu;

    srand(time(NULL));

    switch (message)
    {
    case WM_SIZE:
    {
        GetClientRect(hWnd, &recView); //윈도우 크기가 변경되었을때 사용

    }
    break;
    case WM_CREATE: //한번 만 호출(start느낌, 초기화)
    {
        hMenu = GetMenu(hWnd);
        hSubMenu = GetSubMenu(hMenu, 2);
        EnableMenuItem(hSubMenu, ID_EDITCOPY, MF_GRAYED);
        EnableMenuItem(hSubMenu, ID_EDITPASTE, MF_GRAYED);

        CreateBitmap();
        GetClientRect(hWnd, &recView);
        //SetTimer(hWnd, TIMER_SECOND, 20, AniProc);

        // >> split window
        {
            Chidwnd[0] = CreateWindowEx(WS_EX_CLIENTEDGE, _T("Child Window Class 1"),
                NULL, WS_CHILD | WS_VISIBLE,
                0, 0, recView.right- wnd3Len, recView.bottom / 2 - 1,
                hWnd, NULL, hInst, NULL);

            Chidwnd[1] = CreateWindowEx(WS_EX_CLIENTEDGE, _T("Child Window Class 2"),
                NULL, WS_CHILD | WS_VISIBLE,
                0, recView.bottom / 2 + 1, recView.right - wnd3Len, recView.bottom / 2 - 1,
                hWnd, NULL, hInst, NULL);

            Chidwnd[2] = CreateWindowEx(WS_EX_CLIENTEDGE, _T("Child Window Class 3"),
                NULL, WS_CHILD | WS_VISIBLE,
                wnd3Len, 0, recView.right, recView.bottom,
                hWnd, NULL, hInst, NULL);
        }

    }
    break;

    case WM_TIMER:
    {
        if (wParam == TIMER_SECOND)
        {
            UpdateFrame(hWnd);
            InvalidateRect(hWnd, NULL, FALSE);
        }
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
        if (wParam == 'c' || wParam == 'C')
        {
            if (InCircle(center.x, center.y, mousePos.x, mousePos.y, radius))
            {
                UINT state = GetMenuState(hSubMenu, ID_EDITCOPY, MF_BYCOMMAND);

                if ((state == MF_DISABLED) || MF_GRAYED)
                {
                    EnableMenuItem(hSubMenu, ID_EDITCOPY, MF_ENABLED);
                }

                else if (state == MF_ENABLED)
                {
                    EnableMenuItem(hSubMenu, ID_EDITCOPY, MF_GRAYED);
                }
            }
        }
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
            int temp = randNum;
            //int ans = MessageBox(hWnd, _T("네모 그릴래?"), _T("도형선택"), MB_YESNOCANCEL);

            //DialogBox(hInst, MAKEINTATOM(IDD_DIALOG1), hWnd, Dialog_Test1_Proc);


            /*if (ans == IDYES)
            {
                randNum = RECTANGLE;
            }

            else if (ans == IDNO)
            {
                randNum = NONE;
            }

            else
            {
                randNum = temp;
            }*/


        }
        break;
        case ID_DRAW_STAR:
        {

            int temp = randNum;
            int ans = MessageBox(hWnd, _T("별 그릴래?"), _T("도형선택"), MB_YESNOCANCEL);
            if (ans == IDYES)
            {
                randNum = STAR;

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

        case ID_EDITCOPY:
        {
            bufferCenter = { radius,radius };
            bufferRadius = radius;

            UINT state = GetMenuState(hSubMenu, ID_EDITPASTE, MF_BYCOMMAND);

            if ((state == MF_DISABLED) || MF_GRAYED)
            {
                EnableMenuItem(hSubMenu, ID_EDITPASTE, MF_ENABLED);
            }

            else if (state == MF_ENABLED)
            {
                EnableMenuItem(hSubMenu, ID_EDITPASTE, MF_GRAYED);
            }
        }
        break;

        case ID_EDITPASTE:
        {
            isPasted = true;
        }
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
    //case WM_PAINT: //그림 띄우기
    //{
    //    hdc = BeginPaint(hWnd, &ps);
    //    // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...  

    //    //DrawBitmap(hWnd, hdc);
    //    DrwaBitmapDoubleBuffering(hWnd, hdc);
    //    DrawRectText(hdc);

    //    EndPaint(hWnd, &ps);
    //}
    //break;
    case WM_DESTROY: //종료버튼을 누를 때 발생하는 이벤트
    {
        DeleteBitmap();
        KillTimer(hWnd, TIMER_SECOND);
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

void CreateBitmap()
{
    ////수지
    //{
    //    hBackImage = (HBITMAP)LoadImage(NULL, TEXT("Images/수지.bmp"),
    //        IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

    //    if (hBackImage == NULL)
    //    {
    //        DWORD dwError = GetLastError();
    //        MessageBox(NULL, _T("이미지 로드 에러_1"), _T("에러"), MB_OK);
    //        return;
    //    }

    //    GetObject(hBackImage, sizeof(BITMAP), &bitBack);
    //}


    //시공
    {
        hTransparentImage = (HBITMAP)LoadImage(NULL, TEXT("Images/sigong.bmp"),
            IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

        if (hTransparentImage == NULL)
        {
            DWORD dwError = GetLastError();
            MessageBox(NULL, _T("이미지 로드 에러_2"), _T("에러"), MB_OK);
            return;
        }

        GetObject(hTransparentImage, sizeof(BITMAP), &bitTransparent);
    }

    //Ani
    {
        hAniImage = (HBITMAP)LoadImage(NULL, TEXT("Images/zero_run.bmp"),
            IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

        if (hAniImage == NULL)
        {
            DWORD dwError = GetLastError();
            MessageBox(NULL, _T("이미지 로드 에러_3"), _T("에러"), MB_OK);
            return;
        }

        GetObject(hAniImage, sizeof(BITMAP), &bitAni);

        //: 
        RUN_FRAME_MAX = bitAni.bmWidth / SPRITE_SIZE_X - 1; //이전 사진으로
        RUN_FRAME_MIN = 2; //그 전의 사진은 달리기 직전
        curframe = RUN_FRAME_MIN;

        SPRITE_FRAME_COUNT_X = bitAni.bmWidth / SPRITE_SIZE_X;
        SPRITE_FRAME_COUNT_Y = bitAni.bmHeight / SPRITE_SIZE_Y;
    }

    // BackImage
    {
        hFrontImage = (HBITMAP)LoadImage(NULL, TEXT("Images/Background.bmp"),
            IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

        if (hFrontImage == NULL)
        {
            DWORD dwError = GetLastError();
            MessageBox(NULL, _T("이미지 로드 에러_4"), _T("에러"), MB_OK);
            return;
        }

        GetObject(hFrontImage, sizeof(BITMAP), &bitFront);
    }
}

void DrawBitmap(HWND hWnd, HDC hdc)
{
    HDC hMenDC;
    HBITMAP hodBitmap;
    int bx, by;
    {//수지
        hMenDC = CreateCompatibleDC(hdc);
        hodBitmap = (HBITMAP)SelectObject(hMenDC, hBackImage);
        bx = bitBack.bmWidth;
        by = bitBack.bmHeight;

        BitBlt(hdc, 0, 0, bx, by, hMenDC, 0, 0, SRCCOPY);

        SelectObject(hMenDC, hodBitmap);
        DeleteDC(hMenDC);
    }

    {//시공

        hMenDC = CreateCompatibleDC(hdc);
        hodBitmap = (HBITMAP)SelectObject(hMenDC, hTransparentImage);
        bx = bitTransparent.bmWidth;
        by = bitTransparent.bmHeight;

        //BitBlt(hdc, 150, 150, bx, by, hMenDC, 0, 0, SRCCOPY);
        TransparentBlt(hdc, 240, 255, bx * 2, by, hMenDC, 0, 0, bx, by, RGB(255, 0, 255));
        //TransparentBlt(hdc, 383, 265, bx * 2, by, hMenDC, 0, 0, bx, by, RGB(255, 0, 255));

        SelectObject(hMenDC, hodBitmap);
        DeleteDC(hMenDC);

    }

    {//Ani
        hMenDC = CreateCompatibleDC(hdc);
        hodBitmap = (HBITMAP)SelectObject(hMenDC, hAniImage);
        bx = bitAni.bmWidth / SPRITE_FRAME_COUNT_X;
        by = bitAni.bmHeight / SPRITE_FRAME_COUNT_Y;

        int xStart = curframe * bx;
        int yStart = 0;
        static int posX = 150;
        posX += 1;
        //BitBlt(hdc, 150, 150, bx, by, hMenDC, 0, 0, SRCCOPY);
        TransparentBlt(hdc, posX, 150, bx, by, hMenDC, xStart, yStart, bx, by, RGB(255, 0, 255));

        SelectObject(hMenDC, hodBitmap);
        DeleteDC(hMenDC);
    }


}

void DeleteBitmap()
{
    DeleteObject(hAniImage);
    DeleteObject(hBackImage);
    DeleteObject(hTransparentImage);
}

void UpdateFrame(HWND hWnd)
{
    curframe++;
    if (curframe > RUN_FRAME_MAX)
    {
        curframe = RUN_FRAME_MIN;
    }

    InvalidateRect(hWnd, NULL, FALSE); // true: 배경이 있을 때 깜박임, false: 깜박임 X, 배경 없으면 잔상 남음 
}

static int yPos = 0;

void DrawRectText(HDC hdc)
{
    TCHAR strTest[] = _T("이미지 출력");
    TextOut(hdc, 10, yPos, strTest, _tcslen(strTest));
}

void Update()
{
    //: wm_keydown, wm_keyup -> 반응이 직각적으로 오지 않음
    if (GetKeyState('A') & 0x8000)
    {

    }

    if (GetKeyState('D') & 0x8000)
    {

    }

    if (GetKeyState('W') & 0x8000)
    {

    }

}

VOID CALLBACK AniProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
    UpdateFrame(hWnd);
    yPos += 5;
    if (yPos > recView.bottom) yPos = 0;
}

void DrwaBitmapDoubleBuffering(HWND hWnd, HDC hdc)
{
    HDC hMenDC;
    HBITMAP hodBitmap;
    int bx, by;

    HDC hMenDC2;
    HBITMAP hodBitmap2;

    hMenDC = CreateCompatibleDC(hdc);
    if (hDoubleBufferImage == NULL)
    {
        hDoubleBufferImage = CreateCompatibleBitmap(hdc, recView.right, recView.bottom);
    }

    hodBitmap = (HBITMAP)SelectObject(hMenDC, hDoubleBufferImage);

    //{//수지

    //    hMenDC2 = CreateCompatibleDC(hMenDC);
    //    hodBitmap2 = (HBITMAP)SelectObject(hMenDC2, hBackImage);
    //    bx = bitBack.bmWidth;
    //    by = bitBack.bmHeight;

    //    BitBlt(hMenDC, 0, 0, bx, by, hMenDC2, 0, 0, SRCCOPY);

    //    SelectObject(hMenDC2, hodBitmap2);
    //    DeleteDC(hMenDC2);
    //}

    {//시공

        hMenDC2 = CreateCompatibleDC(hMenDC);
        hodBitmap2 = (HBITMAP)SelectObject(hMenDC2, hTransparentImage);
        bx = bitTransparent.bmWidth;
        by = bitTransparent.bmHeight;

        //BitBlt(hdc, 150, 150, bx, by, hMenDC, 0, 0, SRCCOPY);
        TransparentBlt(hMenDC, 240, 255, bx * 2, by, hMenDC2, 0, 0, bx, by, RGB(255, 0, 255));
        TransparentBlt(hMenDC, 383, 265, bx * 2, by, hMenDC2, 0, 0, bx, by, RGB(255, 0, 255));

        SelectObject(hMenDC2, hodBitmap2);
        DeleteDC(hMenDC2);

    }

    {//Ani
        hMenDC2 = CreateCompatibleDC(hMenDC);
        hodBitmap2 = (HBITMAP)SelectObject(hMenDC2, hAniImage);
        bx = bitAni.bmWidth / SPRITE_FRAME_COUNT_X;
        by = bitAni.bmHeight / SPRITE_FRAME_COUNT_Y;

        int xStart = curframe * bx;
        int yStart = 0;
        static int posX = 150;
        posX += 3;
        //BitBlt(hdc, 150, 150, bx, by, hMenDC, 0, 0, SRCCOPY);
        //TransparentBlt(hMenDC, posX, 150, bx, by, hMenDC2, xStart, yStart, bx, by, RGB(255, 0, 255));
        StretchBlt(hMenDC, posX, 150, -bx, by, hMenDC2, xStart, yStart, bx, by, SRCCOPY);
        //StretchBlt(hMenDC, posX, 150, -bx, by, hMenDC2, xStart, yStart, bx, by, SRCCOPY);
        //TransparentBlt(hMenDC, posX, 150, bx, by, hMenDC2, xStart, yStart, bx, by, RGB(255, 0, 255));

        SelectObject(hMenDC2, hodBitmap2);
        DeleteDC(hMenDC2);  
    }
    //<< hMenDC 에 그려주기

    {//>> front image

       hMenDC2 = CreateCompatibleDC(hMenDC);
       hodBitmap2 = (HBITMAP)SelectObject(hMenDC2, hFrontImage);
       bx = bitFront.bmWidth;
       by = bitFront.bmHeight;

       HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255));
       HBRUSH oldBrush = (HBRUSH)SelectObject(hMenDC2, hBrush);

       Ellipse(hMenDC2, 250, 100, 750, 500);

       SelectObject(hMenDC2,oldBrush);
       DeleteObject(hBrush);
       
       TransparentBlt(hMenDC, 0, 0, bx, by, hMenDC2, 0, 0, bx, by, RGB(255, 0, 255));

       SelectObject(hMenDC2, hodBitmap2);



       DeleteDC(hMenDC2);
    }



    //hdc에 그려주기
    //BitBlt(hdc, 0, 0, recView.right, recView.bottom, hMenDC, 0, 0, SRCCOPY);
    TransparentBlt(hdc, 0, 0, recView.right, recView.bottom, hMenDC, 0, 0,
        recView.right, recView.bottom, RGB(255, 0, 255));

        //hBrush = CreateSolidBrush(RGB(255, 0, 255));
        //oldB = (HBRUSH)SelectObject(hMenDC, hBrush);
        //Ellipse(hMenDC, 400, 300, 700, 500);
        //SelectObject(hdc, oldB);
        //DeleteObject(hBrush);

    SelectObject(hMenDC, hodBitmap);
    DeleteDC(hMenDC);
}

BOOL CALLBACK Dialog_Test1_Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    switch (iMsg)
    {
    case WM_INITDIALOG:
    {
        HWND hBtn = GetDlgItem(hDlg, IDC_PAUSE);
        EnableWindow(hBtn, FALSE);
    }
    return 1;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_START:
        {
            HDC hdc = GetDC(hDlg);
            SetDlgItemText(hDlg, ID_TEXT, _T("Start"));
            ReleaseDC(hDlg, hdc);

            HWND hBtn = GetDlgItem(hDlg, IDC_START);
            EnableWindow(hBtn, FALSE);

            hBtn = GetDlgItem(hDlg, IDC_PAUSE);
            EnableWindow(hBtn, TRUE);
        }
        break;
        case IDC_PAUSE:
        {
            HDC hdc = GetDC(hDlg);
            SetDlgItemText(hDlg, ID_TEXT, _T("Pause"));
            ReleaseDC(hDlg, hdc);


            HWND hBtn = GetDlgItem(hDlg, IDC_PAUSE);
            EnableWindow(hBtn, FALSE);

            hBtn = GetDlgItem(hDlg, IDC_START);
            EnableWindow(hBtn, TRUE);
        }
        break;
        case IDC_BUTTON_PRINT:
        {
            HDC hdc = GetDC(hDlg);
            TextOut(hdc, 0, 0, _T("Print"), 5);

            SetDlgItemText(hDlg, ID_TEXT, _T("Print"));

            ReleaseDC(hDlg, hdc);
        }
        break;
        case IDOK:
            EndDialog(hDlg, 0);
            break;
        case ID_EXIT:
            EndDialog(hDlg, 0);
            break;
        }

        break;

    }
    return 0;
}

#define IDC_CHILD1_BTN1 2000

LRESULT CALLBACK ClidWndWndProc1(HWND hWnd, UINT message, WPARAM wParam, LPARAM IParam)
{
    HWND hBtn;
    static bool bToggle = false;

    switch (message)
    {
    case WM_CREATE:
        SetTimer(hWnd, TIMER_SECOND, 20, AniProc);

        hBtn = CreateWindow(_T("button"), _T("OK"),
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 200, 10 , 100, 30 , hWnd, (HMENU)IDC_CHILD1_BTN1, hInst, NULL);
        break;
    case WM_COMMAND:
    {
        switch (LOWORD(wParam))
        {

        case IDC_CHILD1_BTN1:
            bToggle = !bToggle;
            break;

        default:
            break;
        }
    }
        break;
    case WM_PAINT: //그림 띄우기
    {
         PAINTSTRUCT ps;
         HDC hdc = BeginPaint(hWnd, &ps);
        //hdc = BeginPaint(hWnd, &ps);
        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...  
    
        //DrawBitmap(hWnd, hdc);
        DrwaBitmapDoubleBuffering(hWnd, hdc);
        DrawRectText(hdc);
        if (bToggle)
        {
            TextOut(hdc, 200, 50, _T("Button Clicked"), 14);
        }
    
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        break;
    default:
        break;
    }
    return DefWindowProc(hWnd,message,wParam, IParam);
}

LRESULT CALLBACK ClidWndWndProc2(HWND hWnd, UINT message, WPARAM wParam, LPARAM IParam)
{
    static POINT mousePos;

    switch (message)
    {
    case WM_CREATE:
        break;
    case WM_COMMAND:
        break;
    case WM_MOUSEMOVE:
    {
        GetCursorPos(&mousePos);
        InvalidateRect(hWnd, NULL, FALSE);
    }
    case WM_PAINT: //그림 띄우기
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        TCHAR str[128];
        wsprintf(str, TEXT("WORLD POSITION : (%04d, %04d)"), mousePos.x, mousePos.y);
        TextOut(hdc, 10, 30, str, lstrlen(str));

        ScreenToClient(hWnd, &mousePos);
        wsprintf(str, TEXT("LOCAL POSITION : (%04d, %04d)"), mousePos.x, mousePos.y);
        TextOut(hdc, 10, 50, str, lstrlen(str));

        EndPaint(hWnd, &ps);
    }
    break;
    
        break;
    case WM_DESTROY:
        break;
    default:
        break;
    }
    return DefWindowProc(hWnd, message, wParam, IParam);
}

LRESULT CALLBACK ClidWndWndProc3(HWND, UINT, WPARAM, LPARAM)
{
    return LRESULT();
}
