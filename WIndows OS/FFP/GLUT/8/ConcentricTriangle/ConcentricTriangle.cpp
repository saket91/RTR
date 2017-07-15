#include <GL/freeglut.h>
#include "math.h"
//global variable declaration
bool bFullscreen = false; //variable to toggle for fullscreen

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
	float centroidX = (point1X + point2X + point3X) / 3.0f;
	float centroidY = (point1Y + point2Y + point3Y) / 3.0f;
	float centroidZ = (point1Z + point2Z + point3Z) / 3.0f;

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
	DrawConcentricTriangle(0.0f, 0.5f, 0.0f, -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 10, 0.05f);



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

