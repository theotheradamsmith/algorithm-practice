#include <stdio.h>

unsigned long long nfact(size_t n) {
	if (n <= 0) return 1;
	unsigned long long s = n;
	while (--n) s *= n;
	return s;
}

unsigned long long pnk(size_t n, size_t k) {
	size_t d = (k < n) ? n - k : 1;
	return nfact(n) / nfact(d);
}

void prnarray(int *a, size_t sz) {
	size_t i;
	for (i = 0; i < sz; i++) {
		printf(" %2d", a[i]);
	}
	printf("\n");
}

void swap(int *x, int *y) {
	int temp = *x;
	*x = *y;
	*y = temp;
}

void permute(int *a, size_t i, size_t n) {
	size_t j;
	if (i == n)
		prnarray(a, n);
	else
		for (j = i; j < n; j++) {
			if (*(a+i) != *(a+j)) {
				swap((a+i), (a+j));
			}
			permute(a, i+1, n);
			if (*(a+i) != *(a+j)) {
				swap((a+i), (a+j));
			}
		}
}

int main(void) {
	int test[] = {1, 2, 3};
	size_t sz = sizeof(test)/sizeof(test[0]);

	unsigned long long p = pnk(sz, sz);
	printf("Total permutations: %llu\n", p);

	printf("Permutations:\n");
	permute(test, 0, sz);
	printf("\n");

	return 0;
}
