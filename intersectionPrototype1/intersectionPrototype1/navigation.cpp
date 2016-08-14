#include "navigation.h"
//#include "path.h"
#include "tapeFollow.h"
#include "multiplex.h"
#include "phys253.h"
#include "armControl.h"
#include "menu.h"

#define ARR_SIZE 10
#define fardropDelay 5000
#define closedropDelay 3500
namespace nav {
	courseGraph graph = courseGraph();
	int dir;
	int neighborCount;
	int prev_index;
	int temp_index;
	unsigned long time;
	bool collide = false;
	
	int speed = 75;

	int find_index(const courseGraph::node *origin, const courseGraph::node *target) {
		for (int i = 0; i < 4; i++) {
			if (origin->neighbors[i] == target) {
				return i;
			}
		}
	}



	//courseGraph graph = courseGraph();
	courseGraph::node *temp;
	void turn_dir(int dir) {

		if (dir == LEFT) {
			delay(150);
			tapeFollow::turnLeft();
		}
		if (dir == RIGHT) {
			delay(150);
			tapeFollow::turnRight();
		}
		if (dir == STRAIGHT) {
			delay(50);
			tapeFollow::followTape(speed); //TODO: which speed?
			
		}
		if (dir == BACK)
			tapeFollow::turnAround();
	}
	const courseGraph::node* turn_node(const courseGraph::node *origin, const courseGraph::node *prev_node1, const courseGraph::node *prev_node2, int direction) {
		const courseGraph::node *nextNode;


		prev_index = find_index(origin, prev_node1);
		//for (int i = 0; i < origin->neighborCount + 1; i++) {
			//if (origin->neighbors[i] == prev_node1)
			//	prev_index = i;

		//}

		//if (origin->neighborCount == 1) {
			//turn_dir(BACK);
			//nextNode = origin->neighbors[0];
		//}

		if (origin->neighborCount == 2) {
			if (prev_index == 0) {
				turn_dir(LEFT);
				nextNode = origin->neighbors[1];
			}
			else {
				turn_dir(RIGHT);
				nextNode = origin->neighbors[0];
			}
		}
		// TODO: add functionality for not going back to second last node either
		else {
			if (dir != NONE) {
				if (dir == LEFT && origin->nextDir(prev_index) != NULL) {
					turn_dir(dir);// TODO: put safeguard against turning to NULL here 
					nextNode = origin->nextDir(prev_index);

				}

				else if ((dir == LEFT && (origin->nextDir(prev_index) == NULL))) {
					turn_dir(STRAIGHT);
					if (prev_index == 1) {
						prev_index = 3;
					}
					else if (prev_index == 0) {
						prev_index = 2;
					}
					else
						prev_index -= 2;
					nextNode = origin->neighbors[(prev_index)];
				}

				else if (dir == RIGHT && origin->prevDir(prev_index) != NULL) {
					turn_dir(dir);
					nextNode = origin->prevDir(prev_index);// TODO: put safeguard against turning to NULL here 
				}

				else if ((dir == RIGHT && origin->prevDir(prev_index) == NULL)) {
					turn_dir(STRAIGHT);
					nextNode = origin->neighbors[(prev_index + 2) % 4];
				}

				else if (dir == STRAIGHT) {
					if (origin->neighbors[(prev_index + 2) % 4] != NULL) {
						turn_dir(STRAIGHT);
						nextNode = origin->neighbors[(prev_index + 2) % 4];

					}
					else {
						turn_dir(LEFT);
						nextNode = origin->nextDir(prev_index);
					}

				}



			}

			else {

				if (origin->preferred1 != prev_node1) {
					temp_index = find_index(origin, origin->preferred1);
					nextNode = origin->preferred1;
				}

				else if (origin->preferred1 == prev_node1) {
					temp_index = find_index(origin, origin->preferred2);
					nextNode = origin->preferred2;
				}
				if (abs(prev_index - temp_index) == 2) {
					turn_dir(STRAIGHT);
				}
				else if (abs(prev_index - temp_index) == 1) {
					if (prev_index > temp_index) {
						turn_dir(RIGHT);
					}
					else {
						turn_dir(LEFT);

					}
				}

				else {
					if (prev_index > temp_index)
						turn_dir(RIGHT);
					else
						turn_dir(LEFT);

				}
			}

		}
		return nextNode;



	}

