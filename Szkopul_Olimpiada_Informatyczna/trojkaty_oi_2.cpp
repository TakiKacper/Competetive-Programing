#include <iostream>
#include <vector>
#include <algorithm>

// budowa trojkata: a + b > c jezeli posortowane to a + c > b i b + c > a za darmo

int main() {
    std::vector<unsigned long long> set;

    while (set.size() < 45) {
        unsigned long long length;
        std::cin >> length;
        if (length == 0) break;
        set.push_back(length);
    }

    if (set.size() < 3) {
        std::cout << "NIE"; return 0;
    }

    std::sort(set.begin(), set.end());
    
    for (int i = 0; i + 2 < set.size(); i++) {
        auto a = set[i];
        auto b = set[i + 1];
        auto c = set[i + 2];

        if (a + b > c) {
            std::cout << a << ' ' << b << ' ' << c << '\n';
            return 0;
        }
    }

    std::cout << "NIE" << '\n';

    return 0;
}
