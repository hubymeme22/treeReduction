#include "DecisionTree.h"
#include <chrono>
using namespace std;
using namespace std::chrono;

int main() {
	// make new gate and generate nodes of 4-layer depth
	BoolTree covidGate;
	covidGate.generate_nodes(4);

	// insert decision to have covid
	covidGate.insert_decision("1111");
	covidGate.insert_decision("1100");
	covidGate.insert_decision("1010");

	// count the speed of the algorithm
	auto start = high_resolution_clock::now();
	covidGate.print_all();
	auto end = high_resolution_clock::now();

	auto duration = duration_cast<microseconds>(end  - start);
	cout << endl << "microseconds it took to traverse all nodes : " << duration.count() << endl;

	// simplify the gates
	covidGate.simplify( covidGate.get_root() );

	// count the speed of the algorithm (simplified)
	auto start1 = high_resolution_clock::now();
	cout << endl;
	covidGate.print_all();
	auto end1 = high_resolution_clock::now();

	auto duration1 = duration_cast<microseconds>(end1 - start1);
	cout << endl << "microseconds it took to traverse all nodes : " << duration1.count() << endl;
}

// 1110101010
