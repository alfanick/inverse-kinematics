#ifndef DETAILED_CUBE_H
#define DETAILED_CUBE_H

#include <GLUT/glut.h>

//Zadeklaruj globalnie
extern float *geomVertices;
extern float *geomTexCoords;
extern float *geomNormals;
extern int geomVertexCount;

void initCube();
void freeCube();
void drawCube();


#endif
