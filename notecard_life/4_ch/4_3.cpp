#include <stdio.h>
#include <vector>
#include <list>

class Tree {
	public:
		Tree(int d, int l, Tree *parent);
		int getData();
		void printTree(Tree *t);
		void insert(int d);
		Tree *findNode(int d);
		void listOfDepths(Tree *t, std::vector<std::list<int>> &lists);

		Tree *left;
		Tree *right;
		Tree *parent;

	private:
		int data;
		int size;
		int level;

		void insert(int d, int lev);
		void listOfDepths(Tree *t, std::vector<std::list<int>> &lists, int level);
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

void Tree::listOfDepths(Tree *t, std::vector<std::list<int>> &lists, int level) {
	if (!t) {
		return;
	}

	int v = t->getData();
	if (lists.size() == level) {
		std::list<int> li;
		li.push_back(v);
		lists.push_back(li);
	} else {
		lists[level].push_back(v);
	}

	listOfDepths(t->left, lists, level+1);
	listOfDepths(t->right, lists, level+1);
}

void Tree::listOfDepths(Tree *t, std::vector<std::list<int>> &lists) {
	listOfDepths(t, lists, 0);
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

	std::vector<std::list<int>> lists;

	t->listOfDepths(t, lists);

	for (auto l : lists) {
		printf("List: ");
		for (auto n : l) {
			printf("%d ", n);
		}
		printf("\n");
	}

	return 0;
}
