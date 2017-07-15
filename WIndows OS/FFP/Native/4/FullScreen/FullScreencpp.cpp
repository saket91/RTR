#include "windows.h"
#include "Windowsx.h"
#include "stdio.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

bool gbIsFullScreen = false;

WINDOWPLACEMENT wpPrev = { sizeof(WINDOWPLACEMENT) }; //initilizing first member of structure
MONITORINFO mi = { sizeof(MONITORINFO) }; //initilizing structure
DWORD dwstyle = 0;

void ToggleFullScreen(HWND hwnd)
{
	if (!gbIsFullScreen)
	{
		//switch to full screen mode
		 dwstyle = GetWindowLong(hwnd, GWL_STYLE);

		if (dwstyle & WS_OVERLAPPEDWINDOW)
		{
			bool bIsWindowPlacement = GetWindowPlacement(hwnd, &wpPrev);
			//Get Hmonitor 
			HMONITOR hmonitor = MonitorFromWindow(hwnd, MONITORINFOF_PRIMARY);

			bool bIsMoniterInfo = GetMonitorInfo(hmonitor, &mi);

			if (bIsMoniterInfo && bIsWindowPlacement)
			{
				SetWindowLong(hwnd, GWL_STYLE, dwstyle & ~WS_OVERLAPPEDWINDOW);
				SetWindowPos(hwnd, HWND_TOP,
					mi.rcMonitor.left, mi.rcMonitor.top,
					mi.rcMonitor.right - mi.rcMonitor.left,
					mi.rcMonitor.bottom - mi.rcMonitor.top,
					SWP_NOZORDER | SWP_FRAMECHANGED);
				gbIsFullScreen = true;

			}
		}
	}
	else
	{
		//switch to normal mode
		gbIsFullScreen = false;
		SetWindowLong(hwnd, GWL_STYLE, dwstyle & WS_OVERLAPPEDWINDOW);
		SetWindowPlacement(hwnd, &wpPrev);
		SetWindowPos(hwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
	}
}



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int cmdShow)
{
	//Variable decleration

	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;

	TCHAR szAppname[] = TEXT("My App");

	//Initilize Wndclass
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.lpszClassName = szAppname;
	wndclass.lpszMenuName = NULL;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.hInstance = hInstance;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpfnWndProc = WndProc;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.cbWndExtra = 0;
	wndclass.cbClsExtra = 0;

	//Register Class
	RegisterClassEx(&wndclass);

	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenheight = GetSystemMetrics(SM_CYSCREEN);

	int x = (screenWidth / 2) - (800 / 2); //800 window width
	int y = (screenheight / 2) - (600 / 2); //600 window height

	hwnd = CreateWindow(szAppname, TEXT("My First Window"), WS_OVERLAPPEDWINDOW,
		x, y, 800, 600, NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, cmdShow);
	UpdateWindow(hwnd);

	//message loop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return ((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wparam, LPARAM lparam)
{
	switch (iMsg)
	{
	case WM_KEYDOWN:
	{
		TCHAR messagesg[MAX_PATH];
		switch (LOWORD(wparam))
		{
		case 0x46:  //F - full screen toggle
			ToggleFullScreen(hwnd);
			break;

		}
	}
	break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	}

	return (DefWindowProc(hwnd, iMsg, wparam, lparam));
}


