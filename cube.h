#ifndef CUBE_H
#define CUBE_H

//cubeVertices - tablica ze wspó³rzêdnymi wierzcho³ków.
//cubeColors - tablica z kolorami wierzcho³ków
//cubeVertexCount - liczba wierzcho³ków

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