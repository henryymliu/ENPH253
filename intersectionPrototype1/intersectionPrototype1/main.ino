

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
	//tapeFollow::followTape(70);
	LCD.clear(); LCD.home();
	LCD.print(next_node->ID);

	tapeFollow::followTape(60);
	if (tapeFollow::intersectionDetected) {
		tapeFollow::followTape(10);
		delay(200);
		next_node = nav::turn(curr_node, prev_node1, prev_node2);
		prev_node1 = curr_node;
		prev_node2 = prev_node1;

		curr_node = next_node;
		
//prev_node2 = prev_node1;
		//delay(1500);
		tapeFollow::intersectionDetected = false;
	}
	//delay(30);
}

