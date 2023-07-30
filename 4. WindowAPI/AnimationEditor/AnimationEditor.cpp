// AnimationEditor.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "AnimationEditor.h"
#include<vector>
#include<commdlg.h>

#pragma comment(lib, "msimg32.lib")

using namespace std;

#define MAX_LOADSTRING 100
#define TIMER_FIRST 1
 
// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void DrawRect(HDC hdc, vector<RECT> & rec);
void DrawRectInstant(HDC hdc, RECT & rec);
void DrawPivot(HDC hdc);
void ShowPosInfo(HDC hdc);
void ShowProc(HDC hdc);
void CalcAns();
void ShowAni(HWND hWnd, HDC hdc);
VOID CALLBACK AniProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);
void Init(HWND hWnd);
INT_PTR CALLBACK Frame_Settings(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK Offset_Settings(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK File_Save(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
void SaveData();

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
    LoadStringW(hInstance, IDC_ANIMATIONEDITOR, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ANIMATIONEDITOR));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ANIMATIONEDITOR));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_ANIMATIONEDITOR);
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
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

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

struct AniAns
{
    POINT offset;
    int width;
    int height;
    POINT pivot;
};

int changePivot[4] = {0}; // up - down - left - right
int changePivotNum;



vector<AniAns> Datas;
int frameTotalCount;
int frameStart = 0;
int frameEnd;
int frameCount;
int aniSpeed=100;

POINT startMousePos;
POINT moveMousePos;
POINT endMousePos;
POINT ImageOffset={0,0};

vector<POINT> pivotPos;
vector<RECT> rec;
RECT rec2;

HBITMAP hImage;
BITMAP bit;

HWND hWd;
HDC hc;

bool showAni = false;

