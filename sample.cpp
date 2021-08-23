#include "DecisionTree.h"

int main() {
	// simple program for testing
	// the Decision tree reduction algorithm

	// Bool Tree that will be used in the program
	BoolTree compGate;

	// assign a depth of 10
	// this should have 2047 nodes
	compGate.generate_nodes(10);

	// assign the true values (random)
	compGate.insert_decision("1101001011");
	compGate.insert_decision("1101010011");
	compGate.insert_decision("0101010010");
	compGate.insert_decision("1101001011");
	compGate.insert_decision("0101011011");
	compGate.insert_decision("1100000011");
	compGate.insert_decision("0111010011");
	compGate.insert_decision("0101000011");
	compGate.insert_decision("1101010011");

	// confirm the number of nodes
	cout << "Whole tree :" << endl;
	compGate.print_all();

	// simplify the tree
	compGate.simplify( compGate.get_root() );

	// print the simplified node
	cout << endl << "Reduced tree : " << endl;
	compGate.print_all();
}
