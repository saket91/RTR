#include "windows.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpstr, int CmdShow)
{
	WNDCLASSEX wndclass;
	
	TCHAR szAppName[] = TEXT("MyApp");

	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.style = CS_VREDRAW | CS_HREDRAW;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = WndProc;


	//Register the wndclass
	RegisterClassEx(&wndclass);
	
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenheight = GetSystemMetrics(SM_CYSCREEN);

	int x = (screenWidth/2) - (800 / 2); //800 window width
	int y = (screenheight/2) - (600 / 2); //600 window height

	HWND hwnd =CreateWindow(
		szAppName, 
		TEXT("Saket K:Centered Window"),
		WS_OVERLAPPEDWINDOW,
		x,y,800,600,
		NULL,NULL,hInstance,NULL);
	
	HMONITOR monitor = MonitorFromWindow(hwnd, MONITORINFOF_PRIMARY);
	
	ShowWindow(hwnd, CmdShow);
	UpdateWindow(hwnd);

	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0)) //always return true except when msg is WM_QUIT
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return ((int)(msg.wParam));
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM lparam, LPARAM wparam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		break;
	}
	return (DefWindowProc(hwnd, msg, lparam, wparam));
}