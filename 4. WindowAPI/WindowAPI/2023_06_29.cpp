// WindowAPI.cpp : ���ø����̼ǿ� ���� �������� �����մϴ�.
//

#include "framework.h"
#include "WindowAPI.h"
#include<iostream>
#include<vector>
#include<cmath>

#define MAX_LOADSTRING 100
#define PI (3.141592653589)
#define timer_ID1 (11)
#define timer_ID2 (12)
#define BSIZE (50)

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
void DrawGrid(HDC hdc, POINT start, POINT end, int count);
void DrawCircle(HDC hdc, POINT center, int radius);
void DrawSunflower(HDC hdc, POINT center, int radius, int num);
void DrawStar(HDC hdc, POINT center, int radius, int vertexs);
void DrawButton(HDC hdc, POINT center, int width, int height, int way);
void PaintArea(HDC hdc, POINT center, int width, int height);
double LengthPts(POINT a, POINT b);
BOOL InCircle(POINT a, POINT b);

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
    while (GetMessage(&msg, nullptr, 0, 0)) // �̺�Ʈ�� �־����
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

    return RegisterClassExW(&wcex);//�� �ʿ�
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
    static RECT recView;
    static POINT center = { 50,50 };
    static POINT mousePos;
    static int radius = 50;

    static BOOL bFlag = false;


    switch (message)
    {
    case WM_CREATE: //�ѹ� �� ȣ��(start����, �ʱ�ȭ)
    {
        GetClientRect(hWnd, &recView);
        //SetTimer(hWnd, timer_ID1, 500, NULL); //���� �� �ʿ�!!
        //SetTimer(hWnd, timer_ID2, 1000, NULL); //���� �� �ʿ�!!
    }
        break;
    case WM_TIMER:
    {
        if (wParam == timer_ID1)
        {
            center.x += 20;
            center.y += 20;
            InvalidateRect(hWnd, NULL, TRUE);
        }

        else if (wParam == timer_ID2)
        {
            //center.x -= 20;
            center.y -= 20;
            InvalidateRect(hWnd, NULL, TRUE);
        }
    }
    break;
    case WM_KEYDOWN: //�����ִ� ���� �� Ȯ��
    {
        if (wParam == VK_RIGHT)
        {
            center.x += radius;
            if (center.x + radius >= recView.right)
                center.x = recView.right- radius;
        }

        else if (wParam == VK_LEFT)
        {
            center.x -= radius;
            if (center.x - radius <= recView.left)
                center.x = recView.left + radius;
        }

        else if (wParam == VK_UP)
        {
            center.y -= radius;
            if (center.y - radius <= recView.top)
                center.y = recView.top+ radius;
        }

        else if (wParam == VK_DOWN)
        {
            center.y += radius;
            if (center.y + radius >= recView.bottom)
                center.y = recView.bottom - radius;
        }

        InvalidateRect(hWnd, NULL, TRUE);
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

        //if()
    }
    break;
    case WM_LBUTTONUP:
    {

    }
    break;
    case WM_MOUSEMOVE:
    {
        if (bFlag)
        {
            center.x = LOWORD(lParam);
            center.y = HIWORD(lParam);
            InvalidateRect(hWnd, NULL, TRUE);
        }
    }
    break;
    case WM_CHAR: //���� �Է� Ȯ��
    {

    }
    break;

    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // �޴� ������ ���� �м��մϴ�:
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
    case WM_PAINT: //�׸� ����
    {
        hdc = BeginPaint(hWnd, &ps);
        // TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�...  

        DrawCircle(hdc, center, radius);

        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY: //�����ư�� ���� �� �߻��ϴ� �̺�Ʈ
    {
       // KillTimer(hWnd, timer_ID1);
        //KillTimer(hWnd, timer_ID2);
        PostQuitMessage(0);
    }
    break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam); //����Ʈ�� ó����

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

void DrawGrid(HDC hdc, POINT start, POINT end, int count)
{
    long width = end.x - start.x;
    long height = end.y - start.y;

    for (int i = 0; i <= count; i++)
    {
        MoveToEx(hdc, start.x + (width / count) * i, start.y, NULL);
        LineTo(hdc, start.x + (width / count) * i, end.y);

        MoveToEx(hdc, start.x, start.y + (width / count) * i, NULL);
        LineTo(hdc, end.x, start.y + (width / count) * i);
    }
}

void DrawCircle(HDC hdc, POINT center, int radius)
{
    POINT start = { center.x - radius,center.y - radius };
    POINT end = { center.x + radius, center.y + radius };

    Ellipse(hdc, start.x, start.y, end.x, end.y);
}

void DrawSunflower(HDC hdc, POINT center, int radius, int num)
{
    DrawCircle(hdc, center, radius);
    long newRadius = radius * sin(PI / num) / (1 - sin(PI / num));

    for (long i = 1; i <= num; i++)
    {
        long newCenterX = center.x + (-1 * sin(2 * PI * i / num)) * (radius / (1 - sin(PI / num)));
        long newCenterY = center.y + cos(2 * PI * i / num) * (radius / (1 - sin(PI / num)));
        POINT newCenter = { newCenterX,newCenterY };
        DrawCircle(hdc, newCenter, newRadius);
    }
}

void DrawStar(HDC hdc, POINT center, int radius, int vertexs)
{
    POINT* points = new POINT[2 * vertexs];

    for (int i = 0; i < vertexs * 2; i += 2)
    {
        points[i].x = center.x + (-1 * sin(72 * PI * i * 0.5 / 180)) * (radius);
        points[i].y = center.y + cos(72 * PI * i * 0.5 / 180) * (radius);
    }

    for (int i = 1; i < vertexs * 2; i += 2)
    {
        points[i].x = center.x + cos(72 * PI * i * 0.5 / 180) * (radius * (1 - sin(72 * PI / 180)) * tan(0.1 * PI))
            + (-1 * sin(72 * PI * i * 0.5 / 180)) * (radius * tan(0.1 * PI));
        points[i].y = center.y + sin(72 * PI * i * 0.5 / 180) * (radius * (1 - sin(72 * PI / 180)) * tan(0.1 * PI))
            + cos(72 * PI * i * 0.5 / 180) * (radius * tan(0.1 * PI));
    }

    Polygon(hdc, points, 2 * vertexs);

    delete[] points;

}

void DrawButton(HDC hdc, POINT center, int width, int height, int way)
{
    int x1 = center.x - width / 2;
    int y1 = center.y - height / 2;
    int x2 = center.x + width / 2;
    int y2 = center.y + height / 2;

    RECT rec = { x1,y1,x2,y2 };
    Rectangle(hdc, x1, y1, x2, y2);

    if(way==0)//��
        DrawText(hdc,_T("����"), _tcslen(_T("����")),&rec, DT_SINGLELINE | DT_CENTER|DT_VCENTER);
    else if (way == 1)//�Ʒ�
        DrawText(hdc, _T("�Ʒ���"), _tcslen(_T("�Ʒ���")), &rec, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
    else if (way == 2)//����
        DrawText(hdc, _T("����"), _tcslen(_T("����")), &rec, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
    else if (way == 3)//������
        DrawText(hdc, _T("������"), _tcslen(_T("������")), &rec, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
    
}

void PaintArea(HDC hdc, POINT center, int width, int height)
{
    int x1 = center.x - width / 2;
    int y1 = center.y - height / 2;
    int x2 = center.x + width / 2;
    int y2 = center.y + height / 2;

    RECT rec = { x1,y1,x2,y2 };
    Rectangle(hdc, x1, y1, x2, y2);

}

double LengthPts(POINT a, POINT b)
{
    return (sqrt((float)((a.x-b.x)*(a.x-b.x))+(a.y-b.y)*(a.y-b.y)));
}

BOOL InCircle(POINT a, POINT b)
{
    if (LengthPts(a, b) < BSIZE) return TRUE;
    else return FALSE;
}
