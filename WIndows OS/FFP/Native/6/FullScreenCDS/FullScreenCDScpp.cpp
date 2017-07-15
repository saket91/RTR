#include "windows.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

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
		50, 50, 500, 500, NULL, NULL, hInstance, NULL);

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

bool gbIsFullScreen = false;
DEVMODE dm;


LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wparam, LPARAM lparam)
{
	switch (iMsg)
	{
	case WM_KEYDOWN:
	{
		if (wparam == 0x46)
		{
			if (gbIsFullScreen==false)
			{
				dm.dmSize = sizeof(DEVMODE);
				dm.dmDisplayFlags = DM_DISPLAYFLAGS;

				DEVMODE dm1 = { sizeof(DEVMODE) };
				EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dm1);
				
				dm.dmPelsWidth = dm1.dmPelsWidth;
				dm.dmPelsHeight = dm1.dmPelsHeight;
				dm.dmBitsPerPel = dm1.dmBitsPerPel;
				dm.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;

				LONG retval = ChangeDisplaySettings(NULL, CDS_FULLSCREEN);

			}
			else
			{
				ChangeDisplaySettings(NULL, 0);
				ShowCursor(TRUE);
			}
		}
	}
	break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hwnd, iMsg, wparam, lparam));
}