

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
	//RCServo0.write(20);
	RCServo1.write(140);//GRIP
	RCServo2.write(110); //

}

//tapeFollow tf;

//courseGraph graph = courseGraph();

//const courseGraph::node* next_node;
//const courseGraph::node* currr_node = &nav::graph.n12;
//const courseGraph::node* prev_node1 = &nav::graph.n17;
//const courseGraph::node* prev_node2 = &nav::graph.n16;
//int c = 0;
//int temp;
void loop() {
	menu::menuLoop();
	//arm::pickup(RIGHT);
	//delay(2000);
	/*
	delay(2000);
	temp = mux::detectAdjacentPassenger();
	
	LCD.clear(); LCD.home();
	if (temp == RIGHT) {
		LCD.print("PR");
	}
	else if(temp==LEFT) {
		LCD.print("PL");
	}
		//RCServo1.write(100);
	//delay(1000);
	//RCServo1.write(150);
	/*
	arm::stow();
	arm::pickup(RIGHT);
	delay(1000);
	arm::release();
	delay(3000);
	*/
	//tapeFollow::followTape(80);
	
	
	
	//tapeFollow::followTape(80);
	//c++
	//LCD.clear(); LCD.home();
	/*
	++if (tapeFollow::c >= 30) {
		LCD.print("NN:");
		LCD.print(next_node->ID);
		LCD.print("PN:");
		LCD.print(prev_node1->ID);
	}
	//nav::checkAdjacentPassengers();
	
	/*
	if (tapeFollow::intersectionDetected) {
		//delay(60);
		tapeFollow::followTape(10);

		next_node = nav::turn(curr_node, prev_node1, prev_node2);
		prev_node1 = curr_node;
		prev_node2 = prev_node1;

		curr_node = next_node;
	}
	
	tapeFollow::intersectionDetected = false;
	*/
	//arm::turn_arm(2);
	//delay(10000);
	//RCServo1.write(10);//GRIP
	//RCServo2.write(170);
	

	//nav::dropoff(prev_node1, currr_node);
	

}

