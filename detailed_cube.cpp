#include "detailed_cube.h"

float *geomVertices;
float *geomTexCoords;
float *geomNormals;
int geomVertexCount;

void quad(int subdiv,int i1, int i2, float x, float y, float back, float nx, 
	float ny, float s,float t,int pos){
		geomVertices[i1*subdiv*3*4+i2*3*4+0+pos*3]=x;
		geomVertices[i1*subdiv*3*4+i2*3*4+1+pos*3]=y;
		geomVertices[i1*subdiv*3*4+i2*3*4+2+pos*3]=-back;
		geomNormals[i1*subdiv*3*4+i2*3*4+0+pos*3]=nx;
		geomNormals[i1*subdiv*3*4+i2*3*4+1+pos*3]=ny;
		geomNormals[i1*subdiv*3*4+i2*3*4+2+pos*3]=-1.0/3;
		geomTexCoords[i1*subdiv*2*4+i2*2*4+0+pos*2]=s;
		geomTexCoords[i1*subdiv*2*4+i2*2*4+1+pos*2]=t;
}

void initCube() {
	int subdiv=100; float back=1;
	float dn=(2.0/3)/subdiv;
	float nx=-1.0/3; float ny=-1.0/3;
	float s=0; float t=0;
	float dst=1.0/subdiv;
	float x=-back; float y=-back;
	float dp=(float)2*back/subdiv;

	geomVertices=new float[4*3*subdiv*subdiv];geomTexCoords=new float[4*2*subdiv*subdiv];
	geomNormals=new float[4*3*subdiv*subdiv];geomVertexCount=4*subdiv*subdiv;
	for (int i1=0;i1<subdiv;i1++) {
		for (int i2=0;i2<subdiv;i2++) {
			quad(subdiv,i1,i2,x,y,back,nx,ny,s,t,0);
			quad(subdiv,i1,i2,x+dp,y,back,nx+dn,ny,s+dst,t,1);
			quad(subdiv,i1,i2,x+dp,y+dp,back,nx+dn,ny+dn,s+dst,t+dst,2);
			quad(subdiv,i1,i2,x,y+dp,back,nx,ny+dn,s,t+dst,3);
			nx+=dn;x+=dp;s+=dst;
		}
		nx=-1.0/3;x=-back;s=0;
		ny+=dn;y+=dp;t+=dst;
	}
}

void wall() {
	glEnable(GL_NORMALIZE);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,geomVertices);
	glNormalPointer(GL_FLOAT,0,geomNormals);
	glTexCoordPointer(2,GL_FLOAT,0,geomTexCoords);
	glDrawArrays(GL_QUADS,0,geomVertexCount);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void drawCube() {
	glPushMatrix();
	wall();
	glRotatef(90,1,0,0);
	wall();
	glRotatef(90,1,0,0);
	wall();
	glRotatef(90,1,0,0);
	wall();
	glRotatef(90,1,0,0);
	glRotatef(90,0,1,0);
	wall();
	glRotatef(180,0,1,0);
	wall();
	glPopMatrix();
}

void freeCube() {
	delete []geomVertices;
	delete []geomTexCoords;
	delete []geomNormals;
}