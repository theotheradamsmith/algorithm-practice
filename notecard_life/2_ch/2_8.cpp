#include <stdio.h>
#include <iostream>
#include <algorithm>

#include <set>

#define N 5

struct ll {
	char c;
	struct ll *next;
};

struct ll *make_ll(char c) {
	struct ll *z = new struct ll;
	z->c = c;
	z->next = nullptr;
	return z;
}

struct ll *insert_after(struct ll *li, char c) {
	if (!li) {
		return make_ll(c);
	} else {
		li->next = make_ll(c);
		return li->next;
	}
}

void print_ll(struct ll *li) {
	while (li) {
		printf("%c ", li->c);
		li = li->next;
	}
	printf("\n");
}

struct ll *find_loop(struct ll *node) {
	std::set<struct ll *> node_set;

	while (node) {
		if (node_set.find(node) != node_set.end()) {
			return node;
		} else {
			node_set.insert(node);
			node = node->next;
		}
	}

	return nullptr;
}

int main(void) {
	struct ll *l = nullptr;
	struct ll *p;

	char chars[N] = {'a', 'b', 'c', 'd', 'e'};
	for (int i = 0; i < N; i++) {
		if (i == 0) {
			l = make_ll(chars[i]);
			p = l;
		} else {
			p = insert_after(p, chars[i]);
		}
	}

	print_ll(l);

	// Introduce a loop at 'c'
	p->next = l->next->next;

	p = find_loop(l);

	if (p) {
		printf("Loop detected beginning with node %p => %c\n", p, p->c);
	} else {
		printf("No loop detected\n");
	}

	return 0;
}
