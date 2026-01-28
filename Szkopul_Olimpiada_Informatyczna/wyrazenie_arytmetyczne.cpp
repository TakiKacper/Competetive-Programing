#include <iostream>
#include <cmath>
#include <climits>

using ull = unsigned long long;

ull a, b, c;
ull lowest[1000001];

inline void solve(ull n) {
    ull inc_low = ULLONG_MAX;
    ull mul_low = ULLONG_MAX;

    for (ull i = 1; i < n; i++) {
        auto add_left  = i;
        auto add_right = n - i;

        inc_low = std::min(inc_low, lowest[add_left] + lowest[add_right] + b);

        if (n % i == 0 && i != 1) {
            auto mul_left  = i;
            auto mul_right = (n / i);
        
            mul_low = std::min(mul_low, lowest[mul_left] + lowest[mul_right] + c);
        }
    }

    lowest[n] = std::min(inc_low, mul_low);
}

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
	std::cin.exceptions(std::cin.failbit);

    ull n; std::cin >> n;
    std::cin >> a >> b >> c;

    lowest[0] = 0;
    lowest[1] = a;

    std::cout << lowest[1] << ' ';

    for (ull i = 2; i <= n; i++) {
        solve(i);
        std::cout << lowest[i] << ' ';
    }
}
