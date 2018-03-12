#include <list>
#include <stdio.h>

void handle_carry(int &s, int &c) {
	if (s >= 10) {
		s = s % 10;
		c = 1;
	} else {
		c = 0;
	}
}

std::list<int> sumlist(std::list<int> a, std::list<int> b) {
	std::list<int> res;

	std::list<int>::iterator ait = a.begin();
	std::list<int>::iterator bit = b.begin();

	int s;
	int carry = 0;

	while (ait != a.end() && bit != b.end()) {
		s = (*ait) + (*bit) + carry;
		handle_carry(s, carry);
		res.push_back(s);
		ait++;
		bit++;
	}

	if (ait != a.end()) {
		while (ait != a.end()) {
			s = *ait + carry;
			handle_carry(s, carry);
			res.push_back(s);
			ait++;
		}
	} else {
		while (bit != b.end()) {
			s = *bit + carry;
			handle_carry(s, carry);
			res.push_back(s);
			bit++;
		}
	}

	if (carry)
		res.push_back(carry);

	return res;
}

int main() {
	std::list<int> a;
	a.push_back(7);
	a.push_back(1);
	a.push_back(6);

	std::list<int> b;
	b.push_back(5);
	b.push_back(9);
	b.push_back(2);

	std::list<int> sum = sumlist(a, b);

	for (auto i : sum) {
		printf("%d ", i);
	}

	printf("\n");
}
