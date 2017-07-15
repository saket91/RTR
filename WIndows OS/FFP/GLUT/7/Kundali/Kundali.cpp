#include <GL/freeglut.h>

//global variable declaration
bool bFullscreen = false; //variable to toggle for fullscreen

						  //Reusing my old function
void DrawWiredRectangle(GLfloat point1X, GLfloat point1Y, GLfloat point1Z,
	GLfloat point2X, GLfloat point2Y, GLfloat point2Z,
	GLfloat point3X, GLfloat point3Y, GLfloat point3Z,
	GLfloat point4X, GLfloat point4Y, GLfloat point4Z)
{

	glBegin(GL_LINES);
	{
		glVertex3f(point1X, point1Y, point1Z);
		glVertex3f(point2X, point2Y, point2Z);
		glVertex3f(point2X, point2Y, point2Z);
		glVertex3f(point3X, point3Y, point3Z);
		glVertex3f(point3X, point3Y, point3Z);
		glVertex3f(point4X, point4Y, point4Z);
		glVertex3f(point4X, point4Y, point4Z);
		glVertex3f(point1X, point1Y, point1Z);
	}glEnd();

}

void DrawLine(GLfloat point1X, GLfloat point1Y, GLfloat point1Z,
	GLfloat point2X, GLfloat point2Y, GLfloat point2Z)
{
	glBegin(GL_LINES);
	{
		glVertex3f(point1X, point1Y, point1Z);
		glVertex3f(point2X, point2Y, point2Z);
	}glEnd();

}

void DrawKundali()
{
	DrawWiredRectangle(-0.8f, 0.8f, 0.0f,
		0.8f, 0.8f, 0.0f,
		-0.8f, -0.8f, 0.0f,
		0.8f, -0.8f, 0.0f);


	DrawWiredRectangle(-0.8f, 0.8f, 0.0f,
		0.8f, 0.8f, 0.0f,
		0.8f, -0.8f, 0.0f,
		-0.8f, -0.8f, 0.0f);

	DrawWiredRectangle(0.0f, 0.8f, 0.0f,
		0.8f, 0.0f, 0.0f,
		0.0f, -0.8f, 0.0f,
		-0.8f, 0.0f, 0.0f);

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
	DrawKundali();

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

