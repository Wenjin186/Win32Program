#include <Windows.h>

//该程序实现了显示窗口的最简代码，其中并不涉及任何消息调用。
//在wMinMain函数返回直接while(true)，会阻止窗口因为主函数退出而造成的闪退

//ASCII码版的调用WinMain，Unicode调用wWinMain
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    PTSTR szCmdLine, int iCmdShow)
{
    HWND         hwnd;
    MSG          msg;
    WNDCLASS     wndclass;

    wndclass.style = CS_OWNDC;
    wndclass.lpfnWndProc = DefWindowProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = NULL;
    wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = TEXT("mywindow");

    RegisterClass(&wndclass);

    hwnd = CreateWindow(wndclass.lpszClassName,                  // window class name
        TEXT("我的窗口"), // window caption
        WS_OVERLAPPEDWINDOW,        // window style
        CW_USEDEFAULT,              // initial x position
        CW_USEDEFAULT,              // initial y position
        CW_USEDEFAULT,              // initial x size
        CW_USEDEFAULT,              // initial y size
        NULL,                       // parent window handle
        NULL,                       // window menu handle
        hInstance,                  // program instance handle
        NULL);                     // creation parameters


    ShowWindow(hwnd, iCmdShow);

    while (true);

    return 0;
}