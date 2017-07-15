#include <GL/freeglut.h>
#define _USE_MATH_DEFINES

#include "math.h"

//global variable declaration
bool bFullscreen = false; //variable to toggle for fullscreen

						  //Using my old function here
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

void DrawConcentricCircleWithColors(GLfloat centerX, GLfloat centerY, GLfloat centerZ, GLfloat radius, GLint count, GLfloat gap)
{
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
	glLineWidth(2.0f);
	for (int i = 0; i < count; i++)
	{
		glColor3f(colors[i][0], colors[i][1], colors[i][2]);
		DrawWiredCircleByLine(centerX, centerY, centerZ, (radius + (i*gap)));
	}
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

	glutInitWindowSize(800, 800); //to declare initial window size
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
	DrawConcentricCircleWithColors(0.0f, 0.0f, 0.0f, 0.5f, 10, 0.05f);


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

