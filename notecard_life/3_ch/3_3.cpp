#include <list>
#include <vector>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

class SubStack {
	public:
		SubStack(int cap);
		bool empty();
		void push(int n);
		int pop();
		int getSize();
		bool atCap();
		void print();

	private:
		int cap;
		int size;
		std::list<int> stack;
};

SubStack::SubStack(int cap) : cap(cap) {
	size = 0;
};

bool SubStack::atCap() {
	return size == cap;
}

int SubStack::getSize() {
	return size;
}

bool SubStack::empty() {
	return size == 0;
}

void SubStack::print() {
	for (auto i : stack) {
		printf("%d ", i);
	}
}

void SubStack::push(int n) {
	if (size < cap) {
		stack.push_front(n);
		size++;
	} else {
		printf("No push!\n");
	}
}

int SubStack::pop() {
	if (size > 0) {
		int top = stack.front();
		stack.pop_front();
		size--;
		return top;
	} else {
		printf("No poppy!\n");
		abort();
	}
}

void test_substack() {
	SubStack s(5);

	for (int i = 1; i < 6; i++) {
		s.push(i);
		s.print();
		printf("\n");
	}

	s.push(6);
	s.print();
	printf("\n");

	printf("Popping %d\n", s.pop());
	s.print();
	printf("\n");

	printf("Popping %d\n", s.pop());
	s.print();
	printf("\n");

	s.push(6);
	s.print();
	printf("\n");

	printf("Popping %d\n", s.pop());
	s.print();
	printf("\n");

	printf("Popping %d\n", s.pop());
	s.print();
	printf("\n");

	s.push(7);
	s.print();
	printf("\n");

	for (int i = 0; i < 6; i++) {
		if (!s.empty()) {
			printf("Popping %d\n", s.pop());
			s.print();
			printf("\n");
		}
	}

	s.push(8);
	s.print();
	printf("\n");
	s.push(9);
	s.print();
	printf("\n");
}

class SetOfStacks {
	public:
		SetOfStacks(int cap);
		bool empty();
		void push(int n);
		int pop();
		int getNumStacks();
		int popStackAt(int index);
		void printStacks();

	private:
		int substack_cap;
		int insertion_idx;
		int size;
		int num_stacks;
		std::vector<SubStack> substacks;
};

SetOfStacks::SetOfStacks(int cap) : substack_cap(cap) {
	size = 0;
	insertion_idx = 0;
	num_stacks = 1;
	substacks.push_back(SubStack(cap));
}

bool SetOfStacks::empty() {
	if (size == 0) {
		assert(substacks[0].empty());
	}

	return size == 0;
}

int SetOfStacks::getNumStacks() {
	return num_stacks;
}

void SetOfStacks::push(int n) {
	if (substacks[insertion_idx].atCap()) {
		insertion_idx++;
		num_stacks++;
		substacks.push_back(SubStack(substack_cap));
	}

	substacks[insertion_idx].push(n);
	size++;
}

int SetOfStacks::pop() {
	if (!empty()) {
		size--;
		if (substacks[insertion_idx].getSize() == 0) {
			insertion_idx--;
			num_stacks--;
			substacks.pop_back();
			return substacks[insertion_idx].pop();
		}

		return substacks[insertion_idx].pop();
	} else {
		abort();
	}
}

int SetOfStacks::popStackAt(int index) {
	assert(index <= insertion_idx);

	int ret_val = substacks[index].pop();
	size--;

	std::list<int> tempstack;
	for (int i = index+1; i <= insertion_idx; i++) {
		while (!substacks[i].empty()) {
			tempstack.push_front(substacks[i].pop());
		}
		substacks[i-1].push(tempstack.front());
		tempstack.pop_front();
		while(!tempstack.empty()) {
			substacks[i].push(tempstack.front());
			tempstack.pop_front();
		}
	}

	return ret_val;
}

void SetOfStacks::printStacks() {
	int i = 1;
	for (auto s : substacks) {
		printf("Substack %d\n", i++);
		s.print();
		printf("\n");
	}
}

void test_SoS() {
	SetOfStacks s(5);

	for (int i = 0; i < 18; i++) {
		s.push(i);
	}

	s.printStacks();
	printf("\n");

	printf("Pop Stack At 1: %d\n", s.popStackAt(1));

	s.printStacks();
	printf("\n");

	for (int i = 0; i < 11; i++) {
		printf("Popping: %d\n", s.pop());
	}

	s.printStacks();
	printf("\n");

	for (int i = 6; i < 12; i++) {
		s.push(i*10);
	}

	s.printStacks();
	printf("\n");

	while (!s.empty()) {
		printf("Popping: %d\n", s.pop());
	}
}

int main() {
	//test_substack();
	test_SoS();
}
