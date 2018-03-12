#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool one_away(const char *a, const char *b) {
	int lena = strlen(a);
	int lenb = strlen(b);
	if (abs(lena - lenb) > 1) {
		return false;
	}

	bool found_diff = false;

	while (*a && *b) {
		if (*a == *b) {
			a++;
			b++;
		} else {
			if (found_diff) {
				return false;
			}

			found_diff = true;
			if (lena > lenb) {
				a++;
			} else if (lenb > lena) {
				b++;
			} else {
				a++;
				b++;
			}
		}
	}

	while (*a) {
		if (found_diff) {
			return false;
		} else {
			found_diff = true;
			a++;
		}
	}

	while (*b) {
		if (found_diff) {
			return false;
		} else {
			found_diff = true;
			b++;
		}
	}

	return true;
}

int main(void) {
	const char *pairs[] = {
		"pale", "ple",
		"pales", "pale",
		"apales", "apalea",
		"pale", "bale",
		"pale", "bake",
		"paler", "bak",
		"ler", "aler",
	};

	for (int i = 0; i < sizeof(pairs)/sizeof(pairs[0]); i += 2) {
		printf("One away? %s : %s => %s\n",
			pairs[i], pairs[i+1], one_away(pairs[i], pairs[i+1]) ? "yes" : "no");
	}

	return 0;
}
