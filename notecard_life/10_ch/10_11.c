#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRSIZE(arr) \
	((sizeof(arr)) / (sizeof(arr[0])))

static void swap(int *a, int *b) {
	*a ^= *b;
	*b ^= *a;
	*a ^= *b;
}

enum state {
	PEAK,
	VALLEY
};

void peakize(int arr[], int len) {
	enum state st = PEAK;

	int *p1 = arr;
	int *p2 = arr+1;

	for (int i = 1; i < len; i++) {
		if (st == PEAK) {
			if (*p1 < *p2) {
				swap(p1, p2);
			}

			st = VALLEY;
		} else if (st == VALLEY) {
			if (*p1 >= *p2) {
				swap(p1, p2);
			}

			st = PEAK;
		}

		p1++;
		p2++;
	}
}

static void print_array(int arr[], int len) {
	printf("{ ");
	for (int i = 0; i < len; i++) {
		printf("%d ", arr[i]);
	}
	printf("}");
}

static void test(int arr[], int len) {
	printf("Array: ");
	print_array(arr, len);
	printf(" => ");
	peakize(arr, len);
	print_array(arr, len);
	printf("\n");
}

int main(void) {
	int test1[] = {5, 3, 1, 2, 3};
	int test2[] = {5, 8, 6, 2, 3, 4, 6};
	int test3[30];

	srand(time(NULL));

	for (int i = 0; i < 30; i++) {
		test3[i] = rand() % 30 + 1;
	}

	test(test1, ARRSIZE(test1));
	test(test2, ARRSIZE(test2));
	test(test3, 30);

}
