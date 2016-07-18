// navigation.h

#ifndef _NAVIGATION_h
#define _NAVIGATION_h
#define LEFT 0
#define STRAIGHT 1
#define RIGHT 2
#define BACK -1
#define NONE -2

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "path.h"
#include "IR.h"
namespace nav {
	//Navigates from startN to endN.
	//Returns 0 if successful, otherwise failed with status
	//int navToNode(const courseGraph::node *startN, const courseGraph::node *endN);
	void turn(const courseGraph::node *curr_node, const courseGraph::node *prev_node1, courseGraph::node *prev_node2);
	void turn_node(const courseGraph::node *origin, const courseGraph::node *prev_node1, const courseGraph::node *prev_node2, int direction);
	void turn_dir(int turn);



	


}

#endif

