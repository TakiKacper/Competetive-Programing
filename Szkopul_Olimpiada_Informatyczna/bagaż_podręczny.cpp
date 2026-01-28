#include <iostream>
#include <climits>
#include <algorithm>

using ull = unsigned long long;

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin.exceptions(std::cin.failbit);

    ull n; std::cin >> n;
    ull bA = ULLONG_MAX, bB = ULLONG_MAX, bC = ULLONG_MAX;

    while (n--) {
        ull A[3];
        std::cin >> A[0] >> A[1] >> A[2];
        
        std::sort(A, A + 3);

        bA = std::min(A[0], bA);
        bB = std::min(A[1], bB);
        bC = std::min(A[2], bC);
    }

    std::cout << bA * bB * bC;
}
