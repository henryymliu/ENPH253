#include "navigation.h"
//#include "path.h"
#include "tapeFollow.h"
#include "multiplex.h"

namespace nav {

	int dir;
	int neighborCount;
	int prev_index;
	int speed = 60;

	//courseGraph graph = courseGraph();
	courseGraph::node *temp;
	void turn_dir(int dir) {
		if (dir == LEFT)
			tapeFollow::turnLeft();
		if (dir == RIGHT)
			tapeFollow::turnRight();
		if (dir == STRAIGHT)
			tapeFollow::followTape(speed); //TODO: which speed?
		if (dir == BACK)
			tapeFollow::turnAround();
	}
	const courseGraph::node* turn_node(const courseGraph::node *origin, const courseGraph::node *prev_node1, const courseGraph::node *prev_node2,  int direction){
		const courseGraph::node *nextNode;

		for (int i = 0; i < origin->neighborCount + 1; i++) {
			if (origin->neighbors[i] == prev_node1)
				prev_index = i;
				
		}

		if (origin->neighborCount == 1) {
			turn_dir(BACK);
			nextNode = origin->neighbors[0];
		}

		else if (origin->neighborCount== 2) {
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
					nextNode = origin->neighbors[(prev_index+2)%4];
				}

				else if (dir == STRAIGHT) {
					if (origin->neighbors[(prev_index + 2) % 4] != NULL) {
						turn_dir(STRAIGHT);
						nextNode=origin->neighbors[(prev_index + 2) % 4];

					}
					else {
						turn_dir(LEFT);
						nextNode = origin->nextDir(prev_index);
					}
			
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
	


}