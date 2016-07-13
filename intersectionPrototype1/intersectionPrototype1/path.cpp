//#include <std/vector>
//#include <stdio.h>


//using namespace std;

#include "path.h"
void courseGraph::node::addNeighbor(const node *n) {
	neighbors[neighborCount++] = n;
}

	//11, 15 are end points
courseGraph::courseGraph(){
	
	node n1;
	node n2;
	node n3;
	node n4;
	node n5;
	node n6;
	node n7;
	node n8;
	node n9;
	node n10;
	node n11; //endpoint
	node n12;
	node n13;
	node n14;
	node n15; //endpoint
	node n16;
	node n17;
	node n18;
	node n19;
	node n20;

	n1.addNeighbor(&n2);
	n1.addNeighbor(&n5);

	
	n2.addNeighbor(&n3);
	n2.addNeighbor(&n6);
	n2.addNeighbor(&n1);

	n3.addNeighbor(&n4);
	n3.addNeighbor(&n9);
	n3.addNeighbor(&n2);

	n4.addNeighbor(&n10);
	n4.addNeighbor(&n3);

	n5.addNeighbor(&n1);
	n5.addNeighbor(&n6);
	n5.addNeighbor(&n11);

	n6.addNeighbor(&n2);
	n6.addNeighbor(&n7);
	n6.addNeighbor(&n12);
	n6.addNeighbor(&n5);

	n7.addNeighbor(&n8);
	n7.addNeighbor(&n13);
	n7.addNeighbor(&n6);

	n8.addNeighbor(&n9);
	n8.addNeighbor(&n13);
	n8.addNeighbor(&n7);

	n9.addNeighbor(&n10);
	n9.addNeighbor(&n14);
	n9.addNeighbor(&n8);
	n9.addNeighbor(&n3);

	n10.addNeighbor(&n4);
	n10.addNeighbor(&n15);
	n10.addNeighbor(&n9);

	n11.addNeighbor(&n5);

	n12.addNeighbor(&n6);
	n12.addNeighbor(&n17);
	n12.addNeighbor(&n16);
	
	n13.addNeighbor(&n8);
	n13.addNeighbor(&n7);

	n14.addNeighbor(&n20);
	n14.addNeighbor(&n19);
	n14.addNeighbor(&n9);

	
	n15.addNeighbor(&n10);

	n16.addNeighbor(&n12);

	n17.addNeighbor(&n12);

	n18.addNeighbor(&n13);

	n19.addNeighbor(&n14);

	n20.addNeighbor(&n14);


	/**
	nod/e nb;
	node nC;
	node nD;
	node nE;
	node nF;
	node nG;
	node nH;
	node nI;
	node nJ;
	node nK;
	node nL;
	node nM;

	**/

	//printf("%d \n", n10.neighbors[1]);

}
