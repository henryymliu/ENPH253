//#include <std/vector>
//#include <stdio.h>


//using namespace std;

#include "path.h"
void courseGraph::node::addNeighbor(const node *n) {
	neighbors[i++] = n;
	if (n != NULL)
		neighborCount++;

}

const courseGraph::node* courseGraph::node::nextDir(int ind) const{ // ind from 0 to 3 inclusive
	return neighbors[(ind + 1) % 4];

}


const courseGraph::node* courseGraph::node::prevDir(int ind) const{ // ind from 0 to 3 inclusive
	if (ind == 0)
		ind = 4;
	return neighbors[(ind - 1)];
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
	n1.preferred1 = &n2;
	n1.preferred2 = &n5;

	n2.addNeighbor(NULL);
	n2.addNeighbor(&n3);
	n2.addNeighbor(&n6);
	n2.addNeighbor(&n1);
	n2.preferred1 = &n3;
	n2.preferred2 = &n1;

	n3.addNeighbor(NULL);
	n3.addNeighbor(&n4);
	n3.addNeighbor(&n9);
	n3.addNeighbor(&n2);
	n3.preferred1 = &n4;
	n3.preferred2 = &n2;

	n4.addNeighbor(&n10);
	n4.addNeighbor(&n3);
	n4.preferred1 = &n3;
	n4.preferred2 = &n10;

	
	n5.addNeighbor(&n1);
	n5.addNeighbor(&n6);
	n5.addNeighbor(&n11);
	n5.addNeighbor(NULL);
	n5.preferred1 = &n6;
	n5.preferred2 = &n1;

	n6.addNeighbor(&n2);
	n6.addNeighbor(&n7);
	n6.addNeighbor(&n12);
	n6.addNeighbor(&n5);
	n6.preferred1 = &n12;
	n6.preferred2 = &n7;

	n7.addNeighbor(&n8);
	n7.addNeighbor(NULL);
	n7.addNeighbor(&n13);
	n7.addNeighbor(&n6);
	n7.preferred1 = &n13;
	n7.preferred2 = &n8;

	n8.addNeighbor(&n9);
	n8.addNeighbor(&n13);
	n8.addNeighbor(NULL);
	n8.addNeighbor(&n7);
	n8.preferred1 = &n13;
	n8.preferred2 = &n7;

	n9.addNeighbor(&n10);
	n9.addNeighbor(&n14);
	n9.addNeighbor(&n8);
	n9.addNeighbor(&n3);
	n9.preferred1 = &n14;
	n9.preferred2 = &n10;

	n10.addNeighbor(&n4);
	n10.addNeighbor(NULL);
	n10.addNeighbor(&n15);
	n10.addNeighbor(&n9);
	n10.preferred1 = &n4;
	n10.preferred2 = &n9;

	n11.addNeighbor(&n5);


	n12.addNeighbor(&n6);
	n12.addNeighbor(NULL);
	n12.addNeighbor(&n17);
	n12.addNeighbor(&n16);
	n12.preferred1 = &n16;
	n12.preferred2 = &n6;

	n13.addNeighbor(NULL);
	n13.addNeighbor(&n8);
	n13.addNeighbor(&n7);
	n13.addNeighbor(&n18);
	n13.preferred1 = &n18;
	n13.preferred2 = &n7;

	n14.addNeighbor(&n20);
	n14.addNeighbor(&n19);
	n14.addNeighbor(&n9);
	n14.addNeighbor(NULL);
	n14.preferred1 = &n19;
	n14.preferred2 = &n20;
	
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
