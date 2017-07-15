#include <GL/freeglut.h>

#define _USE_MATH_DEFINES
#include "math.h"

//global variable declaration
bool bFullscreen = false; //variable to toggle for fullscreen

void DrawWiredCircleByLine(GLfloat centerX, GLfloat centerY, GLfloat centerZ, GLfloat radius)
{
	glBegin(GL_LINE_LOOP);
	{
		for (float angle = 0; angle < 2 * M_PI; angle = angle + 0.01f)
		{
			glVertex3f(centerX + radius*sin(angle), centerY + radius*cos(angle), 0.0f);
		}

	}glEnd();
}

void DrawWiredTriangle(GLfloat point1X, GLfloat point1Y, GLfloat point1Z,
	GLfloat point2X, GLfloat point2Y, GLfloat point2Z,
	GLfloat point3X, GLfloat point3Y, GLfloat point3Z)
{
	glBegin(GL_LINES);
	{
		glVertex3f(point1X, point1Y, point1Z);
		glVertex3f(point2X, point2Y, point2Z);
		glVertex3f(point2X, point2Y, point2Z);
		glVertex3f(point3X, point3Y, point3Z);
		glVertex3f(point3X, point3Y, point3Z);
		glVertex3f(point1X, point1Y, point1Z);
	}glEnd();
}

void DrawSymbol(float point1X, float point1Y, float point1Z,
	float point2X, float point2Y, float point2Z,
	float point3X, float point3Y, float point3Z)
{

	DrawWiredTriangle(point1X, point1Y, point1Z,
		point2X, point2Y, point2Z,
		point3X, point3Y, point3Z);

	float centroidX = (point1X + point2X + point3X) / 3.0f;
	float centroidY = (point1Y + point2Y + point3Y) / 3.0f;
	float centroidZ = (point1Z + point2Z + point3Z) / 3.0f;

	float a = (point1Y - point2Y);
	float b = (point2X - point1X);
	float c = (point1X*point2Y) - (point2X*point1Y);

	float rad = fabs(a*centroidX + b*centroidY + c) / (sqrt(a*a + b*b));

	DrawWiredCircleByLine(centroidX, centroidY, centroidZ, rad);

	float midpointX = (point2X + point3X) / 2;
	float midpointY = (point2Y + point3Y) / 2;
	float midpointZ = (point2Z + point3Z) / 2;

	glBegin(GL_LINES);
	{
		glVertex3f(point1X, point1Y, point1Z);
		glVertex3f(midpointX, midpointY, midpointZ);
	}glEnd();

}

int main(int argc, char** argv)
{
	//function prototypes
	void display(void);
	void resize(int, int);
	void keyboard(unsigned char, int, int);
	void mouse(int, int, int, int);
	void initialize(void);
	void uninitialize(void);

	//code
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowSize(800, 600); //to declare initial window size
	glutInitWindowPosition(100, 100); //to declare initial window position
	glutCreateWindow("GLUT based Window!!!"); //open the window with "OpenGL First Window : Hello World" in the title bar

	initialize();

	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutCloseFunc(uninitialize);

	glutMainLoop();

	//	return(0); 
}

void display(void)
{

	//code

	//to clear all pixels
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Rendering Command
	DrawSymbol(0.0f, 0.5f, 0.0f, -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f);

	//to process buffered OpenGL Routines
	glFlush();
}

void initialize(void)
{
	//code
	//to select clearing (background) clear
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //blue 
}

void keyboard(unsigned char key, int x, int y)
{
	//code
	switch (key)
	{
	case 27: // Escape
		glutLeaveMainLoop();
		break;
	case 'F':
	case 'f':
		if (bFullscreen == false)
		{
			glutFullScreen();
			bFullscreen = true;
		}
		else
		{
			glutLeaveFullScreen();
			bFullscreen = false;
		}
		break;
	default:
		break;
	}
}

void mouse(int button, int state, int x, int y)
{
	//code
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		break;
	default:
		break;
	}
}

void resize(int width, int height)
{
	// code
	if (height == 0)
		height = 1;

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

}

void uninitialize(void)
{
	// code
}

