#include <stdio.h>

int stackSize = 300;
int indexUsed = 0;
int stackPointer[3] = {-1, -1, -1};

class StackNode {
	public:
		StackNode(int p, int v) : previous(p), value(v) {}
		int previous;
		int value;
};

StackNode *buffer[900];

void push(int stackNum, int value) {
	int lastIndex = stackPointer[stackNum];
	stackPointer[stackNum] = indexUsed;
	indexUsed++;
	buffer[stackPointer[stackNum]] = new StackNode(lastIndex, value);
}

int pop(int stackNum) {
	int value = buffer[stackPointer[stackNum]]->value;
	int lastIndex = stackPointer[stackNum];
	stackPointer[stackNum] = buffer[stackPointer[stackNum]]->previous;
	buffer[lastIndex] = nullptr;
	indexUsed--;
	return value;
}

int peek(int stack) {
	return buffer[stackPointer[stack]]->value;
}

bool isEmpty(int stack) {
	return stackPointer[stack] == -1;
}
