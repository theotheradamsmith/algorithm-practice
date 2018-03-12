#include <unordered_set>

#include <stdio.h>

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

struct ll *remove_dups(struct ll *input) {
	std::unordered_set<int> map;

	struct ll *lp = input;
	struct ll *next = input->next;
	map.insert(lp->d);

	while (next) {
		while (next && map.find(next->d) != map.end()) {
			struct ll *temp = next->next;
			delete next;
			next = temp;
		}

		lp->next = next;

		if (next) {
			map.insert(next->d);
			lp = next;
			next = next->next;
		}
	}

	return input;
}

int main() {
	struct ll *l = nullptr;
	struct ll *p;

	int nums[N] = {2, 2, 1, 2, 5, 10, 2, 1};
	for (int i = 0; i < N; i++) {
		if (i == 0) {
			l = make_ll(nums[i]);
			p = l;
		} else {
			p = insert_after(p, nums[i]);
		}
	}

	l = remove_dups(l);

	print_ll(l);
}
