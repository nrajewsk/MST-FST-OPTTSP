#ifndef fasttsp_h
#define fasttsp_h

#include <iostream>
#include <iomanip>
#include <limits>
#include <deque>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class FastTSP {
private:
	//Tracks coordinates and other impotrtant info for calculations
	struct fastTSPNode {
		int index;
		int X;
		int Y;
	};

	double approxDist(const fastTSPNode &one, const fastTSPNode &two);
	double exactDist(const fastTSPNode &one, const fastTSPNode &two);

	deque<fastTSPNode> outties;
	deque<fastTSPNode> innies;

	double totDist;

public:
	/*
	*Requires: 
	*Modifies:
	*Effects:
	*/
	void fastTSP();
	/*
	*Requires:
	*Modifies:
	*Effects:
	*/
	void printFastTSP();
	/*
	*Requires:
	*Modifies:
	*Effects:
	*/
	void addNode(int index, int X, int Y);

	double totalDistance();

	vector<int> returnIndexVec();

};

#endif // !fasttsp_h

