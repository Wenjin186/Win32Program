// GDI视频项目.cpp : 定义应用程序的入口点。
//

#include "Resource.h"
#include "framework.h"
#include "GDI视频项目.h"
#include <string>

using namespace std;

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

HBITMAP hbmpBack = NULL;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此处放置代码。

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_GDI, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GDI));

    MSG msg;

    // 主消息循环:
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
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GDI));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_GDI);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中

   hbmpBack = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP2));

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
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 分析菜单选择:
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
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 在此处添加使用 hdc 的任何绘图代码...

            HDC hDCMem = CreateCompatibleDC(hdc);
            HBITMAP hOldBmp = (HBITMAP)SelectObject(hDCMem, hbmpBack);
            BITMAP bmp;
            GetObject(hbmpBack, sizeof(BITMAP), &bmp); //不知道干什么的
            
            //BitBlt(hdc, 0, 0, bmp.bmWidth, bmp.bmHeight, hDCMem, 0, 0, SRCCOPY);
            
            RECT rcClient;
            GetClientRect(hWnd, &rcClient);
            int nWidth = rcClient.right - rcClient.left;
            int nHeight = rcClient.bottom - rcClient.top;
            StretchBlt(hdc, 0, 0, nWidth, nHeight, hDCMem, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);

            SelectObject(hDCMem, hOldBmp); //不知道干什么的
            DeleteDC(hDCMem);

            //==============
            //绘制标题
            LOGFONT logfont;
            memset(&logfont, 0, sizeof(LOGFONT));
            logfont.lfWeight = 20;
            logfont.lfHeight = 40;
            logfont.lfCharSet = GB2312_CHARSET;
            _tcscpy(logfont.lfFaceName, TEXT("宋体"));
            HFONT hFont = CreateFontIndirect(&logfont);
            HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);

            COLORREF clrOldText = SetTextColor(hdc, RGB(0, 0, 128));

            SetBkMode(hdc, TRANSPARENT);

            wstring str = L"北岛网站流量统计报表";
            DrawText(hdc, str.c_str(), str.length(), &rcClient, DT_CENTER | DT_TOP | DT_SINGLELINE);

            SelectObject(hdc, hOldFont);
            DeleteObject(hFont);

            SetTextColor(hdc, clrOldText);

            TextOut(hdc, 5, 100, TEXT("7000"), 4);
            TextOut(hdc, 5, 130, TEXT("6000"), 4);
            TextOut(hdc, 5, 160, TEXT("5000"), 4);
            TextOut(hdc, 5, 190, TEXT("4000"), 4);
            TextOut(hdc, 5, 220, TEXT("3000"), 4);
            TextOut(hdc, 5, 250, TEXT("2000"), 4);
            TextOut(hdc, 5, 280, TEXT("1000"), 4);
            TextOut(hdc, 106, 323, TEXT("1月"), 2);
            TextOut(hdc, 182, 323, TEXT("2月"), 2);
            TextOut(hdc, 250, 323, TEXT("3月"), 2);

            TextOut(hdc, 5+380, 100, TEXT("7000"), 4);
            TextOut(hdc, 5+380, 130, TEXT("6000"), 4);
            TextOut(hdc, 5+380, 160, TEXT("5000"), 4);
            TextOut(hdc, 5+380, 190, TEXT("4000"), 4);
            TextOut(hdc, 5+380, 220, TEXT("3000"), 4);
            TextOut(hdc, 5+380, 250, TEXT("2000"), 4);
            TextOut(hdc, 5+380, 280, TEXT("1000"), 4);
            TextOut(hdc, 106+380, 323, TEXT("1月"), 2);
            TextOut(hdc, 182+380, 323, TEXT("2月"), 2);
            TextOut(hdc, 250+380, 323, TEXT("3月"), 2);

            TextOut(hdc, 700, 323, TEXT("4月"), 2);
            TextOut(hdc, 125, 700, TEXT("访问群体"), 4);
            TextOut(hdc, 525, 700, TEXT("学习等级"), 4);
            
            

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

// “关于”框的消息处理程序。
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
