#ifndef CUBE_H
#define CUBE_H

//cubeVertices - tablica ze wsp�rz�dnymi wierzcho�k�w.
//cubeColors - tablica z kolorami wierzcho�k�w
//cubeVertexCount - liczba wierzcho�k�w

int cubeVertexCount=24;

float cubeVertices[]={
	-1,-1,-1,
	-1, 1,-1,
	 1, 1,-1,
	 1,-1,-1,

	-1,-1, 1,
	-1, 1, 1,
	 1, 1, 1,
	 1,-1, 1,

	-1,-1,-1,
	-1,-1, 1,
	 1,-1, 1,
	 1,-1,-1,

	-1, 1,-1,
	-1, 1, 1,
	 1, 1, 1,
	 1, 1,-1,

	-1,-1,-1,
	-1,-1, 1,
	-1, 1, 1,
	-1, 1,-1,

	 1,-1,-1,
	 1,-1, 1,
	 1, 1, 1,
	 1, 1,-1
};

float cubeColors[]={
	1,0,0, 1,0,0, 1,0,0, 1,0,0,
	0,1,0, 0,1,0, 0,1,0, 0,1,0,
	0,0,1, 0,0,1, 0,0,1, 0,0,1,
	1,1,0, 1,1,0, 1,1,0, 1,1,0,
	0,1,1, 0,1,1, 0,1,1, 0,1,1,
	1,1,1, 1,1,1, 1,1,1, 1,1,1
};



#endif