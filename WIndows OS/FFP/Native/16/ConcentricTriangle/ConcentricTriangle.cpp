#include <Windows.h>
#include <gl/GL.h>

#define WIN_WIDTH  800
#define WIN_HEIGHT 600

#pragma comment(lib,"opengl32.lib")

#define _USE_MATH_DEFINES
#include "math.h"

float ComputeVectorLength(float x, float y, float z)
{
	return sqrt((x*x) + (y*y) + (z*z));
}

void ComputeNormalizedVector(float inX, float inY, float inZ, float *outX, float *outY, float *outZ)
{
	float length = sqrt((inX*inX) + (inY*inY) + (inZ*inZ));

	*outX = inX / length;
	*outY = inY / length;
	*outZ = inZ / length;
}

void ProjectPointInDirection(float pointX, float pointY, float pointZ,
	float directionX, float directionY, float directionZ,
	float *outPointX, float *outPointY, float *outPointZ, float distance)
{
	*outPointX = pointX + (distance * directionX);
	*outPointY = pointY + (distance * directionY);
	*outPointZ = pointZ + (distance * directionZ);
}

void DrawConcentricTriangle(float point1X, float point1Y, float point1Z,
	float point2X, float point2Y, float point2Z,
	float point3X, float point3Y, float point3Z,
    int count, float gap)
{
	float centroidX = (point1X + point2X + point3X)/3.0f;
	float centroidY = (point1Y + point2Y + point3Y)/3.0f;
	float centroidZ = (point1Z + point2Z + point3Z)/3.0f;

	float direction1X, direction1Y, direction1Z;
	float direction2X, direction2Y, direction2Z;
	float direction3X, direction3Y, direction3Z;

	ComputeNormalizedVector(point1X - centroidX, point1Y - centroidY, point1Z - centroidZ, &direction1X, &direction1Y, &direction1Z);
	ComputeNormalizedVector(point2X - centroidX, point2Y - centroidY, point2Z - centroidZ, &direction2X, &direction2Y, &direction2Z);
	ComputeNormalizedVector(point3X - centroidX, point3Y - centroidY, point3Z - centroidZ, &direction3X, &direction3Y, &direction3Z);

	float distance1 = ComputeVectorLength(point1X - centroidX, point1Y - centroidY, point1Z - centroidZ);
	float distance2 = ComputeVectorLength(point2X - centroidX, point2Y - centroidY, point2Z - centroidZ);
	float distance3 = ComputeVectorLength(point3X - centroidX, point3Y - centroidY, point3Z - centroidZ);

	float projectPoint1X, projectPoint1Y, projectPoint1Z;
	float projectPoint2X, projectPoint2Y, projectPoint2Z;
	float projectPoint3X, projectPoint3Y, projectPoint3Z;

	glPointSize(3.0f);
	glBegin(GL_POINTS);
	{
		glVertex3f(centroidX, centroidY, centroidZ);
	}glEnd();

	GLfloat colors[10][3] = {
		{ 1.0f,0.0f,0.0f },
		{ 0.0f,1.0f,0.0f },
		{ 0.0f,0.0f,1.0f },
		{ 1.0f,0.0f,1.0f },
		{ 1.0f,1.0f,0.0f },
		{ 0.0f,1.0f,1.0f },
		{ 0.5f,0.5f,0.5f },
		{ 1.0f,165.0f / 255.0f,0.0f },
		{ 1.0f,192.0f / 255.0f, 203.0f / 255.0f },
		{ 1.0f,1.0f,1.0f }
	};

	for (int i = 0; i < count; i++)
	{
		glColor3f(colors[i][0], colors[i][1], colors[i][2]);
		ProjectPointInDirection(centroidX, centroidY, centroidZ, direction1X, direction1Y, direction1Z, &projectPoint1X, &projectPoint1Y, &projectPoint1Z, distance1 + (gap*i));
		ProjectPointInDirection(centroidX, centroidY, centroidZ, direction2X, direction2Y, direction2Z, &projectPoint2X, &projectPoint2Y, &projectPoint2Z, distance2 + (gap*i));
		ProjectPointInDirection(centroidX, centroidY, centroidZ, direction3X, direction3Y, direction3Z, &projectPoint3X, &projectPoint3Y, &projectPoint3Z, distance3 + (gap*i));

		glBegin(GL_LINES);
		{
			glVertex3f(projectPoint1X, projectPoint1Y, projectPoint1Z);
			glVertex3f(projectPoint2X, projectPoint2Y, projectPoint2Z);

			glVertex3f(projectPoint2X, projectPoint2Y, projectPoint2Z);
			glVertex3f(projectPoint3X, projectPoint3Y, projectPoint3Z);

			glVertex3f(projectPoint3X, projectPoint3Y, projectPoint3Z);
			glVertex3f(projectPoint1X, projectPoint1Y, projectPoint1Z);
		}glEnd();
	}
}

//Prototype Of WndProc() declared Globally
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//Global variable decleration
HWND ghwnd = NULL;
HDC ghdc = NULL;
HGLRC ghrc = NULL;

DWORD dwStyle;
WINDOWPLACEMENT wpPrev = { sizeof(WINDOWPLACEMENT) };

bool gbActiveWindow = false;
bool gbEscapeKeyIsPressed = false;
bool gbFullScreen = false;

