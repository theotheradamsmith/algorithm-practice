#include <stdio.h>

#define N 5

void execute_rotations_c(char m[N][N], int n, int i, int d) {
	char t = m[d][i];
	m[d][i] = m[i][n-1];
	m[i][n-1] = m[n-1][n-1+d-i];
	m[n-1][n-1+d-i] = m[n-1+d-i][d];
	m[n-1+d-i][d] = t;
}

void rotate_char_matrix(char m[N][N]) {
	int __N = N;
	int row = 0;
	int depth = 0;

	while (__N - 1 > 1) {
		for (int i = row; i < __N - 1; ++i) {
			execute_rotations_c(m, __N, i, depth);
		}
		depth++;
		row++;
		__N--;
	}
}

void execute_rotations_i(int m[N][N], int n, int i, int d) {
	char t = m[d][i];
	m[d][i] = m[i][n-1];
	m[i][n-1] = m[n-1][n-1+d-i];
	m[n-1][n-1+d-i] = m[n-1+d-i][d];
	m[n-1+d-i][d] = t;
}

void rotate_int_matrix(int m[N][N]) {
	int __N = N;
	int row = 0;
	int depth = 0;

	while (__N - 1 > 1) {
		for (int i = row; i < __N - 1; ++i) {
			execute_rotations_i(m, __N, i, depth);
		}
		depth++;
		row++;
		__N--;
	}
}

void print_matrix_c(char m[N][N]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%c ", m[i][j]);
		}
		printf("\n");
	}
}

void print_matrix_i(int m[N][N]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%d ", m[i][j]);
		}
		printf("\n");
	}
}

int main(void) {
	char carr[N][N] = {
		{'a', 'b', 'c', 'd', 'e'},
		{'f', 'g', 'h', 'i', 'j'},
		{'k', 'l', 'm', 'n', 'o'},
		{'p', 'q', 'r', 's', 't'},
		{'u', 'v', 'w', 'x', 'y'}
	};

	int iarr[N][N] = {
		{10, 11, 12, 13, 14},
		{15, 16, 17, 18, 19},
		{20, 21, 22, 23, 24},
		{25, 26, 27, 28, 29},
		{30, 31, 32, 33, 34}
	};

	print_matrix_c(carr);
	printf("\n");
	rotate_char_matrix(carr);
	print_matrix_c(carr);
	printf("\n");
	printf("\n");
	print_matrix_i(iarr);
	printf("\n");
	rotate_int_matrix(iarr);
	print_matrix_i(iarr);
}
