#ifndef opttsp_h
#define opttsp_h

#include <iostream>
#include <iomanip>
#include <limits>
#include <deque>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class optTSP {

private:
	struct Node {

		int X;
		int Y;
		double Distance = numeric_limits<double>::infinity();
		int index;
	};

	vector<Node> path;
	deque<Node> unvisited;

	deque <Node> Nodes;

	double lower_bound(deque<Node> &nodes);
	double upper_bound(deque<Node> &nodes);

	double lowBound = 0.0;

	double exactDist(Node &one, Node &two);
	double approxDist(Node &one, Node &two);
	bool is_promising(deque<Node> &unvisited, vector<Node> &path);

	double totDist;
	double dist = 0.0;

	vector<Node> OutputTSP;

public:

	void OptTsp();
	void addNode(int index, int X, int Y);
	void gen_perms();
	void printTSP();

};
#endif // !opttsp_h

