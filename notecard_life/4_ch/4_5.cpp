#include <stdio.h>
#include <stdlib.h>
#include <vector>

#define DEBUG 1

class Tree {
	public:
		Tree(int d, int l, Tree *parent);
		void printTree();
		void insert(int d);
		int getData();
		bool validateBST();

		Tree *parent;
		Tree *left;
		Tree *right;

	private:
		int data;
		int size;
		int level;

		void insert(int d, int lev);
		void buildNodeArray(Tree *t, std::vector<int> &arr);
};

Tree::Tree(int d, int l=0, Tree *parent=nullptr) : data(d), level(l), parent(parent) {
	size = 1;
	left = right = nullptr;
}

int Tree::getData() {
	return data;
}

void Tree::printTree() {
	if (this == nullptr) {
		printf("\n");
		return;
	}

	right->printTree();
	for (int i = 0; i < level; i++) {
		printf("\t");
	}
	printf("%d", data);
	left->printTree();
}

void Tree::insert(int d, int lev) {
	lev++;
	if (d <= data) {
		if (!left)
			left = new Tree(d, lev, this);
		else
			left->insert(d, lev);
	} else {
		if (!right)
			right = new Tree(d, lev, this);
		else
			right->insert(d, lev);
	}
	size++;
}

void Tree::insert(int d) {
	insert(d, level);
}

void Tree::buildNodeArray(Tree *t, std::vector<int> &arr) {
	if (!t)
		return;

	buildNodeArray(t->left, arr);
	arr.push_back(t->data);
	buildNodeArray(t->right, arr);
}

bool Tree::validateBST() {
	std::vector<int> node_arr;
	buildNodeArray(this, node_arr);
	std::vector<int>::iterator a = node_arr.begin();
	std::vector<int>::iterator b = node_arr.begin()+1;

	printf("{ ");
	for (auto i : node_arr) {
		printf("%d ", i);
	}
	printf("}\n");

	while (b != node_arr.end()) {
		if (*b < *a)
			return false;
		a++;
		b++;
	}
	return true;
}

int main() {
	Tree *t = new Tree(20);

	t->insert(10);
	t->insert(5);
	t->insert(3);
	t->insert(7);
	t->insert(6);
	t->insert(4);
	t->insert(15);
	t->insert(17);
	t->insert(18);
	t->insert(19);
	t->insert(20);
	t->insert(30);
	t->insert(25);
	t->insert(35);

	t->printTree();
	printf("\n");
	printf("Is t a BST? %s\n", t->validateBST() ? "yes" : "no");
	printf("\n");

	Tree *t2 = new Tree(20);
	t2->insert(10);
	t2->insert(30);
	t2->insert(5);
	t2->insert(1);
	t2->insert(15);
	t2->insert(25);
	t2->insert(35);

	t2->printTree();
	printf("\n");
	printf("Is t2 a BST? %s\n", t2->validateBST() ? "yes" : "no");
	printf("\n");

	Tree *t3 = new Tree(10);

	t3->right = new Tree(2, 1, t);
	t3->right->right = new Tree(3, 2, t);

	t3->left = new Tree(5, 1, t);
	t3->left->left = new Tree(17, 2, t3->left);
	t3->left->right = new Tree(3, 2, t3->left);
	t3->left->right->right = new Tree(7, 3, t3->left->right);

	t3->left->left->left = new Tree(-2, 3, t3->left->left);
	t3->left->left->right = new Tree(-3, 3, t3->left->left);

	t3->left->left->right->left = new Tree(10, 4, t3->left->left->right);
	t3->left->left->right->right = new Tree(7, 4, t3->left->left->right);

	t3->left->left->right->right->left = new Tree(-6, 5, t3->left->left->right->right);
	t3->left->left->right->right->right = new Tree(11, 5, t3->left->left->right->right);

	t3->left->left->right->right->left->left = new Tree(-15, 6, t3->left->left->right->right->left);
	t3->left->left->right->right->left->right = new Tree(5, 6, t3->left->left->right->right->left);

	t3->left->left->right->right->left->left->right = new Tree(-8, 7, t3->left->left->right->right->left->left);

	t3->printTree();
	printf("Is t3 a BST? %s\n", t3->validateBST() ? "yes" : "no");
	printf("\n");

	return 0;
}
