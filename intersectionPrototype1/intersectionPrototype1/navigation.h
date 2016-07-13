// navigation.h

#ifndef _NAVIGATION_h
#define _NAVIGATION_h

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
	int navToNode(const courseGraph::node *startN, const courseGraph::node *endN);


	


}

#endif

