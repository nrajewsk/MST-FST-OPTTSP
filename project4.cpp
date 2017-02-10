#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>

#include "mst.h"
#include "fastTSP.h"
#include "OptTSP.h"

using namespace std;

char ReadInCommands(int argc, char* argv[]);

int main(int argc, char* argv[]) {
	
	ios_base::sync_with_stdio(false);
	cout << setprecision(2);
	cout << fixed;

	char mode = ReadInCommands(argc, argv);;

	int numVertices = 0;
	cin >> numVertices;

	if (mode == 'm') {
		MST primsMST;
		for (int i = 0; i < numVertices; i++) {
			int X, Y;
			cin >> X >> Y;
			primsMST.addNode(i, X, Y);
		}
		primsMST.primsMST();
		primsMST.PrintMST();
	}
	else if (mode == 'f') {
		FastTSP fTSP;
		for (int i = 0; i < numVertices; i++) {

			int X, Y;
			cin >> X >> Y;
			fTSP.addNode(i, X, Y);
		}
		fTSP.fastTSP();
		fTSP.printFastTSP();
	}
	else {
		optTSP oTSP;
		for (int i = 0; i < numVertices; i++){

			int X, Y;
			cin >> X >> Y;
			oTSP.addNode(i, X, Y);
		}
		oTSP.OptTsp();
		oTSP.printTSP();
	}
	return 0;
}
/*
*Requires: Valid argc and argv.
*Modifies: Nothing.
*Effects:  Decides mode that program is to be ran in
*/
char ReadInCommands(int argc, char * argv[]){

	if (argc > 1 && argc < 4) {
		if (!strcmp(argv[1], "-m") || !strcmp(argv[1], "--mode")) {
			if (argc == 3) {
				if (!strcmp(argv[2], "MST")) {
					return 'm';
				}//if
				else if (!strcmp(argv[2], "FASTTSP")) {
					return 'f';
				}
				else if (!strcmp(argv[2], "OPTTSP")) {
					return 'o';
				}
				else {
					cerr << "Invalid Mode entered.  Must be MSTMSTNode, OPTTSP, or FASTTSP\n";
					exit(1);
				}//else
			}//if
			else {
				cerr << "Must enter a mode. Must be MSTMSTNode, OPTTSP, or FASTTSP\n";
				exit(1);
			}//else
		}//if

		else if (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")) {
			cout << "This is the help section\n";
			exit(0);
		}//else if
		else {
			cerr << "Incorrect commands entered\n";
			exit(1);
		}//else
	}//if

	else {
		cerr << "No commands entered\n";
		exit(1);
	}
}