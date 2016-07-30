

/*
 Name:		intersectionPrototype1.ino
 Created:	6/29/2016 6:51:41 PM
 Author:	Henry
*/

//NOTE: ADD HEADERS HERE

#include "multiplex.h"
#include "armControl.h"
#include "eepromParams.h"
#include "navigation.h"
#include "menu.h"
#include "armControl.h"
#include <phys253.h>          
#include <LiquidCrystal.h> 
#include "tapeFollow.h"


void setup() {

	#include <phys253setup.txt>
	Serial.begin(9600);
	

}

//tapeFollow tf;
enum state{inMenu, TapeFollow};
courseGraph graph = courseGraph();
state currState = inMenu;
const courseGraph::node* next_node;
const courseGraph::node* curr_node = &graph.n4;
const courseGraph::node* prev_node1 = &graph.n10;
const courseGraph::node* prev_node2 = &graph.n3;

void loop() {


	/*
	switch (currState) {
	case inMenu:
		Menu::menuLoop();
		break;
	}
	*/
	//tapeFollow::followTape(80);
	
	
	
	
	tapeFollow::followTape(70);
	LCD.clear(); LCD.home();
	//if (tapeFollow::c >= 30) {
		LCD.print("NN:");
		LCD.print(next_node->ID);
	//}
	//nav::checkAdjacentPassengers();
	
	
	if (tapeFollow::intersectionDetected) {
		//delay(100);
		tapeFollow::followTape(10);

		next_node = nav::turn(curr_node, prev_node1, prev_node2);
		prev_node1 = curr_node;
		prev_node2 = prev_node1;

		curr_node = next_node;
	}
	
	tapeFollow::intersectionDetected = false;
	

}

