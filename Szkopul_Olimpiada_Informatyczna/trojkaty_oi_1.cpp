#include <iostream>
#include <vector>
#include <algorithm>

using ulamek = std::pair<int, int>;

// a <= b < c
bool trojkat(ulamek& a, ulamek& b, ulamek& c) {
    int ae = a.first * b.second * c.second;
    int be = b.first * a.second * c.second;
    int ce = c.first * a.second * b.second;

    return (ae + be > ce);
}

int main() {
    int n; std::cin >> n;
    std::vector<ulamek> boki(n);

    for (int i = 0; i < n; i++) {
        char c; std::cin >> boki[i].first >> c >> boki[i].second;
    }

    std::sort(boki.begin(), boki.end(), [](const ulamek& a, const ulamek& b) {
        int ae = a.first * b.second;
        int be = b.first * a.second;
        return ae < be;
    });
    
    auto a = boki[0];
    auto b = boki[1];
    auto c = boki[n - 1];

    std::cout << (trojkat(a, b, c) ? "TAK" : "NIE");
}
