#include <stdio.h>
#include <stdlib.h>

class Tree {
	public:
		Tree(int d, int l, Tree *parent);
		void printTree();
		void insert(int d);
		int getData();
		bool isBalanced();

		Tree *parent;
		Tree *left;
		Tree *right;

	private:
		int data;
		int size;
		int level;

		void insert(int d, int lev);
		int checkHeight(Tree *t);
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

int Tree::checkHeight(Tree *t) {
	if (!t)
		return 0;

	int left_height = checkHeight(t->left);
	if (left_height == -1)
		return -1;

	int right_height = checkHeight(t->right);
	if (right_height == -1)
		return -1;

	if (abs(left_height - right_height) > 1)
		return -1;
	else
		return (left_height > right_height ? left_height + 1 : right_height + 1);
}

bool Tree::isBalanced() {
	return checkHeight(this) == -1 ? false : true;
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

	printf("Is tree balanced? %s\n", t->isBalanced() ? "yes" : "no");
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
	printf("Is tree2 balanced? %s\n", t2->isBalanced() ? "yes" : "no");
	printf("\n");



	return 0;
}
