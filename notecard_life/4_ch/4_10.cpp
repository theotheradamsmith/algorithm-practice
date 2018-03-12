#include <stdio.h>

class Tree {
	public:
		Tree(int d, int l, Tree *parent);
		int getData();
		void printTree(Tree *t);
		void insert(int d);
		Tree *findNode(int d);
		bool checkSubtree(Tree *a, Tree *b);

		Tree *left;
		Tree *right;
		Tree *parent;

	private:
		int data;
		int size;
		int level;

		void insert(int d, int lev);
		bool check_for_parity(Tree *a, Tree *b);
};

Tree::Tree(int d, int l=0, Tree *parent=nullptr) : data(d), level(l), parent(parent) {
	size = 1;
	left = right = nullptr;
}

int Tree::getData() {
	return data;
}

void Tree::printTree(Tree *t) {
	if (!t) {
		printf("\n");
		return;
	}

	printTree(t->right);
	for (int i = 0; i < t->level; i++) {
		printf("\t");
	}
	printf("%d", t->data);
	printTree(t->left);
}

void Tree::insert(int d) {
	insert(d, level);
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

Tree *Tree::findNode(int d) {
	if (d == data) {
		return this;
	} else if (d <= data) {
		return left != nullptr ? left->findNode(d) : nullptr;
	} else if (d > data) {
		return right != nullptr ? right->findNode(d) : nullptr;
	}

	return nullptr;
}

bool Tree::check_for_parity(Tree *a, Tree *b) {
	if (!a && !b) {
		return true;
	} else if (!a || !b) {
		return false;
	} else if (a->data != b->data) {
		return false;
	} else {
		return (check_for_parity(a->left, b->left) && check_for_parity(a->right, b->right));
	}
}

bool Tree::checkSubtree(Tree *a, Tree *b) {
	if (!b)
		return true;
	if (!a)
		return false;

	if (a->data == b->data && check_for_parity(a, b))
		return true;

	return (checkSubtree(a->left, b) || checkSubtree(a->right, b));
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

	t->printTree(t);
	printf("\n");

	Tree *a = t->findNode(10);
	Tree *b = t->findNode(20);

	printf("Is Node %d a subtree of Node %d? %s\n", b->getData(), a->getData(), a->checkSubtree(a, b) ? "yes" : "no");

	return 0;
}
