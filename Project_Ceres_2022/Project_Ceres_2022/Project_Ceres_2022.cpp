#include <math.h>
#include "GL/glut.h"   
#include <stdio.h>
#include <string.h>
#include "visuals.h"  
int main(int argc, char* argv[])
{
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(50, 50);
	
	glutCreateWindow("Project Ceres 2022");
		
	Setup();
		
	glutDisplayFunc(Render);
	glutReshapeFunc(Resize);
	glutIdleFunc(Idle);
	glutKeyboardFunc(Keyboard);
		
	glutMainLoop();
	return 0;
}
