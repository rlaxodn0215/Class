// WindowAPI.cpp : ���ø����̼ǿ� ���� �������� �����մϴ�.
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


// ���� ����:
HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.
WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.

// �� �ڵ� ��⿡ ���Ե� �Լ��� ������ �����մϴ�:
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

    // TODO: ���⿡ �ڵ带 �Է��մϴ�.

    // ���� ���ڿ��� �ʱ�ȭ�մϴ�.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWAPI, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // ���ø����̼� �ʱ�ȭ�� �����մϴ�:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWAPI));

    MSG msg;

    // �⺻ �޽��� �����Դϴ�:
    //while (GetMessage(&msg, nullptr, 0, 0)) // �̺�Ʈ�� �־����
    //{
    //    if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
    //    {
    //        TranslateMessage(&msg);
    //        DispatchMessage(&msg);
    //    }
    //}

    while (true) // �̺�Ʈ�� �־����
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
//  �Լ�: MyRegisterClass()
//
//  �뵵: â Ŭ������ ����մϴ�.
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
    RegisterClassExW(&wcex);//�� �ʿ�



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
//   �Լ�: InitInstance(HINSTANCE, int)
//
//   �뵵: �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����ϴ�.
//
//   �ּ�:
//
//        �� �Լ��� ���� �ν��Ͻ� �ڵ��� ���� ������ �����ϰ�
//        �� ���α׷� â�� ���� ���� ǥ���մϴ�.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) //�����츦 �����ϴ� �κ�
{
    hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

    HWND hWnd = CreateWindowW(szWindowClass, _T("szTitle"), WS_OVERLAPPEDWINDOW,
        200, 200, 1024, 768, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow); //�����찡 ������
    UpdateWindow(hWnd);

    return TRUE;
}

//
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  �뵵: �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND  - ���ø����̼� �޴��� ó���մϴ�.
//  WM_PAINT    - �� â�� �׸��ϴ�.
//  WM_DESTROY  - ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) //Ű �Է� ���� ���� wParam�� ����� 
//�޼��� �߻����� ���ο� �Լ� ȣ�� (case���� �Լ��� �����̴�, ����X)->�ҷ��� static �Լ� ���
{
    PAINTSTRUCT ps;
    HDC hdc;
    SIZE size;
    //LPCWCHAR str = (LPCWCHAR)_T("Ű ���ȴ�!!");

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
        GetClientRect(hWnd, &recView); //������ ũ�Ⱑ ����Ǿ����� ���

    }
    break;
    case WM_CREATE: //�ѹ� �� ȣ��(start����, �ʱ�ȭ)
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
    case WM_KEYDOWN: //�����ִ� ���� �� Ȯ��
    {
        if (wParam == 0x31) //1�� ���
        {
            verson = 1;
        }

        else if (wParam == 0x32) //2�� ���
        {
            verson = 2;
        }

        else if (wParam == 0x33) //3�� ���
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
    case WM_CHAR: //���� �Է� Ȯ��
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
        // �޴� ������ ���� �м��մϴ�:
        switch (wmId)
        {
        case ID_DRAW_CIRCLE:
        {
            int temp = randNum;
            int ans = MessageBox(hWnd, _T("�� �׸���?"), _T("��������"), MB_YESNOCANCEL);
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
            //int ans = MessageBox(hWnd, _T("�׸� �׸���?"), _T("��������"), MB_YESNOCANCEL);

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
            int ans = MessageBox(hWnd, _T("�� �׸���?"), _T("��������"), MB_YESNOCANCEL);
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

        case IDM_ABOUT: //����->����
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT: //������
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }

    }
    break;
    //case WM_PAINT: //�׸� ����
    //{
    //    hdc = BeginPaint(hWnd, &ps);
    //    // TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�...  

    //    //DrawBitmap(hWnd, hdc);
    //    DrwaBitmapDoubleBuffering(hWnd, hdc);
    //    DrawRectText(hdc);

    //    EndPaint(hWnd, &ps);
    //}
    //break;
    case WM_DESTROY: //�����ư�� ���� �� �߻��ϴ� �̺�Ʈ
    {
        DeleteBitmap();
        KillTimer(hWnd, TIMER_SECOND);
        PostQuitMessage(0);
    }
    break;
    default:
    {
        return DefWindowProc(hWnd, message, wParam, lParam); //����Ʈ�� ó����
    }
    break;

    return 0;

    }

}

// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
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
    ////����
    //{
    //    hBackImage = (HBITMAP)LoadImage(NULL, TEXT("Images/����.bmp"),
    //        IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

    //    if (hBackImage == NULL)
    //    {
    //        DWORD dwError = GetLastError();
    //        MessageBox(NULL, _T("�̹��� �ε� ����_1"), _T("����"), MB_OK);
    //        return;
    //    }

    //    GetObject(hBackImage, sizeof(BITMAP), &bitBack);
    //}


    //�ð�
    {
        hTransparentImage = (HBITMAP)LoadImage(NULL, TEXT("Images/sigong.bmp"),
            IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

        if (hTransparentImage == NULL)
        {
            DWORD dwError = GetLastError();
            MessageBox(NULL, _T("�̹��� �ε� ����_2"), _T("����"), MB_OK);
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
            MessageBox(NULL, _T("�̹��� �ε� ����_3"), _T("����"), MB_OK);
            return;
        }

        GetObject(hAniImage, sizeof(BITMAP), &bitAni);

        //: 
        RUN_FRAME_MAX = bitAni.bmWidth / SPRITE_SIZE_X - 1; //���� ��������
        RUN_FRAME_MIN = 2; //�� ���� ������ �޸��� ����
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
            MessageBox(NULL, _T("�̹��� �ε� ����_4"), _T("����"), MB_OK);
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
    {//����
        hMenDC = CreateCompatibleDC(hdc);
        hodBitmap = (HBITMAP)SelectObject(hMenDC, hBackImage);
        bx = bitBack.bmWidth;
        by = bitBack.bmHeight;

        BitBlt(hdc, 0, 0, bx, by, hMenDC, 0, 0, SRCCOPY);

        SelectObject(hMenDC, hodBitmap);
        DeleteDC(hMenDC);
    }

    {//�ð�

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

    InvalidateRect(hWnd, NULL, FALSE); // true: ����� ���� �� ������, false: ������ X, ��� ������ �ܻ� ���� 
}

static int yPos = 0;

void DrawRectText(HDC hdc)
{
    TCHAR strTest[] = _T("�̹��� ���");
    TextOut(hdc, 10, yPos, strTest, _tcslen(strTest));
}

void Update()
{
    //: wm_keydown, wm_keyup -> ������ ���������� ���� ����
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

    //{//����

    //    hMenDC2 = CreateCompatibleDC(hMenDC);
    //    hodBitmap2 = (HBITMAP)SelectObject(hMenDC2, hBackImage);
    //    bx = bitBack.bmWidth;
    //    by = bitBack.bmHeight;

    //    BitBlt(hMenDC, 0, 0, bx, by, hMenDC2, 0, 0, SRCCOPY);

    //    SelectObject(hMenDC2, hodBitmap2);
    //    DeleteDC(hMenDC2);
    //}

    {//�ð�

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
    //<< hMenDC �� �׷��ֱ�

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



    //hdc�� �׷��ֱ�
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
    case WM_PAINT: //�׸� ����
    {
         PAINTSTRUCT ps;
         HDC hdc = BeginPaint(hWnd, &ps);
        //hdc = BeginPaint(hWnd, &ps);
        // TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�...  
    
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
    case WM_PAINT: //�׸� ����
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
