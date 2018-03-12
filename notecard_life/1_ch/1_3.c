#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void urlify(char *s, int truelen) {
	int org_idx = truelen - 1;
	int fin_idx = strlen(s) - 1;

	while (org_idx >= 0) {
		if (s[org_idx] == ' ') {
			s[fin_idx--] = '0';
			s[fin_idx--] = '2';
			s[fin_idx--] = '%';
			org_idx--;
		} else {
			s[fin_idx--] = s[org_idx--];
		}
	}
}

int main(void) {
	char *str = strdup(" Mr John Smith      ");

	printf("%s urlified => ", str);
	urlify(str, 14);
	printf("%s\n", str);

	free(str);

	return 0;
}
