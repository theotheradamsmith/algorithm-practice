/**
 * Langton's Ant
 *
 * An ant is sitting on an infinite grid of white and black squares. It initially faces right.
 * At each step, it does the following:
 *   1) At a white square, flip the color of the square, turn 90 degrees right (clockwise),
 *      and move forward one unit.
 *   2) At a black square, flip the color of the square, turn 90 degrees left (counter-clockwise),
 *      and move forward one unit.
 *
 * Write a program to simulate the first K moves that the ant makes and print the final board as a
 * grid. Note that you are not provided with the data structure to represent the grid. This is
 * something you must design yourself. The only input to your method is K. You should print
 * the final grid and return nothing.
 *
 * The method signature might be something like:
 * void printKMoves(int K).
 */

#include <unordered_map>

#include <stdio.h>
#include <stdlib.h>

#define DEBUG 0

enum facing_direction {
	NORTH,
	EAST,
	SOUTH,
	WEST
};

struct position {
	int row_col[2];
	bool color;
};

struct pair_hash {
	template <class T1, class T2>
	std::size_t operator () (const std::pair<T1,T2> &p) const {
		auto h1 = std::hash<T1>{}(p.first);
		auto h2 = std::hash<T2>{}(p.second);
		return h1 ^ h2;
	}
};

using Unordered_map = std::unordered_map<std::pair<int, int>, struct position *, pair_hash>;

struct position *create_position(int row, int col) {
	struct position *z = new position;
	z->row_col[0] = row;
	z->row_col[1] = col;
	z->color = true;
	return z;
}

static void turn_clockwise(enum facing_direction &direction) {
	switch (direction) {
		case NORTH:
			direction = EAST;
			break;
		case EAST:
			direction = SOUTH;
			break;
		case SOUTH:
			direction = WEST;
			break;
		case WEST:
			direction = NORTH;
			break;
		default:
			abort();
	}
}

static void turn_widdershins(enum facing_direction &direction) {
	switch (direction) {
		case NORTH:
			direction = WEST;
			break;
		case EAST:
			direction = NORTH;
			break;
		case SOUTH:
			direction = EAST;
			break;
		case WEST:
			direction = SOUTH;
			break;
		default:
			abort();
	}
}

static void determine_new_direction(enum facing_direction &direction, bool new_color) {
	// flipping from white to black?
	if (new_color) {
		turn_clockwise(direction);
	} else {
		turn_widdershins(direction);
	}
}

static void determine_shifts(int &row_shift, int &col_shift, const enum facing_direction direction) {
	switch (direction) {
		case NORTH:
			row_shift = -1;
			col_shift = 0;
			break;
		case EAST:
			row_shift = 0;
			col_shift = 1;
			break;
		case SOUTH:
			row_shift = 1;
			col_shift = 0;
			break;
		case WEST:
			row_shift = 0;
			col_shift = -1;
			break;
		default:
			abort();
	}
}

static void execute_moves(int K, Unordered_map &coords, int &total_rows, int &total_cols,
				   int &row_offset, int &col_offset) {
	int lowest_row = 0, lowest_col = 0;
	int highest_row = 0, highest_col = 0;

	// execute initial move
	int row = 0, col = 0, move = 0;
	std::pair<int, int> loc (row, col);

	if (DEBUG)
		printf("Creating new coordinates for move %d at row %d col %d\n", move, row, col);

	struct position *new_square = create_position(row, col);
	coords[loc] = new_square;

	enum facing_direction ant_faces = EAST;

	int row_shift, col_shift;
	determine_shifts(row_shift, col_shift, ant_faces);

	while (++move <= K) {
		row += row_shift;
		col += col_shift;

		if (row < lowest_row)
			lowest_row = row;
		else if (row > highest_row)
			highest_row = row;

		if (col < lowest_col)
			lowest_col = col;
		else if (col > highest_col)
			highest_col = col;

		loc = std::make_pair(row, col);
		auto search = coords.find(loc);

		if (search != coords.end()) {
			if (DEBUG)
				printf("Found coordinates for move %d at row %d col %d\n", move, row, col);
			search->second->color = !search->second->color;
			determine_new_direction(ant_faces, search->second->color);
		} else {
			if (DEBUG)
				printf("Creating new coordinates for move %d at row %d col %d\n", move, row, col);

			new_square = create_position(row, col);

			coords[loc] = new_square;
			determine_new_direction(ant_faces, new_square->color);
		}

		determine_shifts(row_shift, col_shift, ant_faces);
	}

	// Now let's just shift all coordinates in our map and adjust the position structures
	total_rows = 1 + highest_row - lowest_row;
	total_cols = 1 + highest_col - lowest_col;

	// we need to bump all coordinates up by the absolute value of the lowest values
	row_offset = abs(lowest_row);
	col_offset = abs(lowest_col);
}

static void print_board(Unordered_map coords, int rows, int cols, int row_offset, int col_offset) {
	bool board[rows][cols];
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			board[i][j] = false;
		}
	}

	for (auto iter = coords.begin(); iter != coords.end(); ++iter) {
		if (DEBUG) {
			printf("(%d, %d => %s)\n", iter->second->row_col[0], iter->second->row_col[1],
				iter->second->color ? "black" : "white");
		}
		iter->second->row_col[0] += row_offset;
		iter->second->row_col[1] += col_offset;

		board[iter->second->row_col[0]][iter->second->row_col[1]] = iter->second->color;
	}

	printf("\n");
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			printf("%s", board[i][j] ? "#" : "_");
		}
		printf("\n");
	}
	printf("\n");
}

void printKMoves(int K) {
	if (DEBUG)
		printf("printKMoves received %d as argument\n", K);

	Unordered_map coords;
	int rows, cols, row_offset, col_offset;

	execute_moves(K, coords, rows, cols, row_offset, col_offset);

	print_board(coords, rows, cols, row_offset, col_offset);
}

int main(int argc, char **argv) {
	if (argc != 2) {
		printf("Must enter number of steps for ant to take, K, as integer.\n");
		exit(1);
	}

	printKMoves(atoi(argv[1]));

	return 0;
}

