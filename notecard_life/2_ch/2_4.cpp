#include <stdio.h>

#define N 7

struct ll {
	int d;
	struct ll *next;
};

struct ll *make_ll(int d) {
	struct ll *z = new struct ll;
	z->d = d;
	z->next = nullptr;
	return z;
}

struct ll *insert_after(struct ll *li, int d) {
	if (!li) {
		return make_ll(d);
	} else {
		li->next = make_ll(d);
		return li->next;
	}
}

void print_ll(struct ll *li) {
	while (li) {
		printf("%d ", li->d);
		li = li->next;
	}
	printf("\n");
}

struct ll *partition(struct ll *input, int x) {
}

int main() {
	struct ll *l = nullptr;
	struct ll *p;

	int nums[N] = {3, 5, 8, 5, 10, 2, 1};
	for (int i = 0; i < N; i++) {
		if (i == 0) {
			l = make_ll(nums[i]);
			p = l;
		} else {
			p = insert_after(p, nums[i]);
		}
	}

	int x = 5;

	l = partition(l, x);

	print_ll(l);
}
