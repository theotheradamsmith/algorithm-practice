#include <stdio.h>
#include <stdlib.h>

#define N 8

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

struct ll *return_intersection(struct ll *a, struct ll *b) {
	if (!a || !b) {
		return nullptr;
	}

	struct ll *ap = a;
	struct ll *bp = b;
	int alen = 1;
	int blen = 1;

	while (ap->next) {
		alen++;
		ap = ap->next;
	}

	while (bp->next) {
		blen++;
		bp = bp->next;
	}

	if (ap != bp) {
		return nullptr;
	}

	int diff = abs(alen - blen);

	ap = a;
	bp = b;

	if (alen > blen) {
		for (int i = 0; i < diff; i++) {
			ap = ap->next;
		}
	} else {
		for (int i = 0; i < diff; i++) {
			bp = bp->next;
		}
	}

	while (ap != bp) {
		ap = ap->next;
		bp = bp->next;
	}

	return ap;
}

int main() {
	struct ll *l1 = nullptr;
	struct ll *p1;

	int nums[N] = {2, 2, 1, 2, 5, 10, 2, 1};
	for (int i = 0; i < N; i++) {
		if (i == 0) {
			l1 = make_ll(nums[i]);
			p1 = l1;
		} else {
			p1 = insert_after(p1, nums[i]);
		}
	}

	p1 = l1;
	for (int i = 0; i < 4; i++) {
		p1 = p1->next;
	}

	struct ll *l2 = make_ll(4);
	l2->next = p1;

	struct ll *l3 = make_ll(3);

	printf("L1: ");
	print_ll(l1);
	printf("L2: ");
	print_ll(l2);

	struct ll *intersecting_node = return_intersection(l2, l1);

	if (intersecting_node) {
		printf("Intersection value: %d\n", intersecting_node->d);
	} else {
		printf("No intersection\n");
	}


}
