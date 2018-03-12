#include <stdio.h>

#define M 4
#define N 5

void print_matrix_i(int m[M][N]) {
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			printf("%d ", m[i][j]);
		}
		printf("\n");
	}
}

static void nullifyRow(int matrix[M][N], int row) {
	for (int col = 0; col < N; col++) {
		matrix[row][col] = 0;
	}
}

static void nullifyCol(int matrix[M][N], int col) {
	for (int row = 0; row < M; row++) {
		matrix[row][col] = 0;
	}
}

void zeroize(int matrix[M][N]) {
	bool rowHasZero = false;
	bool colHasZero = false;

	int row, col;

	for (row = 0; row < M; row++) {
		if (matrix[row][0] == 0) {
			colHasZero = true;
			break;
		}
	}

	for (col = 0; col < N; col++) {
		if (matrix[0][col] == 0) {
			rowHasZero = true;
			break;
		}
	}

	for (row = 1; row < M; row++) {
		for (col = 1; col < N; col++) {
			if (matrix[row][col] == 0) {
				matrix[row][0] = 0;
				matrix[0][col] = 0;
			}
		}
	}

	for (row = 1; row < M; row++) {
		if (matrix[row][0] == 0) {
			nullifyRow(matrix, row);
		}
	}

	for (col = 1; col < N; col++) {
		if (matrix[0][col] == 0) {
			nullifyCol(matrix, col);
		}
	}

	if (rowHasZero) {
		nullifyRow(matrix, 0);
	}

	if (colHasZero) {
		nullifyCol(matrix, 0);
	}
}

int main() {
	int matrix[M][N] = {
		{1, 1, 1, 1, 1},
		{1, 1, 1, 1, 0},
		{1, 0, 1, 1, 1},
		{1, 1, 1, 1, 1}
	};

	printf("Matrix Before Transformation:\n");
	print_matrix_i(matrix);
	printf("\n");
	printf("Matrix After Transformation:\n");
	zeroize(matrix);
	print_matrix_i(matrix);
	return 0;
}