	const courseGraph::node* turn(const courseGraph::node *curr_node, const courseGraph::node *prev_node1, const courseGraph::node *prev_node2) {
		//const courseGraph::node *next_node;

		dir = mux::cycleReadIR();

		//if signal detected, dir = -1
		return turn_node(curr_node, prev_node1, prev_node2, dir);//mechanically turn towards 'dir'
		//else



	}

	void move_to(const courseGraph::node *prev_node, const courseGraph::node *origin, const courseGraph::node *next_node) {
		int next_index;
		int prev_index;
		next_index = find_index(origin, next_node);
		prev_index = find_index(origin, prev_node);

		if (abs(prev_index - next_index) == 2) {
			turn_dir(STRAIGHT);
		}
		else if (abs(prev_index - next_index) == 1) {
			if (prev_index > next_index) {
				turn_dir(RIGHT);
			}
			else {
				turn_dir(LEFT);

			}
		}

		else {
			if (prev_index > next_index)
				turn_dir(LEFT);
			else
				turn_dir(RIGHT);

		}

	}


	const courseGraph::node* move_min(const courseGraph::node *prev_node, const courseGraph::node *curr_node) {
		int min = 99;
		const courseGraph::node* min_node;
		for (int i = 0; i < 4; i++) {
			if (curr_node->neighbors[i]->ID < min) {
				min = curr_node->neighbors[i]->ID;
				min_node = curr_node->neighbors[i];
			}

		}
		return min_node;


	}


	void dropoff(const courseGraph::node *prev_node, const courseGraph::node *curr_node) {
		const courseGraph::node *temp_node = curr_node;

		while (temp_node->ID != 1 && temp_node->ID != 2 && temp_node->ID != 3 && temp_node->ID != 4) {
			//LCD.home(); LCD.print("cN:");
			//LCD.print(curr_node->ID);
			tapeFollow::followTape(speed);
			if (tapeFollow::intersectionDetected) {
				if (collide) {
					tapeFollow::turnAround();
					tapeFollow::collision = false;
					collide = false;
				}
				temp_node = move_min(prev_node, curr_node);
				//move_to()
				move_to(prev_node, curr_node, temp_node);


				prev_node = curr_node;
				curr_node = temp_node;
				//LCD.home(); LCD.print("cN:");
				//LCD.print(curr_node->ID);
				tapeFollow::intersectionDetected = false;

			}
			else if (tapeFollow::collision) {
				tapeFollow::turnAround();
				collide = true;
				//tapeFollow::collision = false;
			}
		}

		while (!tapeFollow::intersectionDetected) {
			tapeFollow::followTape(speed);
		}
		

		if (temp_node->ID == 1 || temp_node->ID == 2) {
			menu::prevN1 = &nav::graph.n2;
			menu::currN = &nav::graph.n3;
			tapeFollow::turnRight();
			time = millis();
			if (temp_node->ID == 1) {
				while (millis() - time < fardropDelay)
					tapeFollow::followTape(speed);
			}
			 
			else {
				while (millis() - time < closedropDelay)
					tapeFollow::followTape(speed);
				}		
				
			tapeFollow::turnAround();
			time = millis();
			while (millis() - time < 1000) {
					tapeFollow::followTape(50);
			}
			delay(1000);
			motor.stop_all();
			delay(200);
			arm::extend();
			delay(100);
			
			arm::release();
			delay(200);
			arm::retract();
			delay(200);
			tapeFollow::turnAround();


		}
		



		else if (temp_node->ID == 3 || temp_node->ID == 4) {
			menu::prevN1 = &nav::graph.n3;
			menu::currN = &nav::graph.n2;
			tapeFollow::turnLeft();
			time = millis();
			if (temp_node->ID == 4) {
				while (millis() - time < fardropDelay)
					tapeFollow::followTape(speed);
			}

			else {
				while (millis() - time < closedropDelay)
					tapeFollow::followTape(speed);

			}

			//tapeFollow::turnAround();
			delay(500);
			arm::release();
		
		}

		//nav::
		tapeFollow::intersectionDetected = false;


	}

	
	int checkAdjacentPassengers(){
		int passDir = mux::detectAdjacentPassenger(); //TODO:Refine the close-range IR input v/s long-range
		if (passDir != NONE) {
			switch (passDir){
			case RIGHT: //pickup from right
				motor.stop_all();
				delay(500);
				arm::pickup(RIGHT);
				//arm::extend_grab();
				//delay(4000);
				//arm::retract();
				//delay(4000);
				break;
			case LEFT: //pickup from left
				motor.stop_all();
				delay(500);
				arm::pickup(LEFT);
				break;
			}
		}
		return passDir;
	}
	

}