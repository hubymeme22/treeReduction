#include <iostream>
#include <queue>
using namespace std;

// value per node will be initialized to 0
// of course, left and right are pointed to NULL
struct node {
	// data used is short, since by default
	// the binary value stored is 2 (not 1 nor 0)
	short data;
	int depth;

	node* left;
	node* right;

	// constructor for the node
	node() {
		// intialize pointers to NULL, just to make sure
		left = NULL;
		right = NULL;

		// nodes with data value of 2, means that this
		// node is an internal node. The node wit the
		// value of 0 or 1, are leaf nodes
		data = 2;
	}
};

// this BoolTree class will be able to construct
// a decision tree that decides a complex boolean algebra
class BoolTree {
	private:
		node* root;
		int tree_depth;
	public:
		// initializes the root node
		// a node with no value
		BoolTree();

		// generate a n-layer depth of nodes
		// from the root (for combination)
		void generate_nodes(int depth);

		// prints all the leaf nodes
		void print_leaves();
		void print_all(node*);
		void print_all();

		// assign values at the leaf (decision)
		void insert_decision(string binary);

		// compare two child and simplify the root node
		void child_compare(node* target_node);

		// simplifies (making decision faster)
		void simplify(node* target_node);

		// checks for decision with specified input
		bool decide(string binary);

		// retrieves the root node
		node* get_root() const;
};


////////////////////////////
// definition of BoolTree //
////////////////////////////

// constructor
BoolTree::BoolTree() {
	// initialize the root node
	root = new node;
	root->depth = 0;
}

// this method generates a tree from the root node
// with n-depth, right will represent as 1 and left as 0
void BoolTree::generate_nodes(int depth) {
	// assign the value of depth
	tree_depth = depth;

	// queue where the latest are to be appended at
	// the back, and generate new decendants for the
	// current node at the top
	queue<node*> list;
	list.push(root);

	// generate new descendants for the node at the
	// top of the queue
	while (true) {
		// retrieve the front node in the queue
		// this current node's depth will be checked
		// if the node needs descendants or nah
		node* target_node = list.front();
		if (target_node->depth < depth) {
			// make left and right nodes
			node* left = new node;
			node* right = new node;

			// update their depths
			left->depth = target_node->depth + 1;
			right->depth = target_node->depth + 1;

			// another condition for checking if the node
			// is already the leaf node
			if (target_node->depth + 1 == depth) {
				// assign 0's in their values
				left->data = 0;
				right->data = 0;
			}

			// connect this node to current target node
			target_node->left = left;
			target_node->right = right;

			// push the left and right to the queue
			list.pop();
			list.push(left);
			list.push(right);
		} else {
			break;
		}
	}
}

// traverse all the values and prints it in pre-order format
void BoolTree::print_all(node* target_node) {
	if (target_node != NULL) {
		cout << target_node->data << " ";
		print_all(target_node->left);
		print_all(target_node->right);
	}
}

void BoolTree::print_all() {
	print_all(root);
}

// insert the true value to the path
void BoolTree::insert_decision(string binary) {
	// check the size of binary and the max depth of the tree
	if (binary.size() == tree_depth) {
		// where the root node is temporarily stored
		node* adjusting_node = root;

		// for loop with decision
		for (int i = 0; i < tree_depth; i++) {
			if (binary[i] == '0') {
				adjusting_node = adjusting_node->left;
			} else {
				adjusting_node = adjusting_node->right;
			}
		}

		// put true value on the specified node
		adjusting_node->data = 1;
	}
}

// simplify the nodes by poping the child node and
// pushing a node upward
void BoolTree::child_compare(node* target_node) {
	// sanitize and make sure that this target_node is a parent
	// of two leaf nodes
	if (target_node->left->data == 2 || target_node->right->data == 2) {
		// break the algorithm and do nothing
		return;
	}

	// compare the left and right child
	if (target_node->left->data == target_node->right->data) {
		// assign the data on the target node as
		// the current leaf node
		target_node->data = target_node->left->data;
		target_node->left = NULL;
		target_node->right = NULL;

		// de-allocate the memory
		delete target_node->left;
		delete target_node->right;
	}
}

// TO-DO: make a traversal technique to implement the
// parent andchild compare algorithms
void BoolTree::simplify(node* target_node) {
	// check of the node is pointing to the left or right leaf, then stop
	if ((target_node->left->data == 1 || target_node->left->data == 0) &&
		(target_node->right->data == 1 || target_node->right->data == 0)) {
		// apply the parent simplification
		// cout << "STOOOP!!" << endl;
		child_compare(target_node);
		return; // (stop for now)
	} else {
		// simplify the left and right node first before
		// simplifying the self
		simplify(target_node->left);
		simplify(target_node->right);
		child_compare(target_node);
	}
}

// traverses the left and right nodes
bool BoolTree::decide(string binary) {
	// this is pointed to the root and will soon pointed
	// to the leaf where the decision is stored
	node* decision = root;

	// loop for deciding if the pointer is going left or right
	for (int i = 0; i < tree_depth; i++) {
		// check if the decision is going left (0) or right (1)
		// check if the left or right decision is pointing to null
		// meaning, this is simplified
		if (binary[i] == '0') {
			// meaning the node is simplified
			if (decision->left == NULL)
				break;

			// if not simplified, continue traversing
			decision = decision->left;
		} else {
			// meaning the node is simplified
			if (decision->right == NULL)
				break;

			// if not simplified, continue traversing
			decision = decision->right;
		}
	}

	// retrieve the node value and return.
	return decision->data;
}

// retrieves the root node
node* BoolTree::get_root() const {
	return root;
}
