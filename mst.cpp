#include "mst.h"

#include <iostream>
#include <iomanip>
#include <limits>
#include <vector>
#include <algorithm>

using namespace std;

double MST::approxDist(const MSTNode & one, const MSTNode & two){

	double X1 = one.X;
	double X2 = two.X;
	double Y1 = one.Y;
	double Y2 = two.Y;

	double xSquared1 = (X1 - X2)*(X1 - X2);
	double ySquared1 = (Y1 - Y2)*(Y1 - Y2);

	return xSquared1 + ySquared1;
}

void MST::primsMST() {

	Outties[0].Distance = 0.0;
	Innies.push_back(Outties[0]);
	swap(Outties[0], Outties[Outties.size() - 1]);
	Outties.pop_back();

	//set the distances from root node to reachable nodes
	if ((Innies[0].X <= 0 && Innies[0].Y == 0) ||
		(Innies[0].X == 0 && Innies[0].Y <= 0)) {
		for (size_t i = 0; i < Outties.size(); i++) {

			Outties[i].Distance = approxDist(Innies[0], Outties[i]);
			Outties[i].Previous = 0;
		}
	}
	else if (Innies.back().X > 0 || Innies.back().Y > 0) {
		for (size_t i = 0; i < Outties.size(); i++) {
			if (Outties[i].X >= 0 || Outties[i].Y >= 0) {
				Outties[i].Distance = approxDist(Innies[0], Outties[i]);
				Outties[i].Previous = 0;
			}
		}
	}
	else {
		for (size_t i = 0; i < Outties.size(); i++)
		{
			if (Outties[i].X <= 0 && Outties[i].Y <= 0) {
				Outties[i].Distance = approxDist(Innies[0], Outties[i]);
				Outties[i].Previous = 0;
			}
		}
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

		//Is the added node a border node
		//	If so, check distance for all nodes
		if ((Innies.back().X <= 0 && Innies.back().Y == 0) ||
			(Innies.back().X == 0 && Innies.back().Y <= 0)) {

			for (size_t i = 0; i < Outties.size(); i++) {

				double newDist = approxDist(Innies.back(), Outties[i]);

				if (newDist < Outties[i].Distance) {
					Outties[i].Distance = newDist;
					Outties[i].Previous = Innies.back().index;
				}//If
			}//For
		}//If
		 //Is the node a normal node
		 //	If so check distance for all normal and border nodes
		else if (Innies.back().X > 0 || Innies.back().Y > 0) {
			for (size_t i = 0; i < Outties.size(); i++) {
				if (Outties[i].X >= 0 || Outties[i].Y >= 0) {

					double newDist = approxDist(Innies.back(), Outties[i]);

					if (newDist < Outties[i].Distance) {
						Outties[i].Distance = newDist;
						Outties[i].Previous = Innies.back().index;
					}//if
				}//if
			}//for
		}//else if
		 //Else it must be a wild node, update distances for only wild and
		else {
			for (size_t i = 0; i < Outties.size(); i++) {
				if (Outties[i].X <= 0 && Outties[i].Y <= 0) {

					double newDist = approxDist(Innies.back(), Outties[i]);

					if (newDist < Outties[i].Distance) {
						Outties[i].Distance = newDist;
						Outties[i].Previous = Innies.back().index;
					}//if
				}//if
			}//for
		}//else
	}
}

void MST::PrintMST(){

	double totalDistance = 0.0;

	for (size_t i = 0; i < Innies.size(); i++) {
		totalDistance += sqrt(Innies[i].Distance);
	}
	cout << totalDistance << '\n';

	for (size_t i = 1; i < Innies.size(); i++) {

		if (Innies[i].Previous > Innies[i].index) {
			cout << Innies[i].index << ' ' << Innies[i].Previous << '\n';
		}
		else {
			cout << Innies[i].Previous << ' ' << Innies[i].index << '\n';
		}
	}
}

void MST::addNode(int index, int X, int Y){

	MSTNode temp;

	temp.X = X;
	temp.Y = Y;
	temp.index = index;

	Outties.push_back(temp);
}
