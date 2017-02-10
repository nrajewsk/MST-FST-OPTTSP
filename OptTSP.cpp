#include "OptTSP.h"
#include "fastTSP.h"

#include <iostream>
#include <iomanip>
#include <limits>
#include <deque>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

double optTSP::lower_bound(deque<Node> &nodes) {

	deque<Node> Outties = nodes;
	deque<Node> Innies;
	double MSTtotdist = 0.0;

	Outties[0].Distance = 0.0;
	Innies.push_back(Outties[0]);
	swap(Outties[0], Outties[Outties.size() - 1]);
	Outties.pop_back();

	for (size_t i = 0; i < Outties.size(); i++) {

		Outties[i].Distance = approxDist(Innies[0], Outties[i]);
	}

	while (!Outties.empty()) {

		double minDist = numeric_limits<double>::infinity();
		int minIndex = -1;
		//find the minumum value
		for (size_t i = 0; i < Outties.size(); i++) {
			if (Outties[i].Distance < minDist) {
				minDist = Outties[i].Distance;
				minIndex = (int)i;
			}
		}
		//If minIndex == -1, there were no reachable nodes to add with a non empty 
		//Outties vector
		if (minIndex == -1) {
			cerr << "There are unreachable nodes\n";
			exit(1);
		}

		Innies.push_back(Outties[minIndex]);
		swap(Outties[minIndex], Outties[Outties.size() - 1]);
		Outties.pop_back();

		for (size_t i = 0; i < Outties.size(); i++) {

			double newDist = approxDist(Innies.back(), Outties[i]);

			if (newDist < Outties[i].Distance) {
				Outties[i].Distance = newDist;
			}//If
		}//For

	}
	for (size_t i = 0; i < Innies.size(); i++) {

		MSTtotdist += sqrt(Innies[i].Distance);
	}

	return MSTtotdist;
}

double optTSP::upper_bound(deque<Node> &nodes){

	FastTSP fTSP;
	
	for (size_t i = 0; i < nodes.size(); i++) {

		fTSP.addNode((int)i,nodes[i].X, nodes[i].Y);
	}

	fTSP.fastTSP();
	vector<int> indices = fTSP.returnIndexVec();

	for (size_t i = 0; i < indices.size(); i++) {

		OutputTSP.push_back(Nodes[indices[i]]);
	}

	return fTSP.totalDistance();
}

double optTSP::exactDist(Node &one, Node &two){

		double X1 = one.X;
		double X2 = two.X;
		double Y1 = one.Y;
		double Y2 = two.Y;

		double xSquared1 = (X1 - X2)*(X1 - X2);
		double ySquared1 = (Y1 - Y2)*(Y1 - Y2);

		return sqrt(xSquared1 + ySquared1);
}

double optTSP::approxDist(Node & one, Node & two)
{
	double X1 = one.X;
	double X2 = two.X;
	double Y1 = one.Y;
	double Y2 = two.Y;

	double xSquared1 = (X1 - X2)*(X1 - X2);
	double ySquared1 = (Y1 - Y2)*(Y1 - Y2);

	return xSquared1 + ySquared1;
}

bool optTSP::is_promising(deque<Node> &unvisited, vector<Node> &path)
{
	lowBound = lower_bound(unvisited);
	double minDistFirst = numeric_limits<double>::infinity();
	double minDistLast = numeric_limits<double>::infinity();
	double minXtraDist = 0.0;

	//find min distance to add unvisited nodes from first path node
	for (size_t i = 0; i < unvisited.size(); i++) {
		
		double tempDist = exactDist(unvisited[i], path.front());
		if (tempDist < minDistFirst) {
			minDistFirst = tempDist;
		}
	}

	//find mindist to add unvisited nodes from end of path
	for (size_t i = 0; i < unvisited.size(); i++) {

		double tempDist = exactDist(unvisited[i], path.back());
		if (tempDist < minDistLast) {
			minDistLast = tempDist;
		}
	}
	
	//Add together all the distances the "predicted" and the current
	minXtraDist = dist + minDistFirst + minDistLast + lowBound;

	//Check that there is an improvement, if not, it is not promising
	if ((minXtraDist >= totDist))
		return false;
	else 
		return true;
	
}

void optTSP::OptTsp(){

	totDist = upper_bound(Nodes);

	unvisited = Nodes;
	unvisited.pop_front();

	path.push_back(Nodes[0]);
	
	gen_perms();
}

void optTSP::addNode(int index, int X, int Y){

	Node temp;

	temp.X = X;
	temp.Y = Y;
	temp.index = index;

	Nodes.push_back(temp);
}

void optTSP::gen_perms()
{
	if (unvisited.empty()) {
		double dist1 = dist + exactDist(path.front(), path.back());
		if (dist1 <= totDist) {

			totDist = dist1;
			OutputTSP = path;
		}
		return;
	}

	if (!is_promising(unvisited, path)) {
		return;
	}

	for (size_t i = 0; i != unvisited.size(); i++) {

		path.push_back(unvisited.front());
		unvisited.pop_front();
		dist += exactDist(path.back(), path[path.size() - 2]);
		gen_perms();

		unvisited.push_back(path.back());
		path.pop_back();
		dist -= exactDist(path.back(), unvisited.back());
	}
}

void optTSP::printTSP(){

	cout << totDist << '\n';
	for (size_t i = 0; i < OutputTSP.size(); i++)
	{
		cout << OutputTSP[i].index << ' ';
	}
	cout << '\n';
}
