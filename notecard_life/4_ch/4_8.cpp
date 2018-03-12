#include <stdio.h>

class Tree {
	public:
		Tree(int d, int l, Tree *parent);
		int getSize();
		int getData();
		int getLevel();
		void printTree(Tree *t);
		void insert(int d);
		Tree *findCommonAncestor(Tree *t1, Tree *t2);
		Tree *findNode(int d);

		Tree *left;
		Tree *right;
		Tree *parent;

	private:
		int data;
		int size;
		int level;

		void __insert(int d, int lev);
};

Tree::Tree(int d, int l=0, Tree *parent=nullptr) : data(d), level(l), parent(parent) {
	size = 1;
	left = right = nullptr;
}

int Tree::getSize() {
	return size;
}

int Tree::getData() {
	return data;
}

int Tree::getLevel() {
	return level;
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

void Tree::__insert(int d, int lev) {
	lev++;
	if (d <= data) {
		if (!left) {
			left = new Tree(d, lev, this);
		} else {
			left->__insert(d, lev);
		}
	} else {
		if (!right) {
			right = new Tree(d, lev, this);
		} else {
			right->__insert(d, lev);
		}
	}

	size++;
}

void Tree::insert(int d) {
	__insert(d, level);
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

Tree *Tree::findCommonAncestor(Tree *a, Tree *b) {
	int alevel = a->level;
	int blevel = b->level;

	if (alevel > blevel) {
		while (alevel != blevel) {
			a = a->parent;
			alevel--;
		}
	} else {
		while (blevel != alevel) {
			b = b->parent;
			blevel--;
		}
	}

	while (a && b && a != b) {
		a = a->parent;
		b = b->parent;
	}

	if (a)
		return a;

	return nullptr;
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

	Tree *a = t->findNode(4);

	Tree *b = t->findNode(19);

	Tree *ca = t->findCommonAncestor(a, b);

	printf("Common ancestor of %d & %d => ", a->getData(), b->getData());
	ca ? printf("%d\n", ca->getData()) : printf("None\n");

	Tree *t2 = new Tree(40);

	ca = t->findCommonAncestor(a, t2);
	printf("Common ancestor of %d & %d => ", a->getData(), t2->getData());
	ca ? printf("%d\n", ca->getData()) : printf("None\n");

	return 0;
}
