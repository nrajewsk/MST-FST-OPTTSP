#include "fastTSP.h"

#include <iostream>
#include <iomanip>
#include <limits>
#include <deque>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

double FastTSP::approxDist(const fastTSPNode & one, const fastTSPNode & two){

	double X1 = one.X;
	double X2 = two.X;
	double Y1 = one.Y;
	double Y2 = two.Y;

	double xSquared1 = (X1 - X2)*(X1 - X2);
	double ySquared1 = (Y1 - Y2)*(Y1 - Y2);

	return xSquared1 + ySquared1;
}

double FastTSP::exactDist(const fastTSPNode & one, const fastTSPNode & two){

	double X1 = one.X;
	double X2 = two.X;
	double Y1 = one.Y;
	double Y2 = two.Y;

	double xSquared1 = (X1 - X2)*(X1 - X2);
	double ySquared1 = (Y1 - Y2)*(Y1 - Y2);

	return sqrt(xSquared1 + ySquared1);
}

void FastTSP::fastTSP(){

	innies.push_back(outties[0]);
	innies.push_front(outties[0]);

	//Remove the 0th node from outties
	outties.pop_front();

	//Create iterator at beginning
	deque<fastTSPNode>::iterator it = innies.begin();

	//insert 1st element in the middle
	innies.insert(it + 1, outties.front());

	//remove the front() element of otties
	outties.pop_front();

	totDist += 2 * exactDist(innies[1], innies[0]);

	while (!outties.empty()) {

		//"Arbitrarily" select node to be added
		fastTSPNode temp = outties.front();
		outties.pop_front();

		double minDist = numeric_limits<double>::infinity();
		int minIndex = -1;

		//Calc all possible insertion distances
		for (size_t i = 0; i < innies.size() - 1; i++) {

			double dist1 = exactDist(innies[i], temp);
			double dist2 = exactDist(temp, innies[i + 1]);
			double dist3 = exactDist(innies[i], innies[i + 1]);

			double compare = dist1 + dist2 - dist3;

			if (compare < minDist) {

				minDist = compare;
				minIndex = (int)i;
			}

		}
		totDist += minDist;
		it = innies.begin();
		innies.insert(it + minIndex + 1, temp);
	}

	totDist += exactDist(innies.front(), innies.back());
}

void FastTSP::printFastTSP(){
	
	innies.pop_back();
	cout << totDist << '\n';

	for (size_t i = 0; i < innies.size(); i++) {

		cout << innies[i].index << ' ';
	}
	cout << '\n';
}

void FastTSP::addNode(int index, int X, int Y){

	fastTSPNode temp;

	temp.X = X;
	temp.Y = Y;
	temp.index = index;

	outties.push_back(temp);
}

double FastTSP::totalDistance()
{
	return totDist;
}

vector<int> FastTSP::returnIndexVec()
{
	vector<int> indices;
	
	for (size_t i = 0; i < innies.size() - 1; i++) {

		indices.push_back(innies[i].index);
	}

	return indices;
}
