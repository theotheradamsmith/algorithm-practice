#include <stdio.h>
#include <string.h>

bool isSubstring(const char *s1, const char *s2) {
	if (strlen(s1) != strlen(s2))
		return false;

	const char *s1p = s1;

	while (*s1p && *s1p != *s2) {
		s1p++;
	}

	if (!(*s1p))
		return false;

	while (*s1p) {
		if (*s1p != *s2)
			return false;

		s1p++;
		s2++;
	}

	while (*s2) {
		if (*s1 != *s2)
			return false;

		s1++;
		s2++;
	}

	return true;
}

int main() {
	const char *str1 = "waterbottle";
	const char *str2 = "erbottlewat";

	printf("Is %s a rotation of %s? %s\n", str1, str2, isSubstring(str1, str2) ? "yes" : "no");
	printf("Is %s a rotation of %s? %s\n", str2, str1, isSubstring(str2, str1) ? "yes" : "no");

	str1 = "bilbobaggins";
	str2 = "bagginsbalbo";

	printf("Is %s a rotation of %s? %s\n", str1, str2, isSubstring(str1, str2) ? "yes" : "no");
	printf("Is %s a rotation of %s? %s\n", str2, str1, isSubstring(str2, str1) ? "yes" : "no");
}
