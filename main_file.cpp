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
float angle_x = -30;
float angle_y = 0;
float zoom = 1.0f;

GLfloat mat_podstawa[] = { 60.0/255.0, 14.0/255.0, 14.0/255.0, 1.0 };
GLfloat mat_ramie[] = {248.0/255.0, 233.0/255.0, 202.0/255.0, 1.0};
GLfloat mat_staw[] = {222.0/255.0, 197.0/255.0, 62.0/255.0, 1.0};
GLfloat mat_dlon[] = {221.0/255.0,74.0/255.0,54.0/255.0, 1.0};

Bone* root;
float r_up = 60.0f;

void drawBones(Bone* b) {
	glPushMatrix();

	glm::mat4 previous = b->M;

	if (b->parent != NULL) {

    b->M = glm::translate(b->M, glm::vec3(0.0f, 0.0f, b->parent->length));

    b->M = glm::rotate(b->M, b->rotation.x, glm::vec3(b->M*glm::vec4(1.0f, 0.0f, 0.0f, 0.0f)));
    b->M = glm::rotate(b->M, b->rotation.y, glm::vec3(b->M*glm::vec4(0.0f, 1.0f, 0.0f, 0.0f)));
    b->M = glm::rotate(b->M, b->rotation.z, glm::vec3(b->M*glm::vec4(0.0f, 0.0f, 1.0f, 0.0f)));

    b->M = b->parent->M * b->M;
  }

  glLoadMatrixf(glm::value_ptr(b->M));

  if (b->parent != NULL) {
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_staw);
    glutSolidSphere(0.2f, 32,32);
  }

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_ramie);
	GLUquadricObj* q = gluNewQuadric();

  if (b->bones.empty())
    gluCylinder(q, 0.1f, 0.1, b->length - 0.5f, 32, 32);
  else
	  gluCylinder(q, 0.1f, 0.1f, b->length, 32, 32);

	gluDeleteQuadric(q);

  glPopMatrix();


  if (b->bones.empty()) {
    glPushMatrix();

    glLoadMatrixf(glm::value_ptr(glm::translate(b->M, glm::vec3(0.0f, 0.0f, b->length-0.5f))));
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_dlon);
    gluCylinder(q, 0.2f, 0.0f, 0.5f, 32,32);

    glPopMatrix();
  }

	for (std::vector<Bone*>::iterator it = b->bones.begin(); it != b->bones.end(); it++) {
		drawBones(*it);
	}

	b->M=previous;
}

void displayFrame(void) {
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glm::vec3 cameraCenter = glm::vec3(0.0f, 2.0f, 0.0f);
  glm::vec3 cameraEye = glm::vec3(0.0f, 0.0f, -10.0f);
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



	glPushMatrix();
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_podstawa);
	glScalef(3.0f,0.2f,2.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

  root->M = glm::rotate(M*V, -90.0f, glm::vec3(1.0f, 0.0f, 0.0f));

	drawBones(root);
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
      zoom *= 1.05f;
      break;
    case '=':
    case '+':
      zoom /= 1.05f;
      break;

    case 'u':
      root->bones[0]->bones[0]->bones[0]->rotate(-1.0f, 0.0f, 0.0f);
      break;
    case 'j':
      root->bones[0]->bones[0]->bones[0]->rotate(+1.0f, 0.0f, 0.0f);
      break;
    case 'i':
      root->bones[0]->bones[0]->bones[0]->rotate(0.0f, -1.0f, 0.0f);
      break;
    case 'k':
      root->bones[0]->bones[0]->bones[0]->rotate(0.0f, +1.0f, 0.0f);
      break;
     case 'o':
      root->bones[0]->bones[0]->bones[0]->rotate(0.0f, 0.0f, -1.0f);
      break;
    case 'l':
      root->bones[0]->bones[0]->bones[0]->rotate(0.0f, 0.0f, +1.0f);
      break;


    case 'r':
      root->bones[0]->bones[0]->rotate(-1.0f, 0.0f, 0.0f);
      break;
    case 'f':
      root->bones[0]->bones[0]->rotate(+1.0f, 0.0f, 0.0f);
      break;
    case 't':
      root->bones[0]->bones[0]->rotate(0.0f, -1.0f, 0.0f);
      break;
    case 'g':
      root->bones[0]->bones[0]->rotate(0.0f, +1.0f, 0.0f);
      break;
     case 'y':
      root->bones[0]->bones[0]->rotate(0.0f, 0.0f, -1.0f);
      break;
    case 'h':
      root->bones[0]->bones[0]->rotate(0.0f, 0.0f, +1.0f);
      break;

    case 'q':
      root->bones[0]->rotate(-1.0f, 0.0f, 0.0f);
      break;
    case 'a':
      root->bones[0]->rotate(+1.0f, 0.0f, 0.0f);
      break;
    case 'w':
      root->bones[0]->rotate(0.0f, -1.0f, 0.0f);
      break;
    case 's':
      root->bones[0]->rotate(0.0f, +1.0f, 0.0f);
      break;
     case 'e':
      root->bones[0]->rotate(0.0f, 0.0f, -1.0f);
      break;
    case 'd':
      root->bones[0]->rotate(0.0f, 0.0f, +1.0f);
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

  glShadeModel (GL_SMOOTH);

  GLfloat light_ambient[] = {0.1, 0.1, 0.1, 1.0};
  GLfloat light_position[] = { 0.0, 0.0, 0.0, 1.0 };
  GLfloat light_diffuse[] = { 0.3, 0.3, 0.3, 1.0 };
  GLfloat light_specular[] = { 0.3, 0.3, 0.3, 1.0 };


  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);


	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);


	root = new Bone(0.0f);
  root->rotate(90,0,0);

  root->add(new Bone(3.5))->constraints(-90,90, -90,90, -360,360)->rotate(0, 0, 0)
      ->add(new Bone(4))->rotate(0, -75, 0)
      ->add(new Bone(1))->rotate(0, -45, 0);


        glutMainLoop();
        return 0;
}
