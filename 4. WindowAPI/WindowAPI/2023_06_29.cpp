// WindowAPI.cpp : 애플리케이션에 대한 진입점을 정의합니다.
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

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
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
    static POINT center = { 50,50 };
    static POINT mousePos;
    static int radius = 50;

    static BOOL bFlag = false;


    switch (message)
    {
    case WM_CREATE: //한번 만 호출(start느낌, 초기화)
    {
        GetClientRect(hWnd, &recView);
        //SetTimer(hWnd, timer_ID1, 500, NULL); //종료 꼭 필요!!
        //SetTimer(hWnd, timer_ID2, 1000, NULL); //종료 꼭 필요!!
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
    case WM_KEYDOWN: //눌려있는 상태 값 확인
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

        DrawCircle(hdc, center, radius);

        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY: //종료버튼을 누를 때 발생하는 이벤트
    {
       // KillTimer(hWnd, timer_ID1);
        //KillTimer(hWnd, timer_ID2);
        PostQuitMessage(0);
    }
    break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam); //디폴트로 처리함

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

    if(way==0)//위
        DrawText(hdc,_T("위쪽"), _tcslen(_T("위쪽")),&rec, DT_SINGLELINE | DT_CENTER|DT_VCENTER);
    else if (way == 1)//아래
        DrawText(hdc, _T("아래쪽"), _tcslen(_T("아래쪽")), &rec, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
    else if (way == 2)//왼쪽
        DrawText(hdc, _T("왼쪽"), _tcslen(_T("왼쪽")), &rec, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
    else if (way == 3)//오른쪽
        DrawText(hdc, _T("오른쪽"), _tcslen(_T("오른쪽")), &rec, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
    
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
