#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool perm_of_pal(const char *str) {
	int count[256];
	for (int i = 0; i < 256; ++i) {
		count[i] = 0;
	}

	int actual_letters = 0;
	const char *p = str;
	while (*p) {
		if (!(*p == ' ')) {
			count[tolower(*p)]++;
			actual_letters++;
		}

		p++;
	}

	bool abao = false;

	if (actual_letters % 2 == 0) {
		for (int i = 0; i < 256; ++i) {
			if (count[i] % 2 != 0) {
				return false;
			}
		}
	} else {
		for (int i = 0; i < 256; ++i) {
			if (count[i] % 2 != 0) {
				if (abao) {
					return false;
				} else {
					abao = true;
				}
			}
		}
	}

	return true;
}

int main(void) {
	const char *input1 = "Tact Coa";
	const char *input2 = "Taco Co";
	const char *input3 = "Tact C";
	const char *input4 = "Tact Ac";
	const char *input5 = "tact coa";

	printf("%s perm of a pal? %s\n", input1, perm_of_pal(input1) ? "Yes" : "No");
	printf("%s perm of a pal? %s\n", input2, perm_of_pal(input2) ? "Yes" : "No");
	printf("%s perm of a pal? %s\n", input3, perm_of_pal(input3) ? "Yes" : "No");
	printf("%s perm of a pal? %s\n", input4, perm_of_pal(input4) ? "Yes" : "No");
	printf("%s perm of a pal? %s\n", input5, perm_of_pal(input5) ? "Yes" : "No");
}
