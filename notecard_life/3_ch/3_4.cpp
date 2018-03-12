#include <stdio.h>

#include <list>

class MyQueue {
	public:
		MyQueue() {}
		void push(int d);
		int pop();

	private:
		std::list<int> push_stack;
		std::list<int> pop_stack;
};

void MyQueue::push(int d) {
	while (pop_stack.empty() == false) {
		push_stack.push_front(pop_stack.front());
		pop_stack.pop_front();
	}

	push_stack.push_front(d);
}

int MyQueue::pop() {
	while (push_stack.empty() == false) {
		pop_stack.push_front(push_stack.front());
		push_stack.pop_front();
	}

	if (pop_stack.empty()) {
		return -1;
	}

	int ret = pop_stack.front();
	pop_stack.pop_front();
	return ret;
}

int main() {
	MyQueue q;

	q.push(1);
	q.push(2);
	q.push(3);

	printf("Popping: %d\n", q.pop());
	printf("Popping: %d\n", q.pop());

	q.push(4);
	q.push(5);

	printf("Popping: %d\n", q.pop());
	printf("Popping: %d\n", q.pop());
	printf("Popping: %d\n", q.pop());

	q.push(6);
	printf("Popping: %d\n", q.pop());
}
