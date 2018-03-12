#include <stdio.h>
#include <stdlib.h>

#include <vector>
#include <map>

class Tree {
	public:
		Tree(int d, int l, Tree *parent);
		int getSize();
		int getData();
		int getLevel();
		void printTree(Tree *t);
		void insert(int d);
		Tree *findNode(int d);

		void printPaths(Tree *t);
		void pathsWithSum(Tree *t, const int target, int &count);
		int betterPathsWithSum(Tree *t, const int target);

		Tree *left;
		Tree *right;
		Tree *parent;

	private:
		int data;
		int size;
		int level;

		void __insert(int d, int lev);
		void __printPaths(Tree *t, std::vector<int> &path_thus_far);
		void __pathsWithSum(Tree *t, const int target, int parent_sum, int &count);
		int __bpws(Tree *t, std::map<int, int> agg_sums, int target, int running_sum);
};

Tree::Tree(int d, int l=0, Tree *parent=nullptr) : parent(parent) {
	data = d;
	level = l;
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

void Tree::printPaths(Tree *t) {
	std::vector<int> path_thus_far;
	__printPaths(t, path_thus_far);
}

void Tree::__printPaths(Tree *t, std::vector<int> &path_thus_far) {
	if (!t) {
		for (auto p : path_thus_far) {
			printf("%d ", p);
		}
		printf("\n");
		return;
	}

	path_thus_far.push_back(t->data);

	if (t->left)
		__printPaths(t->left, path_thus_far);

	__printPaths(t->right, path_thus_far);

	path_thus_far.pop_back();
}

void Tree::__pathsWithSum(Tree *t, const int target, int parent_sum, int &count) {
	if (!t) {
		return;
	}

	if (parent_sum + t->data == target) {
		count++;
	}

	parent_sum += t->data;

	__pathsWithSum(t->left, target, parent_sum, count);
	__pathsWithSum(t->right, target, parent_sum, count);

}

void Tree::pathsWithSum(Tree *t, const int target, int &count) {
	if (!t)
		return;

	__pathsWithSum(t, target, 0, count);
	pathsWithSum(t->left, target, count);
	pathsWithSum(t->right, target, count);
}

int Tree::__bpws(Tree *t, std::map<int, int> agg_sums, int target, int running_sum) {
	if (!t)
		return 0;

	int count = 0;
	if ((running_sum += t->getData()) == target)
		count++;

	std::map<int, int>::iterator hashed_sum = agg_sums.find(running_sum);
	if (hashed_sum != agg_sums.end()) {
		hashed_sum->second++;
	} else {
		agg_sums.insert({running_sum, 1});
	}

	hashed_sum = agg_sums.find(running_sum - target);
	count += hashed_sum != agg_sums.end() ? hashed_sum->second : 0;
	count += __bpws(t->left, agg_sums, target, running_sum);
	count += __bpws(t->right, agg_sums, target, running_sum);
	agg_sums.erase(running_sum);
	return count;
}

int Tree::betterPathsWithSum(Tree *t, const int target) {
	std::map<int, int> agg_sums;
	return __bpws(t, agg_sums, target, 0);
}

int main() {
	Tree *t = new Tree(10);

	t->right = new Tree(2, 1, t);
	t->right->right = new Tree(3, 2, t);

	t->left = new Tree(5, 1, t);
	t->left->left = new Tree(17, 2, t->left);
	t->left->right = new Tree(3, 2, t->left);
	t->left->right->right = new Tree(7, 3, t->left->right);

	t->left->left->left = new Tree(-2, 3, t->left->left);
	t->left->left->right = new Tree(-3, 3, t->left->left);

	t->left->left->right->left = new Tree(10, 4, t->left->left->right);
	t->left->left->right->right = new Tree(7, 4, t->left->left->right);

	t->left->left->right->right->left = new Tree(-6, 5, t->left->left->right->right);
	t->left->left->right->right->right = new Tree(11, 5, t->left->left->right->right);

	t->left->left->right->right->left->left = new Tree(-15, 6, t->left->left->right->right->left);
	t->left->left->right->right->left->right = new Tree(5, 6, t->left->left->right->right->left);

	t->left->left->right->right->left->left->right = new Tree(-8, 7, t->left->left->right->right->left->left);

	t->printTree(t);

	printf("\nPaths\n");
	t->printPaths(t);

	int target = 15;
	int count = 0;

	t->pathsWithSum(t, target, count);

	printf("\n");
	printf("Paths With Sum %d: %d\n", target, count);
	printf("Cached Paths With Sum %d: %d\n", target, t->betterPathsWithSum(t, target));
	printf("\n");

	delete t;

	t = new Tree(50);

	srand(time(nullptr));

	for (int i = 0; i < 100000; i++) {
		t->insert(i % 5 == 0 ? -1 * (rand() % 100) : rand() % 100);
	}

	target = 30;
	count = 0;

	t->pathsWithSum(t, target, count);

	printf("\n");
	printf("Paths With Sum %d: %d\n", target, count);
	printf("Cached Paths With Sum %d: %d\n", target, t->betterPathsWithSum(t, target));
	printf("\n");

	return 0;
}

