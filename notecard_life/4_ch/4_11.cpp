#include <iostream>
#include <stdio.h>
#include <time.h>

class MyTree {
	public:
		MyTree(int d, int l, MyTree *parent);
		~MyTree() {};

		int getSize();
		int getData();
		int getLevel();
		void printTree(MyTree *t);

		void insert(int d);
		void remove();
		MyTree *find(int d);
		MyTree *getRandomNode();

		MyTree *right;
		MyTree *left;
		MyTree *parent;

	private:
		int data;
		int level;
		int size = 0;

		void __insert(int d, int level);
		MyTree *predecessor_descendant(MyTree *t);
		MyTree *successor_descendant(MyTree *t);
		void reduce_levels(MyTree *t);
		void reduce_parent_sizes(MyTree *t);
};

MyTree::MyTree(int d, int l=0, MyTree *parent=nullptr) : data(d), level(l), parent(parent) {
	size = 1;
	left = right = nullptr;
}

int MyTree::getSize() {
	return size;
}

int MyTree::getData() {
	return data;
}

int MyTree::getLevel() {
	return level;
}

void MyTree::printTree(MyTree *t) {
	if (!t) {
		printf("\n");
		return;
	}

	printTree(t->right);
	for (int i = 0; i < t->level; i++) {
		printf("\t");
	}
	printf("%d: %d %d", t->getData(), t->getSize(), t->getLevel());
	printTree(t->left);
}

void MyTree::__insert(int d, int lev) {
	lev++;

	if (d <= data) {
		if (!left) {
			left = new MyTree(d, lev, this);
		} else {
			left->__insert(d, lev);
		}
	} else {
		if (!right) {
			right = new MyTree(d, lev, this);
		} else {
			right->__insert(d, lev);
		}
	}

	size++;
}

void MyTree::insert(int d) {
	__insert(d, level);
}

MyTree *MyTree::predecessor_descendant(MyTree *t) {
	if (!t->left)
		return nullptr;

	t = t->left;
	while (t->right) {
		t = t->right;
	}

	return t;
}

MyTree *MyTree::successor_descendant(MyTree *t) {
	if (!t->right)
		return nullptr;

	t = t->right;
	while (t->left) {
		t = t->left;
	}

	return t;
}

void MyTree::reduce_levels(MyTree *t) {
	if (t) {
		reduce_levels(t->left);
		t->level--;
		reduce_levels(t->right);
	}
}

void MyTree::reduce_parent_sizes(MyTree *t) {
	while (t) {
		t->size--;
		t = t->parent;
	}
}

void MyTree::remove() {
	MyTree *p;

	// Case 1: Root Node
	if (!parent) {
		if (!left && !right) {
			delete this;
			return;
		}

		if (left) {
			p = predecessor_descendant(this);
		} else {
			p = successor_descendant(this);
		}
	} else {
		MyTree *child;
		if (!left || !right) {
			// There is <= 1 child, so try to find non-null child
			if (left) {
				child = left;
			} else {
				child = right;
			}

			reduce_levels(child);

			if (parent->left == this) {
				parent->left = child;
			} else {
				parent->right = child;
			}

			if (child) {
				child->parent = parent;
			}

			reduce_parent_sizes(parent);

			delete this;
			return;
		} else {
			// There are two children
			p = successor_descendant(this);
		}
	}

	data = p->getData();
	p->remove(); // this is the critical piece that ensures that sizes & levels are updated
}

MyTree *MyTree::find(int d) {
	if (d == data) {
		return this;
	} else if (d <= data) {
		return left != nullptr ? left->find(d) : nullptr;
	} else if (d > data) {
		return right != nullptr ? right->find(d) : nullptr;
	}

	return nullptr;
}

MyTree *MyTree::getRandomNode() {
	static int last_seed = time(nullptr);
	last_seed *= 2;

	srand(last_seed);

	int leftSize = left == nullptr ? 0 : left->getSize();

	int index = rand() % size;
	printf("index: %d\n", index);
	if (index < leftSize) {
		return left->getRandomNode();
	} else if (index == leftSize) {
		return this;
	} else {
		return right->getRandomNode();
	}
}

int main() {
	MyTree *t = new MyTree(20);

	t->insert(10);
	t->insert(5);
	t->insert(3);
	t->insert(7);
	t->insert(6);
	t->insert(15);
	t->insert(17);
	t->insert(30);
	t->insert(25);
	t->insert(35);

	t->printTree(t);
	printf("\n");

	printf("%d\n", t->getRandomNode()->getData());
	printf("%d\n", t->getRandomNode()->getData());
	printf("%d\n", t->getRandomNode()->getData());
	printf("%d\n", t->getRandomNode()->getData());
	printf("%d\n", t->getRandomNode()->getData());

	int r;
	std::cin >> r;

	MyTree *p;
	if ((p = t->find(r)) != nullptr) {
		p->remove();
	}

	t->printTree(t);

	return 0;
}
