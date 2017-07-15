#include <GL/freeglut.h>
#define _USE_MATH_DEFINES
#include "math.h"

//global variable declaration
bool bFullscreen = false; //variable to toggle for fullscreen

						  //Functions 
void DrawWiredCircleByPoint(GLfloat centerX, GLfloat centerY, GLfloat centerZ, GLfloat radius)
{
	glBegin(GL_POINTS);
	{
		for (float angle = 0; angle < 2 * M_PI; angle = angle + 0.000001f)
		{
			glVertex3f(centerX + radius*sin(angle), centerY + radius*cos(angle), 0.0f);
		}

	}glEnd();
}

void DrawWiredCircleBYLine(GLfloat centerX, GLfloat centerY, GLfloat centerZ, GLfloat radius)
{
	glBegin(GL_LINE_LOOP);
	{
		for (float angle = 0; angle < 2 * M_PI; angle = angle + 0.000001f)
		{
			glVertex3f(centerX + radius*sin(angle), centerY + radius*cos(angle), 0.0f);
		}

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

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

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
	//Rendering Command
	//DrawWiredCircleBYLine(0.30f, 0.30f, 0.0f, 0.30f);
	DrawWiredCircleByPoint(0.0f, 0.0f, 0.0f, 1.0f);

	//to process buffered OpenGL Routines
	glutSwapBuffers();
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

