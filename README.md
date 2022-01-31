# Basic Tree Reduction Algorithm
A sample data structure `DecisionTree.h` was made for making a simple decision tree. The decision tree has two types of node: parent and leaf nodes. Parent nodes are represented by nodes that has value of 2, while the leaf nodes are represented by the nodes that contains the decision (1 or 0, represents the true and false respectively)

<br/>

# BoolTree Class
**Below are the use and definition of the BoolTree methods and constructor. This class' purpose is for making a simplified version of a complex truth table, through the use of binary tree graph (a Boolean Tree). An algorithm `BoolTree::simplify(...)` on the other hand, is a recursive algorithm developed (by me) for further simplification of the Boolean Tree.**

## `BoolTree()` : Constructor
Initializes a root node (a single parent node)

## `BoolTree::generate_nodes(int n)` : Void Method
Creates an initilized binary tree with n-depth. Leaf nodes are initialized with value of 0

## `BoolTree::print_leaves()` : Void Method

## `BoolTree::print_all(node* root)` : Void Method
Prints all the nodes (Parent or Leaf nodes) in pre-order traversal

## `BoolTree::print_all()` : Void Method
Uses the provious `BoolTree::print_all(node* root)` method but passes the `this->root` as parameter

## `BoolTree::insert_decision(string bin)` : Void Method
Passes a string of decision that sets the respected leaf as true (sample image of usage below)

## `BoolTree::child_compare(node* tnode)` : Void Method
Compares the child of the parent node `tnode`, and simplifies it (reduce the number of nodes by making itself act as a leaf node)

## `BoolTree::simplify(node* root)` : Void Method
Simplifies the whole boolean tree by passing its root node

## `BoolTree::decide(string binary)` : Boolean Method
Makes a decision based on the biinary input

## `BoolTree::get_root()` : Node Method
Returns the root node of this Boolean Tree

<br/>

# Sample Implementation
Generating nodes (In this example, we are generating a boolean tree with three inputs)
```C++
	...
	#include "BoolTree.h"
	using std::cout;

	int main() {
		BoolTree simple_and_gate;

		// a gate that has two inputs
		simple_and_gate.generate_nodes(2);
	}
```
Applying the code above will result in the ff. graph:

![BoolTree Graph](/Images/node_image_1.png "Node Generated with depth of 2 (2 inputs)")

<br/>

Assigning a decision
```C++
	...
	#include "BoolTree.h"
	using std::cout;

	int main() {
		BoolTree simple_and_gate;

		// a gate that only has two inputs
		simple_and_gate.generate_nodes(2);

		// assign decisions
		simple_and_gate.insert_decision("11");

		// look for the output
		cout << "1 ^ 0 = " << simple_and_gate.decide("10") << "\n";
		cout << "1 ^ 1 = " << simple_and_gate.decide("11") << "\n";
		cout << "0 ^ 1 = " << simple_and_gate.decide("01") << "\n";
		cout << "0 ^ 0 = " << simple_and_gate.decide("00") << "\n";
	}
```

Applying `BoolTree::insert_decision(...)` will result in the ff. graph (1 and 0 inputs are represented by right and left edges respectively):

![Bool Tree Graph with decision](/Images/node_image_2.png "Inserted true on decision '11'")

<br/>

Simplification of nodes can be done by simply calling the `BoolTree::simplify(...)` method:
```C++
	...
	int main() {
		...

		// simplify the nodes first for better decisioning
		simple_and_gate.simplify( simple_and_gate.get_root() );

		// look for the output
		cout << "1 ^ 0 = " << simple_and_gate.decide("10") << "\n";
		cout << "1 ^ 1 = " << simple_and_gate.decide("11") << "\n";
		cout << "0 ^ 1 = " << simple_and_gate.decide("01") << "\n";
		cout << "0 ^ 0 = " << simple_and_gate.decide("00") << "\n";
	}
```

Simplifying the tree:

![Simplified bool tree](/Images/node_image_3.png "Simplified version of the tree above")

<br/>
<br/>

# Other Notes
Although this boolean tree seems simplified enough, there is a better version of this which further simplifies not just the child nodes, but also the
parent nodes [see here](https://daixieit.com/article/index/id/1170). Modifying this code a bit and integrating a `BoolTree::parent_compare(...)` method can further simplify these nodes.

I will modify this code some time in the future, and apply the parent compare... idk, my urges are too random.