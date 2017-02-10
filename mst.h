#ifndef mst_h
#define mst_h

#include <iostream>
#include <iomanip>
#include <limits>
#include <vector>
#include <algorithm>

using namespace std;

class MST {
private:
	struct MSTNode {

		int Previous = -1;
		double Distance = numeric_limits<double>::infinity();
		int index;
		int X;
		int Y;
	};

	/*
	*Requires: Two nodes with valid coordinates
	*Modifies: Nothing.
	*Effects:  Returns a comparable representation of
	*		   distance between two nodes.
	*/
	double approxDist(const MSTNode &one, const MSTNode &two);

	vector<MSTNode> Outties;
	vector<MSTNode> Innies;

public:
	/*
	*Requires: addNode has been used to add valid nodes.
	*Modifies: Nothing public.
	*Effects:  Creates a vector of Nodes connected as MST.
	*/
	void primsMST();
	/*
	*Requires: That a valid MST has been created with primsMST.
	*Modifies: Nothing.
	*Effects:  Prints the total cost of the MST. Followed by
	*/
	void PrintMST();
	/*
	*Requires: A valid X and Y coordinate
	*Modifies: Nothing public.
	*Effects:  Adds a node that can subsequently used when
	*		   computing the MST.
	*/
	void addNode(int index, int X, int Y);

};

#endif // !mst_h
