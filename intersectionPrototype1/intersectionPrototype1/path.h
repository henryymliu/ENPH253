#ifndef _PATH_h
#define _PATH_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

class courseGraph {
public:
	//Node structure that stores neighbors, in order of appearance clockwise from south axis relative to figure
	//NOTE: add distances between nodes in future
	struct node {
		//enum dir { N, S, E, W }; //show possible branch directions of each node wrt global coordinates
								 //vector<int> neighbors;
		const node *neighbors[4];
		void addNeighbor(const node *n);
		int neighborCount = 0;
	};


	courseGraph();

};

#endif