//Main()

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	//Function Prototype
	void initialize(void);
	void uninitialize(void);
	void display(void);

	//Variable decleration

	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;

	TCHAR szClassName[] = TEXT("RTROGL");
	bool bDone = false;

	//Code
	//Initilizing members of struct WNDCLASSEX
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = szClassName;
	wndclass.lpszMenuName = NULL;

	//Register Class
	RegisterClassEx(&wndclass);

	//Create Window
	hwnd = CreateWindowEx(WS_EX_APPWINDOW,
		szClassName,
		TEXT("OpenGL Fixed Function Pipeline using Native Windowing : First Window"),
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE,
		0,
		0,
		WIN_WIDTH,
		WIN_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL);

	ghwnd = hwnd;

	//initialize
	initialize();

	ShowWindow(hwnd, SW_SHOW);
	SetForegroundWindow(hwnd);
	SetFocus(hwnd);

	//Message Loop
	while (bDone == false)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				bDone = true;
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			if (gbActiveWindow == true)
			{
				if (gbEscapeKeyIsPressed == true)
					bDone = true;
				display();
			}
		}
	}

	uninitialize();

	return ((int)msg.wParam);
}

//Wnd Proc()

LRESULT CALLBACK WndProc(HWND hwnd, UINT imsg, WPARAM wParam, LPARAM lparam)
{
	//Function prototype
	void display(void);
	void resize(int, int);
	void ToggleFullScreen(void);
	void uninitialize(void);

	//code 
	switch (imsg)
	{
	case WM_ACTIVATE:
		if (HIWORD(wParam) == 0)
			gbActiveWindow = true;
		else
			gbActiveWindow = false;
		break;

		/*case WM_PAINT:
		display();
		break;
		return(0);*/

		/*case WM_ERASEBKGND:
		return(0);*/

	case WM_SIZE:
		resize(LOWORD(lparam), HIWORD(lparam));
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			gbEscapeKeyIsPressed = true;
			break;

		case 0x46: // F
			if (gbFullScreen == false)
			{
				ToggleFullScreen();
				gbFullScreen = true;
			}
			else
			{
				ToggleFullScreen();
				gbFullScreen = false;
			}
			break;
		default:
			break;
		}
		break;

	case WM_LBUTTONDOWN:
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		break;
	}
	return(DefWindowProc(hwnd, imsg, wParam, lparam));
}
void ToggleFullScreen(void)
{
	//Variable Declerations
	MONITORINFO mi;

	//code
	if (gbFullScreen == false)
	{
		dwStyle = GetWindowLong(ghwnd, GWL_STYLE);
		if (dwStyle & WS_OVERLAPPEDWINDOW)
		{
			mi = { sizeof(MONITORINFO) };

			if (GetWindowPlacement(ghwnd, &wpPrev) && GetMonitorInfo(MonitorFromWindow(ghwnd, MONITORINFOF_PRIMARY), &mi))
			{
				SetWindowLong(ghwnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
				SetWindowPos(ghwnd, HWND_TOP, mi.rcMonitor.left, mi.rcMonitor.top, mi.rcMonitor.right - mi.rcMonitor.left, mi.rcMonitor.bottom - mi.rcMonitor.top, SWP_NOZORDER | SWP_FRAMECHANGED);
			}
		}
		ShowCursor(false);
	}
	else
	{
		//code 
		SetWindowLong(ghwnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPlacement(ghwnd, &wpPrev);
		SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);

		ShowCursor(TRUE);
	}
}

void initialize(void)
{
	//function prototypes
	void resize(int, int);

	//variable decleration
	PIXELFORMATDESCRIPTOR pfd;

	int ipixelFormatIndex;

	//code
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	//Initialize
	pfd.nSize = sizeof(PPIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cRedBits = 8;
	pfd.cBlueBits = 8;
	pfd.cGreenBits = 8;
	pfd.cAlphaBits = 8;

	ghdc = GetDC(ghwnd);

	ipixelFormatIndex = ChoosePixelFormat(ghdc, &pfd);

	if (ipixelFormatIndex == 0)
	{
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
	}

	if (SetPixelFormat(ghdc, ipixelFormatIndex, &pfd) == FALSE)
	{
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
	}

	ghrc = wglCreateContext(ghdc);
	if (ghrc == NULL)
	{
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
	}

	if (wglMakeCurrent(ghdc, ghrc) == FALSE)
	{
		wglDeleteContext(ghrc);
		ghrc = NULL;
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
	}

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	//resize(WIN_WIDTH, WIN_HEIGHT);
}

void display(void)
{
	//code 
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Rendering Command
	DrawConcentricTriangle(0.0f,0.5f, 0.0f, -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 10, 0.05f);

	//glFlush();
	SwapBuffers(ghdc);
}

void resize(int width, int height)
{
	//code 
	if (height == 0)
		height = 1;

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
}

void uninitialize()
{
	//uninitialize code

	if (gbFullScreen == true)
	{
		dwStyle = GetWindowLong(ghwnd, GWL_STYLE);
		SetWindowLong(ghwnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPlacement(ghwnd, &wpPrev);
		SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0,
			SWP_NOMOVE |
			SWP_NOOWNERZORDER |
			SWP_NOZORDER |
			SWP_NOSIZE
			| SWP_FRAMECHANGED);

		ShowCursor(true);
	}

	wglMakeCurrent(NULL, NULL);

	wglDeleteContext(ghrc);

	ghrc = NULL;

	ReleaseDC(ghwnd, ghdc);
	ghdc = NULL;
}