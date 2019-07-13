#include <iostream>
#include <queue>

struct Node {
	int data;
	const char* index;
	Node* left;
	Node* right;
	Node(int x, const char* ch):data(x), index(ch){
		left = NULL;
		right = NULL;
	}
};

//Prints the Bredth First Traversal of a binary Tree
void BFTraversal(Node* root) {
	std::queue<Node*> q;
	q.push(root);
	while (!q.empty()) {
		int count = q.size();
		for (int i = 0; i < count; ++i) {
			Node* curr = q.front();
			q.pop();
			std::cout << curr->data << curr->index << " ";
			if (curr->left)
				q.push(curr->left);
			if (curr->right)
				q.push(curr->right);
		}
		std::cout << std::endl;
	}
}

//Returns the height of the Binary Tree and also chechks whether tree is balanced or not
int height(Node* root, bool& balanced) {
	if (!root)
		return NULL;
	int lh = height(root->left, balanced);
	int rh = height(root->right, balanced);
	if (balanced && abs(lh - rh) > 1)
		balanced = false;

	return std::max(lh, rh) + 1;
}

//Check if root is sum of its left and right child or not
bool childrenSum(Node* root) {
	if (root == NULL)
		return true;
	if (root->left == NULL && root->right == NULL)
		return true;
	int sum = 0;
	if (root->left != NULL)
		sum += root->left->data;
	if (root->right != NULL)
		sum += root->right->data;
	if (root->data == sum && childrenSum(root->right) && childrenSum(root->left))
		return true;
	else
		return false;
}

//Prints all nodes in the kth level of binary tree
void levelk(Node* root, int k) {
	if (root == NULL)
		return;
	if (k==0) {
		std::cout << root->data << " ";
		return;
	}
	levelk(root->left, k - 1);
	levelk(root->right, k - 1);
}

//Check if binart tree is Binary Search Tree(BST) or not
//Idea is to use in-order traversal. And we know that in-order expansion of a BST is a sorted array so we maintain a previous
//pointer and check if value of previous node is less than current(root) node or not, just like we check whether array is
//sorted or not
bool checkBST(Node* root, Node* &prev) {
	if (root == NULL)
		return true;
	if (checkBST(root->left, prev) == false)
		return false;
	if (prev!=NULL && root->data <= prev->data)
		return false;
	prev = root;
	return checkBST(root->right, prev);
}

int main() {
	//Node is a "Tree Node" which contains an extra string literal to identify its proper location in tree
	//i.e. second argument of Node is "(a,b)", where 'a' is index of root node and 'b' is index of current node
	//'x' is used to identify root node which doesn't have a parent.
	
	//normal binary tree
	Node* root = new Node(10, "(x,0)");
	root->left = new Node(2, "(0,1)");
	root->right = new Node(8, "(0,2)");
	root->left->left = new Node(1, "(1,3)");
	root->left->right = new Node(1, "(1,4)");
	root->right->left = new Node(5, "(2,5)");
	root->right->right = new Node(3, "(2,6)");
	root->left->left->left = new Node(1, "(3,7)");
	root->right->right->right = new Node(30, "(6,8)");

	BFTraversal(root);
	bool balanced=true;
	std::cout << "height: " << height(root, balanced) <<" is balanced: "<< (balanced?"Yes":"No") << std::endl;
	std::cout << "Is children sum? " << (childrenSum(root) ? "Yes" : "No") << std::endl;
	levelk(root, 2);
	
	std::cout << std::endl << std::endl;

	//binary search tree
	Node* bst = new Node(10, "(x,0)");
	bst->left = new Node(8, "(0,1)");
	bst->right = new Node(15, "(0,2)");
	bst->left->left = new Node(7, "(1,3)");
	bst->left->right = new Node(3, "(1,4)");
	bst->right->left = new Node(12, "(2,5)");
	bst->right->right = new Node(20, "(2,6)");
	bst->right->right->right = new Node(30, "(6,7)");

	BFTraversal(bst);
	Node* prev = NULL;
	std::cout << "Above tree is BST? " << (checkBST(bst, prev) ? "Yes" : "No") << std::endl;

	std::cin.get();
}
