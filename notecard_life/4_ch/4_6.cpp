#include <stdio.h>

class Tree {
	public:
		Tree(int d, int l, Tree *parent);

		Tree *parent;
		Tree *left;
		Tree *right;

		int getData();
		void insert(int d);
		void printTree();
		Tree *findNode(int d);
		Tree *findSuccessor(Tree *node);

	private:
		int data;
		int size;
		int level;

		void insert(int d, int level);
		void find_smallest_node_to_right(Tree *n, Tree **smallest);
};

Tree::Tree(int d, int l=0, Tree *parent=nullptr) : data(d), level(l), parent(parent) {
	size = 1;
	left = right = nullptr;
}

int Tree::getData() {
	return data;
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

Tree *Tree::findNode(int d) {
	if (d == data)
		return this;
	else if (d <= data)
		return left ? left->findNode(d) : nullptr;
	else if (d > data)
		return right ? right->findNode(d) : nullptr;

	return nullptr;
}

void Tree::find_smallest_node_to_right(Tree *n, Tree **smallest) {
	if (!n)
		return;

	if (n->data < (*smallest)->data) {
		*smallest = n;
	}

	find_smallest_node_to_right(n->left, smallest);
}

Tree *Tree::findSuccessor(Tree *node) {
	if (!node)
		return nullptr;

	Tree *p;
	if (!node->right) {
		p = node->parent;
		while (p && p->data < node->data) {
			p = p->parent;
		}

		return (!p ? nullptr : p);
	}

	p = node->right;
	find_smallest_node_to_right(node->right, &p);

	return p;
}

int main() {
	Tree *t = new Tree(10);
	t->insert(5);
	t->insert(3);
	t->insert(7);
	t->insert(1);
	t->insert(4);
	t->insert(6);
	t->insert(9);
	t->insert(0);
	t->insert(2);
	t->insert(8);
	t->insert(15);
	t->insert(20);
	t->insert(16);
	t->insert(17);
	t->insert(25);

	t->printTree();

	Tree *p;
	for (int i = 0; i < 26; i++) {
		printf("%d => ", i);
		if ((p = t->findSuccessor(t->findNode(i))))
			printf("%d", p->getData());
		else
			printf("None.");

		printf("\n");
	}

	printf("\n");

	return 0;
}
