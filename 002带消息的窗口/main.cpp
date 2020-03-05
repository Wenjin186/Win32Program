#include <Windows.h>

int wWinMain(HINSTANCE hInstance, HINSTANCE, PTSTR szCmdLine, int iCmdShow) {

	TCHAR className[] = TEXT("Message Window");

	WNDCLASS wndclass;
	HWND hwnd;
	MSG msg;

	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = NULL;
	wndclass.hCursor = NULL;
	wndclass.hbrBackground = NULL;
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = className;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = DefWindowProc;

	RegisterClass(&wndclass);

	hwnd = CreateWindow(className, TEXT("带消息的窗口"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, iCmdShow);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}