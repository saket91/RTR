#include "windows.h"
#include "Windowsx.h"
#include "stdio.h"

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

	case WM_CREATE:
		MessageBox(hwnd, TEXT("WM_CREATE recieved"), TEXT("Message Type : WM_Create"), MB_OK| MB_ICONINFORMATION);
		break;

	case WM_LBUTTONDOWN:
	   {
		TCHAR message[MAX_PATH];
		int xPos = GET_X_LPARAM(lparam);
		int yPos = GET_Y_LPARAM(lparam);
		swprintf_s(message, MAX_PATH, TEXT("WM_LBUTTON recieved at x=%d, y=%d"), xPos, yPos);
		MessageBox(hwnd, message, TEXT("Message Type : LButton Down"), MB_OK | MB_ICONINFORMATION);
	   }
	   break;

	case WM_KEYDOWN:
	    {
		  TCHAR messagesg[MAX_PATH];
		  switch (wparam)
		  {
		  case 0x42:
			  wcscpy_s(messagesg, MAX_PATH, TEXT("B key is down"));
			  MessageBox(hwnd, messagesg, TEXT("Message Type : Key Down"), MB_OK | MB_ICONINFORMATION);
			  break;
		  case 0x46:
			  wcscpy_s(messagesg, MAX_PATH, TEXT("F key is down"));
			  MessageBox(hwnd, messagesg, TEXT("Message Type : Key Down"), MB_OK | MB_ICONINFORMATION);
			  break;
		  case 0x4C:
			  wcscpy_s(messagesg, MAX_PATH, TEXT("L key is down"));
			  MessageBox(hwnd, messagesg, TEXT("Message Type : Key Down"), MB_OK | MB_ICONINFORMATION);
			  break;
		  case 0x54:
			  wcscpy_s(messagesg, MAX_PATH, TEXT("T key is down"));
			  MessageBox(hwnd, messagesg, TEXT("Message Type : Key Down"), MB_OK | MB_ICONINFORMATION);
			  break;
		  case 0x51:
			  wcscpy_s(messagesg, MAX_PATH, TEXT("Q key is down"));
			  MessageBox(hwnd, messagesg, TEXT("Message Type : Key Down"), MB_OK | MB_ICONINFORMATION);
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