TCHAR fileName[100];

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;

    OPENFILENAME SFN;
    TCHAR str[100], lpstrFile[100] = _T("");
    TCHAR filter[] = _T("Every File(*.*) \0 *.*\0 Text File\0*.txt;*.doc\0");

    switch (message)
    {
    case WM_CREATE:
    {
        hImage = (HBITMAP)LoadImage(NULL, TEXT("Bitmap/test.bmp"),
            IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

        if (hImage == NULL)
        {
            DWORD dwError = GetLastError();
            MessageBox(NULL, _T("이미지 로드 에러"), _T("에러"), MB_OK);
        }

        GetObject(hImage, sizeof(BITMAP), &bit);

        SetTimer(hWnd, TIMER_FIRST, aniSpeed, AniProc);
        hWd = hWnd;
    }
        break;
    case WM_LBUTTONDOWN:
    {
        startMousePos = { LOWORD(lParam), HIWORD(lParam) };
    }
    break;

    case WM_MOUSEMOVE:
    {
        if (wParam & MK_LBUTTON)
        {
            moveMousePos = { LOWORD(lParam), HIWORD(lParam) };
            rec2 = { startMousePos.x, startMousePos.y,moveMousePos.x,moveMousePos.y };
            InvalidateRect(hWnd, NULL, FALSE);
        }
    }
        break;

    case WM_LBUTTONUP:
    {
        endMousePos = { LOWORD(lParam), HIWORD(lParam) };
        rec.push_back({ startMousePos.x, startMousePos.y,endMousePos.x,endMousePos.y });
        InvalidateRect(hWnd, NULL, FALSE);
    }
        break;
    case WM_RBUTTONDOWN:
    {
        pivotPos.push_back({ LOWORD(lParam), HIWORD(lParam) });
        InvalidateRect(hWnd, NULL, FALSE);
    }
        break;

    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case ID_OFFSET:
            {
                DialogBox(hInst, MAKEINTRESOURCE(IDD_OFFSET), hWnd, Offset_Settings);
            }
                break;

            case ID_INIT:
            {
                Init(hWnd);
                showAni = false;
            }
            break;
            case ID_MAKE_ANI:
            {
                CalcAns();
                showAni = true;
            }
                break;
            case ID_FRAMESETTINGS:
            {
                DialogBox(hInst, MAKEINTRESOURCE(IDD_FRAMESETTINGS), hWnd, Frame_Settings);
            }
                break;
            case ID_SAVE:
            {
                SaveData();
                showAni = false;
            }
                break;
                
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
             hc = hdc;
             if (showAni)
             {
                 ShowAni(hWnd,hdc);
             }

             else
             {
                 ShowProc(hdc);
             }

             EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
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

INT_PTR CALLBACK Offset_Settings(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
    {
        SetDlgItemInt(hDlg, IDC_OFFSET_X, ImageOffset.x, FALSE);
        SetDlgItemInt(hDlg, IDC_OFFSET_Y, ImageOffset.y, FALSE);
    }
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case ID_OFFSETOK:
            ImageOffset.x = GetDlgItemInt(hDlg, IDC_OFFSET_X, NULL, FALSE);
            ImageOffset.y = GetDlgItemInt(hDlg, IDC_OFFSET_Y, NULL, FALSE);

            InvalidateRect(hWd, NULL, TRUE);

            return (INT_PTR)TRUE;
            break;
        case IDOK:
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
            break;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

INT_PTR CALLBACK Frame_Settings(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
    {
        SetDlgItemInt(hDlg, IDC_FRAME_START, 0, FALSE);
        SetDlgItemInt(hDlg, IDC_FRAME_END, frameEnd, FALSE);
        SetDlgItemInt(hDlg, IDC_EDIT_PIVOTNUM, 1, FALSE);
        SetDlgItemInt(hDlg, IDC_EDIT_SPEED, aniSpeed, FALSE);
    }
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case ID_CLAMP:
            if (GetDlgItemInt(hDlg, IDC_FRAME_START, NULL, FALSE) >= 0 &&
                GetDlgItemInt(hDlg, IDC_FRAME_END, NULL, FALSE) < frameTotalCount)
            {
                frameStart = GetDlgItemInt(hDlg, IDC_FRAME_START, NULL, FALSE);
                frameEnd = GetDlgItemInt(hDlg, IDC_FRAME_END, NULL, FALSE);
            }
            else
            {
                MessageBox(NULL, _T("프레임 범위를 제대로 입력하세요."), _T("에러"), MB_OK);
            }

            break;
        case IDC_UP:
            if (GetDlgItemInt(hDlg, IDC_EDIT_PIVOTNUM, NULL, FALSE) >= 0 &&
                GetDlgItemInt(hDlg, IDC_EDIT_PIVOTNUM, NULL, FALSE) < frameTotalCount)
            {
                changePivotNum = GetDlgItemInt(hDlg, IDC_EDIT_PIVOTNUM, NULL, FALSE);
                Datas[changePivotNum].pivot.y++;
            }

            else
            {
                MessageBox(NULL, _T("Pivot번호를 제대로 입력하세요."), _T("에러"), MB_OK);
            }

            break;
        case IDC_DOWN:
            if (GetDlgItemInt(hDlg, IDC_EDIT_PIVOTNUM, NULL, FALSE) >= 0 &&
                GetDlgItemInt(hDlg, IDC_EDIT_PIVOTNUM, NULL, FALSE) < frameTotalCount)
            {
                changePivotNum = GetDlgItemInt(hDlg, IDC_EDIT_PIVOTNUM, NULL, FALSE);
                Datas[changePivotNum].pivot.y--;
            }

            else
            {
                MessageBox(NULL, _T("Pivot번호를 제대로 입력하세요."), _T("에러"), MB_OK);
            }
            break;
        case IDC_LEFT:
            if (GetDlgItemInt(hDlg, IDC_EDIT_PIVOTNUM, NULL, FALSE) >= 0 &&
                GetDlgItemInt(hDlg, IDC_EDIT_PIVOTNUM, NULL, FALSE) < frameTotalCount)
            {
                changePivotNum = GetDlgItemInt(hDlg, IDC_EDIT_PIVOTNUM, NULL, FALSE);
                Datas[changePivotNum].pivot.x++;
            }
            else
            {
                MessageBox(NULL, _T("Pivot번호를 제대로 입력하세요."), _T("에러"), MB_OK);
            }
            break;
        case IDC_RIGHT:
            if (GetDlgItemInt(hDlg, IDC_EDIT_PIVOTNUM, NULL, FALSE) >= 0 &&
                GetDlgItemInt(hDlg, IDC_EDIT_PIVOTNUM, NULL, FALSE) < frameTotalCount)
            {
                changePivotNum = GetDlgItemInt(hDlg, IDC_EDIT_PIVOTNUM, NULL, FALSE);
                Datas[changePivotNum].pivot.x--;
            }
            else
            {
                MessageBox(NULL, _T("Pivot번호를 제대로 입력하세요."), _T("에러"), MB_OK);
            }
            break;
        case ID_SPEEDOK:
        {
            aniSpeed = GetDlgItemInt(hDlg, IDC_EDIT_SPEED, NULL, FALSE);
            SetTimer(hWd, TIMER_FIRST, aniSpeed, AniProc);
        }
            break;
        case IDC_SPEED_UP:
        {
            SetDlgItemInt(hDlg, IDC_EDIT_SPEED, ++aniSpeed, FALSE);
            SetTimer(hWd, TIMER_FIRST, aniSpeed, AniProc);
        }
            break;
        case IDC_SPEED_DOWN:
        {
            if (aniSpeed > 0)
            {
                SetDlgItemInt(hDlg, IDC_EDIT_SPEED, --aniSpeed, FALSE);
                SetTimer(hWd, TIMER_FIRST, aniSpeed, AniProc);
            }

            else
            {
                MessageBox(NULL, _T("Ani 속도는 음수가 될 수 없습니다."), _T("에러"), MB_OK);
            }
        }
            break;
        case IDOK:
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
            break;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

INT_PTR CALLBACK File_Save(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND: 
        if (LOWORD(wParam) == IDOK)
        {
            GetDlgItemText(hDlg, IDC_EDIT_FILENAME, fileName, sizeof(fileName) - 1);
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}


void DrawRect(HDC hdc, vector<RECT> & rec)
{
    HPEN hPen, oldPen;
    HBRUSH hBrush, hOldBrush;
    hPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
    oldPen = (HPEN)SelectObject(hdc, hPen);
    hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
    hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

    for (int i = 0; i < rec.size(); i++)
    {
        Rectangle(hdc, rec[i].left, rec[i].top, rec[i].right, rec[i].bottom);
    }

    SelectObject(hdc, oldPen);
    DeleteObject(hPen);
    SelectObject(hdc, hOldBrush);
    DeleteObject(hBrush);
    
}

void DrawRectInstant(HDC hdc, RECT& rec)
{
    HPEN hPen, oldPen;
    HBRUSH hBrush, hOldBrush;
    hPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
    oldPen = (HPEN)SelectObject(hdc, hPen);
    hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
    hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

    Rectangle(hdc, rec.left, rec.top, rec.right, rec.bottom);

    SelectObject(hdc, oldPen);
    DeleteObject(hPen);
    SelectObject(hdc, hOldBrush);
    DeleteObject(hBrush);
}

void DrawPivot(HDC hdc)
{
    int radius = 2;

    HBRUSH hBrush, oldBrush;
    hBrush = CreateSolidBrush(RGB(255, 0, 0));
    oldBrush = (HBRUSH)SelectObject(hdc, hBrush);

    for (int i = 0; i < pivotPos.size(); i++)
    {
        Ellipse(hdc, pivotPos[i].x - radius, pivotPos[i].y - radius, pivotPos[i].x + radius, pivotPos[i].y + radius);
    }
   
    SelectObject(hdc, oldBrush);
    DeleteObject(hBrush);
}

void ShowPosInfo(HDC hdc)
{

    for (int i = 0; i < rec.size(); i++)
    {
        TCHAR temp[20];
        _stprintf_s(temp, L"[%d,%d]", rec[i].left, rec[i].top);
        TextOut(hdc, rec[i].left, rec[i].top, temp, _tcslen(temp));

        TCHAR temp1[20];
        _stprintf_s(temp1, L"[%d,%d]", rec[i].right, rec[i].bottom);
        TextOut(hdc, rec[i].right, rec[i].bottom, temp1, _tcslen(temp1));
    }

    TCHAR temp2[20];
    _stprintf_s(temp2, L"[%d,%d]", rec2.left, rec2.top);
    TextOut(hdc, rec2.left, rec2.top, temp2, _tcslen(temp2));

    TCHAR temp3[20];
    _stprintf_s(temp3, L"[%d,%d]", rec2.right, rec2.bottom);
    TextOut(hdc, rec2.right, rec2.bottom, temp3, _tcslen(temp3));

    for (int i = 0; i < pivotPos.size(); i++)
    {
        TCHAR temp4[20];
        _stprintf_s(temp4, L"[%d,%d]", pivotPos[i].x, pivotPos[i].y);
        TextOut(hdc, pivotPos[i].x, pivotPos[i].y, temp4, _tcslen(temp4));
    }


}

void ShowProc(HDC hdc)
{
    HDC hMemDC;
    HBITMAP hOldBitmap;

    HDC hMemDC2;
    HBITMAP hOldBitmap2;

    int bx, by;

    hMemDC = CreateCompatibleDC(hdc);
    hOldBitmap = (HBITMAP)SelectObject(hMemDC, hImage);
    bx = bit.bmWidth;
    by = bit.bmHeight;
    DrawRect(hMemDC, rec);

    BitBlt(hdc, -ImageOffset.x, -ImageOffset.y, bx, by, hMemDC, 0, 0, SRCCOPY);

    SelectObject(hMemDC, hOldBitmap);
    DeleteDC(hMemDC);

    DrawRectInstant(hdc, rec2);
    DrawPivot(hdc);
    //ShowPosInfo(hdc);
}

void CalcAns()
{
    if (rec.size() != pivotPos.size())
    {
        MessageBox(NULL, _T("영역과 pivot의 갯수와 원소 위치는 동일해야 합니다."), _T("에러"), MB_OK);
        return;
    }

    frameTotalCount = rec.size();
    frameEnd = frameTotalCount-1;

    for (int i = 0; i < frameTotalCount; i++)
    {
        AniAns temp;

        temp.offset = { rec[i].left,rec[i].top };
        temp.width = rec[i].right - rec[i].left;
        temp.height = rec[i].bottom - rec[i].top;
        temp.pivot.x = pivotPos[i].x - rec[i].left;
        temp.pivot.y= pivotPos[i].y - rec[i].top;

        Datas.push_back(temp);
    }


}

void ShowAni(HWND hWnd, HDC hdc)
{

    HDC hMemDC;
    HBITMAP holdBitmap;

    hMemDC = CreateCompatibleDC(hdc);
    holdBitmap = (HBITMAP)SelectObject(hMemDC, hImage);

    POINT showPos = { 250,250 };

    int bx = Datas[frameCount].width;
    int by = Datas[frameCount].height;
    int xStart = Datas[frameCount].offset.x;
    int yStart = Datas[frameCount].offset.y;
    int posX = showPos.x - Datas[frameCount].pivot.x;
    int posY = showPos.y - Datas[frameCount].pivot.y;

    TransparentBlt(hdc, posX, posY, bx, by, hMemDC, xStart, yStart, bx, by, RGB(255, 0, 255));

    TCHAR temp[20];
    _stprintf_s(temp, L"Frame_Num: %d", frameCount);
    TextOut(hdc, 100, 100, temp, _tcslen(temp));

    SelectObject(hMemDC, holdBitmap);
    DeleteDC(hMemDC);
}

VOID CALLBACK AniProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
    if (showAni)
    {
        frameCount++;

        if (frameCount > frameEnd)
        {
            frameCount = frameStart;
        }


        InvalidateRect(hWnd, NULL, TRUE);
    }
}

void Init(HWND hWnd)
{

    startMousePos = {};
    moveMousePos = {};
    endMousePos = {};

    pivotPos.clear();
    rec.clear();
    rec2 = {};
    frameCount = 0;
    frameTotalCount = 0;
    Datas.clear();

    hImage = (HBITMAP)LoadImage(NULL, TEXT("Bitmap/test.bmp"),
        IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

    if (hImage == NULL)
    {
        DWORD dwError = GetLastError();
        MessageBox(NULL, _T("이미지 로드 에러"), _T("에러"), MB_OK);
    }

    GetObject(hImage, sizeof(BITMAP), &bit);

    InvalidateRect(hWnd, NULL, TRUE);

}

void SaveData()
{
    DialogBox(hInst, MAKEINTRESOURCE(IDD_SAVEDATA), hWd, File_Save);

    HANDLE hFile;
    hFile = CreateFile(fileName, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, 0, 0);

    int n = rec.size();
    DWORD size;
    for (int i = 0; i < n; i++)
    {
        TCHAR index[50];
        _stprintf_s(index, L"Frame_Num: %d\n", i);
        WriteFile(hFile, index, (DWORD)_tcslen(index) * sizeof(TCHAR), &size, NULL);

        TCHAR offset[50];
        _stprintf_s(offset, L"Offset: [%d, %d]\n", Datas[i].offset.x, Datas[i].offset.y);
        WriteFile(hFile, offset, (DWORD)_tcslen(offset) * sizeof(TCHAR), &size, NULL);

        TCHAR Width_Height[50];
        _stprintf_s(Width_Height, L"Width_Height: [%d, %d]\n", Datas[i].width, Datas[i].height);
        WriteFile(hFile, Width_Height, (DWORD)_tcslen(Width_Height) * sizeof(TCHAR), &size, NULL);

        TCHAR pivot[50];
        _stprintf_s(pivot, L"Pivot: [%d, %d]\n\n", Datas[i].pivot.x, Datas[i].pivot.y);
        WriteFile(hFile, pivot, (DWORD)_tcslen(pivot) * sizeof(TCHAR), &size, NULL);
    }

    TCHAR speed[50];
    _stprintf_s(speed, L"Ani_Speed: %d\n\n", aniSpeed);
    WriteFile(hFile, speed, (DWORD)_tcslen(speed) * sizeof(TCHAR), &size, NULL);

    MessageBox(NULL, _T("데이터가 저장되었습니다."), _T("알림"), MB_OK);

    CloseHandle(hFile);
}
