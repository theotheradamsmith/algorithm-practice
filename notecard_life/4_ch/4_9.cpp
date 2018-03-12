#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <queue>

#define DEBUG 1

class Tree {
	public:
		Tree(int d, int l, Tree *parent);
		void printTree();
		void insert(int d);
		int getData();
		void printBSTSequences();

		Tree *parent;
		Tree *left;
		Tree *right;

	private:
		int data;
		int size;
		int level;

		void insert(int d, int lev);
		void buildNodeArrays(Tree *t, std::vector<std::vector<int>> &arr);
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

void Tree::buildNodeArrays(Tree *t, std::vector<std::vector<int>> &arr) {
	std::queue<Tree *> q;
	Tree *p;
	q.push(t);

	while (!q.empty()) {
		p = q.front();
		q.pop();
		if (p->left)
			q.push(p->left);
		if (p->right)
			q.push(p->right);
		if (arr.size() <= p->level)
			arr.resize(p->level+1);
		arr[p->level].push_back(p->data);
	}
}

void Tree::printBSTSequences() {
	std::vector<std::vector<int>> arr;
	buildNodeArrays(this, arr);

	if (DEBUG) {
		for (auto a : arr) {
			printf("{ ");
			for (auto i : a) {
				printf("%d ", i);
			}
			printf(" }\n");
		}
	}

	std::vector<std::vector<int>> answers;

	for (int i = 0; i < arr.size(); i++) {
		std::vector<int> new_answer = arr[0];
		answers.push_back(new_answer);
	}

	if (DEBUG) {
		for (auto a : answers) {
			printf("{ ");
			for (auto i : a) {
				printf("%d ", i);
			}
			printf(" }\n");
		}
	}
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
	t->printBSTSequences();
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
	t2->printBSTSequences();
	printf("\n");

	Tree *t3 = new Tree(2);
	t3->insert(1);
	t3->insert(3);

	t3->printTree();
	printf("\n");
	t3->printBSTSequences();
	printf("\n");

	return 0;
}
