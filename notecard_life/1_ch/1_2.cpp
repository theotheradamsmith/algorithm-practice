#include <stdio.h>
#include <string.h>

bool perm(const char *a, const char *b) {
	if (strlen(a) != strlen(b)) {
		return false;
	}

	int hash1[256] = {0};
	int hash2[256] = {0};

	while (*a) {
		hash1[*a]++;
		a++;
	}

	while (*b) {
		hash2[*b]++;
		b++;
	}

	for (int i = 0; i < 256; i++) {
		if (hash1[i] != hash2[i]) {
			return false;
		}
	}

	return true;
}

int main() {
	const char *a = "abcdcdc";
	const char *b = "cdacbdc";

	printf("Permutations? %s\n", perm(a, b) ? "yes" : "no");
}
