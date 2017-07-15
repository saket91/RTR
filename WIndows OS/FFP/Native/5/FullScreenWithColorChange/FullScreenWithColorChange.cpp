#include "windows.h"
#include "Windowsx.h"
#include "stdio.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

bool gbIsFullScreen = false;

WINDOWPLACEMENT wpPrev = { sizeof(WINDOWPLACEMENT) }; //initilizing first member of structure
MONITORINFO mi = { sizeof(MONITORINFO) }; //initilizing structure
DWORD dwstyle = 0;

int colorcode = -1; //   R/G/B/C/M/Y/K/W -- 1/2/3/4/5/6/7/8

COLORREF colors[8] = { RGB(255,0,0),   RGB(0,255,0),
RGB(0,0,255),   RGB(0,255,255),
RGB(255,0,255),   RGB(255,255,0),
RGB(0,0,0),   RGB(255,255,255), };


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

	hwnd = CreateWindow(szAppname, TEXT("My First Window"), WS_OVERLAPPEDWINDOW,
		100, 10, 1200, 700, NULL, NULL, hInstance, NULL);

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

		case 0x52: //R - set red color
			colorcode = 1;
			InvalidateRect(hwnd, NULL, TRUE);
			break;

		case 0x47: //G - set Green color
			colorcode = 2;
			InvalidateRect(hwnd, NULL, TRUE);
			break;

		case 0x42: //B - set Blue color
			colorcode = 3;
			InvalidateRect(hwnd, NULL, TRUE);
			break;

		case 0x43: //C - set cyan color
			colorcode = 4;
			InvalidateRect(hwnd, NULL, TRUE);
			break;

		case 0x4D: //M - set Magenta color
			colorcode = 5;
			InvalidateRect(hwnd, NULL, TRUE);
			break;

		case 0x59: //Y - set Yellow color
			colorcode = 6;
			InvalidateRect(hwnd, NULL, TRUE);
			break;

		case 0x4B: //K - set Black color
			colorcode = 7;
			InvalidateRect(hwnd, NULL, TRUE);
			break;

		case 0x57: //W - set White color
			colorcode = 8;
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		}
	}
	break;


	case WM_DESTROY:
		PostQuitMessage(0);
		break;


	case WM_PAINT:
	{
		HDC hdc;
		PAINTSTRUCT ps;
		RECT rc;
		HBRUSH hbrush;

		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rc);
		hbrush = CreateSolidBrush(colors[colorcode - 1]);
		FillRect(hdc, &rc, hbrush);
		DeleteObject(hbrush);
		EndPaint(hwnd, &ps);
	}
	break;

	}

	return (DefWindowProc(hwnd, iMsg, wparam, lparam));
}


