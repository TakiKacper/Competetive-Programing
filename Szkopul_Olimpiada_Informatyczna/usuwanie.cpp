#include <bits/stdc++.h>

using namespace std;

int main()
{
	uint64_t a, b;
	std::cin >> a >> b;

	uint64_t count = b - a + 1;

	uint64_t even = count / 2;
	uint64_t non_even = count / 2;

	if (a % 2 == 0 && b % 2 == 0)
		even++;
	else if (a % 2 == 1 && b % 2 == 1)
		non_even++;

	cout << even - (even % 2) + non_even - (non_even % 2);
}
