#ifdef KOT
  #include <GL/glut.h>
#else
  #include <GLUT/glut.h>
#endif

#include <stdio.h> //Przydatne do wypisywania komunikatów na konsoli
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "tga.h"
#include "cube.h"

#include "bone.h"

float speed_x=0; //60 stopni/s
float speed_y=0; //60 stopni/s
int lastTime=0;
float angle_x;
float angle_y;
float zoom = 1.0f;


void displayFrame(void) {
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glm::vec3 cameraCenter = glm::vec3(0.0f, 0.0f, 0.0f);
  glm::vec3 cameraEye = glm::vec3(0.0f, 0.0f, -5.0f);
  glm::vec3 cameraNose = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 V=glm::lookAt(cameraEye, cameraCenter, cameraNose);
  V = glm::rotate(V, angle_y, glm::vec3(0.0f, 1.0f, 0.0f));
  V = glm::rotate(V, angle_x, glm::vec3(1.0f, 0.0f, 0.0f));

	glm::mat4 P=glm::perspective(50.0f*zoom, 1.0f, 1.0f, 50.0f);

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(P));
	glMatrixMode(GL_MODELVIEW);


	glm::mat4 M=glm::mat4(1.0f);
	glLoadMatrixf(glm::value_ptr(V*M));
/*
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,cubeVertices);
	glColorPointer(3,GL_FLOAT,0,cubeColors);
	glDrawArrays(GL_QUADS,0,cubeVertexCount);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
*/

	glScalef(3.0f,0.2f,2.0f);
	glutSolidCube(1.0f);
/*
	GLUquadricObj *quadratic;

	quadratic = gluNewQuadric();

	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	gluCylinder(quadratic,0.1f,0.1f,3.0f,32,32);

	gluDeleteQuadrac(quadratic);
*/


	glutSwapBuffers();
}


void nextFrame(void) {
	int actTime=glutGet(GLUT_ELAPSED_TIME);
	int interval=actTime-lastTime;
	lastTime=actTime;
	angle_x+=speed_x*interval/1000.0;
	angle_y+=speed_y*interval/1000.0;
	if (angle_x>360) angle_x-=360;
	if (angle_x>360) angle_x+=360;
	if (angle_y>360) angle_y-=360;
	if (angle_y>360) angle_y+=360;

	glutPostRedisplay();
}

void specKeyDown(int c, int x, int y) {
  switch (c) {
    case GLUT_KEY_LEFT:
      speed_y=60;
      break;
    case GLUT_KEY_RIGHT:
      speed_y=-60;
      break;
    case GLUT_KEY_UP:
      speed_x=60;
      break;
    case GLUT_KEY_DOWN:
      speed_x=-60;
      break;
  }
}

void specKeyUp(int c, int x, int y) {
  switch (c) {
    case GLUT_KEY_LEFT:
      speed_y=0;
      break;
    case GLUT_KEY_RIGHT:
      speed_y=-0;
      break;
    case GLUT_KEY_UP:
      speed_x=0;
      break;
    case GLUT_KEY_DOWN:
      speed_x=-0;
      break;
  }
}

void keyDown(unsigned char c, int x, int y) {
  switch(c) {
    case '-':
      zoom += 0.01f;
      break;
    case '+':
      zoom -= 0.01f;
      break;
  }
}


int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800,800);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Program OpenGL");
	glutDisplayFunc(displayFrame);
	glutIdleFunc(nextFrame);

	//Tutaj kod inicjujacy
	//glewInit();
	glutSpecialFunc(specKeyDown);
	glutSpecialUpFunc(specKeyUp);
  glutKeyboardFunc(keyDown);

	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

        glutMainLoop();
        return 0;
}
