#define _GNU_SOURCE

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int calc_digits(int c) {
	int ret = 1;
	while (c / 10 > 0) {
		ret++;
		c /= 10;
	}

	return ret;
}

char *compress(char *input) {
	char *output = calloc(1, strlen(input)+1);

	char *p = input;
	char *op = output;
	char *lastuniq = input;

	int max_allowed_index = strlen(input)-1;

	int count = 0, op_index = 0, digits = 0;

	while (*p) {
		if (op_index > max_allowed_index) {
			goto abort_and_copy_input;
		}

		if (*p == *lastuniq) {
			count++;
			p++;
			continue;
		}

		*op = *lastuniq;
		op++;
		op_index++;
		if (op_index > max_allowed_index) {
			goto abort_and_copy_input;
		}
		sprintf(op, "%d", count);
		digits = calc_digits(count);
		op += digits;
		op_index += digits;

		lastuniq = p;
		count = 0;
	}

	if (op_index > max_allowed_index) {
		goto abort_and_copy_input;
	}

	*op = *lastuniq;

	op++;
	op_index++;
	if (op_index > max_allowed_index) {
		goto abort_and_copy_input;
	}

	sprintf(op, "%d", count);
	digits = calc_digits(count);
	op_index += digits;
	op += digits;
	op[op_index] = '\0';

	return output;

abort_and_copy_input:
	free(output);

	output = strdup(input);

	return output;
}

int main(void) {
	char *t1 = "aabcccccaaa";
	char *t1out = compress(t1);

	printf("%s => %s\n", t1, t1out);

	char *t2 = "a";
	char *t2out = compress(t2);

	printf("%s => %s\n", t2, t2out);

	free(t1out);
	free(t2out);
}
