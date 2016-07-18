#include "navigation.h"
//#include "path.h"
#include "tapeFollow.h"

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
	void turn_node(const courseGraph::node *origin, const courseGraph::node *prev_node1, const courseGraph::node *prev_node2,  int direction){
		

		for (int i = 0; i < origin->neighborCount + 1; i++) {
			if (origin->neighbors[i] == prev_node1)
				prev_index = i;

		}

		if (origin->neighborCount == 1) {
			turn_dir(BACK);
		}

		else if (origin->neighborCount+1== 2) {
			if (prev_index == 0) {
				turn_dir(LEFT);
			} 
			else
				turn_dir(RIGHT);
		}
		// TODO: add functionality for not going back to second last node either
		else {
			if (dir != NONE) {
				if (dir == LEFT && origin->nextDir(prev_index) != NULL) {
					turn_dir(dir);// TODO: put safeguard against turning to NULL here 
				}

				else if ((dir == LEFT  && (origin->nextDir(prev_index) == NULL)))
					turn_dir(STRAIGHT);
			
				if (dir == RIGHT && origin->prevDir(prev_index) != NULL) {
					turn_dir(dir);// TODO: put safeguard against turning to NULL here 
				}

				else if ((dir == RIGHT && origin->prevDir(prev_index) == NULL))
					turn_dir(STRAIGHT);

				
			 }

		}


	}

	int turn(const courseGraph::node *curr_node, const courseGraph::node *prev_node1, const courseGraph::node *prev_node2) {
			
		
		//dir = cycleReadIR();
		
		//if signal detected, dir = -1
		turn_node(curr_node, prev_node1, prev_node2, dir);//mechanically turn towards 'dir'
		//else

			

	}
	


}