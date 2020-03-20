#include <Windows.h>
#include <stdio.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

int wWinMain(HINSTANCE hInstance, HINSTANCE, PTSTR szCmdLine, int iCmdShow) {

	TCHAR className[] = TEXT("Message Window");

	WNDCLASS wndclass;
	HWND hwnd;
	MSG msg;

	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = NULL;
	wndclass.hCursor = LoadCursor(NULL, IDC_WAIT);
	wndclass.hbrBackground = NULL;
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = className;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;

	RegisterClass(&wndclass);

	hwnd = CreateWindow(className, TEXT("带消息的窗口"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		//MessageBox(hwnd, TEXT("haha"), TEXT("haha"), MB_OK);
		TranslateMessage(&msg);

		if (msg.message == WM_KEYDOWN) {
			printf("hellofffff\n");
		}

		DispatchMessage(&msg);
	}

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//printf("%d\n", message);
	//printf("=====\n");
	if (message == WM_KEYDOWN) {
		printf("WinProc hellofffff\n");
	}
    HDC         hdc;
    PAINTSTRUCT ps;
    RECT        rect;

    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}

int wmain() {

	wWinMain(GetModuleHandle(NULL), NULL, NULL, SW_SHOWNORMAL);

	return 0;
}