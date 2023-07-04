// WindowAPI.cpp : ���ø����̼ǿ� ���� �������� �����մϴ�.
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


// ���� ����:
HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.
WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.

// �� �ڵ� ��⿡ ���Ե� �Լ��� ������ �����մϴ�:
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
    static POINT mousePos;
    static vector<CObject*> obgs;
    enum OBJECT { CIRCLE, RECTANGLE, STAR, NONE };
    static int randNum = NONE, randRadius;
    static int verson = 1;

    srand(time(NULL));

    switch (message)
    {
    case WM_CREATE: //�ѹ� �� ȣ��(start����, �ʱ�ȭ)
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

        CObject* Obj;

        if (randNum == 0) //��
        {
            CObject* Obj = new CCircle(mousePos);
            obgs.push_back(Obj);
        }

        else if (randNum == 1) //�簢��
        {
            CObject* Obj = new CRectangle(mousePos);
            obgs.push_back(Obj);
        }

        else if (randNum == 2) //��
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
                //_stprintf_s(str,_T("%s ������ ���ڽ��ϱ�?",ofn.IpstrFile));
                OutFormFile(ofn.lpstrFile, hWnd);
                //MessageBox(hWnd, str, _T("���ϼ���"), MB_OK);
            }
        }
            break;
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
    case WM_PAINT: //�׸� ����
    {
        hdc = BeginPaint(hWnd, &ps);
        // TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�...  

        for (int i = 0; i < obgs.size(); i++)
        {
            obgs[i]->Draw(hdc);
        }

        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY: //�����ư�� ���� �� �߻��ϴ� �̺�Ʈ
    {

        KillTimer(hWnd, TIMER_FIRST);
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
