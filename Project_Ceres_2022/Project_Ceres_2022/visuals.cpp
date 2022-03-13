#include <stdio.h>     
#include <string.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include "GL/glut.h"  
#include "visuals.h"   

bool one = false;

float speedEarth = 0.4;
float speedMoon = 0.4;

static float rotEarthX = 0.0;
static float rotMoonX = 0.0;


static float tx = 0.0;
static float worldX = 15.0;
static float worldY = 0.0;
static float scaleFactor = 0.6;
static bool animate = true;
static float first = 1;
static float second = 1;
point stars[500];

int globalWidth, globalHeight;

using namespace std;

void keimeno(const char *str, float size)
{

	glPushMatrix();
	glScalef(size, size, size);

	for (int i = 0; i<strlen(str); i++)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
	glPopMatrix();

}

void Render()
{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
														 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0, 0, -100);
	
	if (!animate) {
		glPushMatrix();
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
		glColor3f(1, 1, 1);
		glTranslatef(-8, 50, 0.0);
		keimeno("Pause", 0.05f);
		glPopMatrix();
	}
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLUquadricObj *quadric;
	quadric = gluNewQuadric();
	gluQuadricDrawStyle(quadric, GLU_FILL);
	gluDeleteQuadric(quadric);

	glScalef(scaleFactor, scaleFactor, scaleFactor);

	glRotatef(worldX, 1, 0, 0);
	glRotatef(worldY, 0, 1, 0);

	glDisable(GL_LIGHTING);
 
	glPushMatrix();
	glColor3f(0.8, 0.498039, 0.196078);
	gluSphere(quadric, 15, 36, 18); 
	glColor3f(1, 1, 0); 
	glEnable(GL_BLEND);
	glBlendFunc(first, second);
	gluSphere(quadric, 20, 36, 18);
	glDisable(GL_BLEND);
	glPopMatrix();

	glEnable(GL_LIGHTING);
	GLfloat light_position[] = { 0.0, 0.0, 0.0, 1.0 }; //Set point-light position (center of sun)
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	GLfloat light_diff[] = { 2.0, 2.0, 2.0, 2.0 }; //Set pont-light strength
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diff);
	GLfloat light_amb[] = { 1.0, 1.0, 1.0, 1.0 }; //Set global illumination
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_amb);

	
	glPushMatrix(); // Planet earth setup
	glRotatef(rotEarthX, 0, 1, 0);
	glTranslatef(60, 0, -10.0);
	glRotatef(rotEarthX, 1, 0, 0);
	glColor3f(0.3, 0.3, 1);                            
	gluSphere(quadric, 5, 36, 18);
	glPopMatrix();
		

	glPushMatrix();// Moon setup
	glTranslatef(70, 0, -10.0);
	glRotated((GLdouble)360 * 2, 0, 1, 0.0);
	glRotatef(rotMoonX, 1, 0, 0);
	glColor3f(0, 1, 0);                            
	gluSphere(quadric, 1, 36, 18);
	glPopMatrix();

	DrawStars();

	glutSwapBuffers();            
}



void Resize(int w, int h)
{
	// define the visible area of the window ( in pixels )
	if (h == 0) h = 1;
	glViewport(0, 0, w, h);
	globalHeight = h;
	globalWidth = w;

	// Setup viewing volume
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0, (float)w / (float)h, 1.0, 1000.0);
}

void Idle()
{
	if (animate)
		rotEarthX += speedEarth; //Set speed of earth
		rotMoonX += speedMoon; //Set speed of moon

	glutPostRedisplay();
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'q': exit(0);
		break;
	case 'w': if (animate) worldX -= 1.0f;
		break;
	case 's': if (animate) worldX += 1.0f;
		break;
	case 'a': if (animate) worldY -= 1.0f;
		break;
	case 'd': if (animate)  worldY += 1.0f;
		break;
	case ' ': animate = !animate;;
		break;
	default: break;
	}
	glutPostRedisplay();

}


void Setup()  // TOUCH IT !! 
{

	//get random cordinates for the stars
	for (int i = 0; i < 500; i++)
		RandomCoordinates(&stars[i]);
	srand(time(0));
	//Parameter handling
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);

	// polygon rendering mode
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// Black background
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}



void RandomCoordinates(point *star)
{

	int lowest = -1000, highest = 1000;
	int range = (highest - lowest) + 1;
	star->x = lowest + int(range*rand() / (RAND_MAX + 1.0));
	star->y = lowest + int(range*rand() / (RAND_MAX + 1.0));
	star->z = lowest + int(range*rand() / (RAND_MAX + 1.0));
	
}

void DrawStars()
{
	GLUquadricObj *quadric;
	quadric = gluNewQuadric();
	gluQuadricDrawStyle(quadric, GLU_FILL);
	gluDeleteQuadric(quadric);
	for ( int i = 0; i < 500; i ++ ) {
		glPushMatrix();
		glTranslatef(stars[i].x, stars[i].y, stars[i].z);
		glColor3f(1, 1, 1);
		gluSphere(quadric, 1, 36, 18);
		glPopMatrix();
	}
}
