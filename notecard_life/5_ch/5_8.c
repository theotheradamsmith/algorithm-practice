#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define HEIGHT 8
#define WIDTH 32

#define X1 2
#define X2 23
#define Y  4

#define DEBUG 1
#define debug_print(fmt, ...) \
	do { if (DEBUG) fprintf(stderr, "%s:%d:%s(): " fmt, __FILE__, \
							__LINE__, __func__, __VA_ARGS__); } while (0)

#define BYTE_TO_BINARY_PATTERN ("%c%c%c%c%c%c%c%c")
#define BYTE_TO_BINARY(byte) \
	(byte & 0x80 ? 'O' : '-'), \
	(byte & 0x40 ? 'O' : '-'), \
	(byte & 0x20 ? 'O' : '-'), \
	(byte & 0x10 ? 'O' : '-'), \
	(byte & 0x08 ? 'O' : '-'), \
	(byte & 0x04 ? 'O' : '-'), \
	(byte & 0x02 ? 'O' : '-'), \
	(byte & 0x01 ? 'O' : '-')

void draw_line(uint8_t screen[], int len, int width, int x1, int x2, int y) {
	debug_print("Drawing a line from (%d,%d) to (%d,%d)\n\n", x1, y, x2, y);

	int start_offset = x1 % 8;
	int first_full_byte = x1 / 8;
	if (start_offset != 0) {
		first_full_byte++;
	}

	int end_offset = x2 % 8;
	int last_full_byte = x2 / 8;
	if (end_offset != 7) {
		last_full_byte--;
	}

	debug_print("start_offset:%d\n", start_offset);
	debug_print("first_full_byte:%d\n", first_full_byte);
	debug_print("end_offset:%d\n", end_offset);
	debug_print("last_full_byte:%d\n", last_full_byte);

	// Set full bytes
	for (int b = first_full_byte; b <= last_full_byte; b++) {
		int byte = (width / 8) * y + b;
		debug_print("\tFilling in byte %d\n", byte);
		screen[byte] = (uint8_t)0xFF;
	}

	// Create masks for start and end of line
	uint8_t start_mask = (uint8_t) (0xFF >> start_offset);
	uint8_t end_mask = (uint8_t) ~(0xFF >> (end_offset + 1));

	if (DEBUG) {
		printf("start_mask: \t");
		printf(BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(start_mask));
		printf("\nend_mask: \t");
		printf(BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(end_mask));
		printf("\n");
	}

	// Set start and end of line
	if ((x1 / 8) == (x2 / 8)) { // x1 and x2 are in the same byte
		uint8_t mask = (uint8_t) (start_mask & end_mask);
		if (DEBUG) {
			printf("mask: \t");
			printf(BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(mask));
			printf("\n");
		}
		screen[(width / 8) * y + (x1 / 8)] |= mask;
	} else {
		if (start_offset != 0) {
			int byte_number = (width / 8) * y + first_full_byte - 1;
			screen[byte_number] |= start_mask;
		}
		if (end_offset != 7) {
			int byte_number = (width / 8) * y + last_full_byte + 1;
			screen[byte_number] |= end_mask;
		}
	}

	debug_print("%s", "\n");
}

void print_screen(uint8_t screen[], int len, int width) {
	debug_print("%s", "Printing\n");
	for (int i = 0; i < len; i += width/8) {
		for (int j = 0; j < width/8; j++) {
			printf(BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(screen[i+j]));
		}
		printf("\n");
	}
}

int main(void) {
	uint8_t screen[HEIGHT*WIDTH] = {0};

	draw_line(screen, HEIGHT*(WIDTH/8), WIDTH, X1, X2, Y);
	print_screen(screen, HEIGHT*(WIDTH/8), WIDTH);

	return 0;
}
