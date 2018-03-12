#include <stdbool.h>
#include <stdio.h>

#define STACKSIZE 300
#define NUMSTACKS 3

struct array_stack {
	int buffer[STACKSIZE * NUMSTACKS];
	int stack_pointer[NUMSTACKS];
};

void init(struct array_stack *as) {
	for (int i = 0; i < STACKSIZE; i++) {
		as->buffer[i] = 0;
	}

	for (int i = 0; i < NUMSTACKS; i++) {
		as->stack_pointer[i] = 0;
	}
}

void push(struct array_stack *as, int stack_num, int value) {
	int index = stack_num * STACKSIZE + as->stack_pointer[stack_num] + 1;
	as->stack_pointer[stack_num]++;
	as->buffer[index] = value;
}

int pop(struct array_stack *as, int stack_num) {
	int index = stack_num * STACKSIZE + as->stack_pointer[stack_num];
	as->stack_pointer[stack_num]--;
	int value = as->buffer[index];
	as->buffer[index] = 0;
	return value;
}

int peek(struct array_stack as, int stack_num) {
	int index = stack_num * STACKSIZE + as.stack_pointer[stack_num];
	return as.buffer[index];
}

bool empty(struct array_stack as, int stack_num) {
	return as.stack_pointer[stack_num] == 0;
}

int main(void) {
	struct array_stack s;
	init(&s);

	printf("Is my new stack empty?\n");
	printf("1: %s, 2: %s, 3: %s\n",
		empty(s, 1) ? "yes" : "no",
		empty(s, 2) ? "yes" : "no",
		empty(s, 3) ? "yes" : "no");

	push(&s, 1, 10);
	push(&s, 2, 20);

	printf("Is my new stack empty?\n");
	printf("1: %s, 2: %s, 3: %s\n",
		empty(s, 1) ? "yes" : "no",
		empty(s, 2) ? "yes" : "no",
		empty(s, 3) ? "yes" : "no");

	printf("Popping %d from stack 2\n", pop(&s, 2));

	printf("Is my new stack empty?\n");
	printf("1: %s, 2: %s, 3: %s\n",
		empty(s, 1) ? "yes" : "no",
		empty(s, 2) ? "yes" : "no",
		empty(s, 3) ? "yes" : "no");

	printf("Top of stack1: %d\n", peek(s, 1));

	return 0;
}
