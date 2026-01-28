#include <iostream>
#include <vector>
#include <set>

using ull = unsigned long long;

struct container {
    ull f_id_1 = 0, v_1 = 0;
    ull f_id_2 = 0, v_2 = 0;
};

int n;
ull k;

std::set<std::pair<ull, ull>> pairs;
std::vector<container>        containers;

void print() {
    if (containers.size() > n) {
        std::cout << "NIE\n";
        return;
    }

    std::cout << "TAK\n";

    for (auto& c : containers) {
        if (c.f_id_2 == 0) std::cout << "1 " << c.f_id_1 << ' ' << c.v_1 << '\n';
        else               std::cout << "2 " << c.f_id_1 << ' ' << c.v_1 << ' ' << c.f_id_2 << ' ' << c.v_2 << '\n';
    }

    while (n > containers.size()) {
        std::cout << "0\n"; n--;
    }
}

int main() {
    std::cin.tie(0);
    std::ios_base::sync_with_stdio(0);

    std::cin >> n >> k;

    for (int i = 0; i < n; i++) {
        ull a; std::cin >> a;
        pairs.insert({a, i + 1});
    }

    while (pairs.size()) {
        auto smallest = *pairs.begin();
        pairs.erase(pairs.begin());
        
        while (smallest.first >= k) {
            containers.push_back({smallest.second, k, 0, 0});
            smallest.first -= k;
        }

        if (smallest.first == 0) continue;

        // push rest + fill with part of the biggest amount
        if (pairs.size()) {
            auto biggest = *pairs.rbegin();
            pairs.erase(--pairs.end());

            ull taken = std::min(biggest.first, k - smallest.first);

            containers.push_back({
                smallest.second, smallest.first,
                biggest.second,  taken
            });

            biggest.first -= taken;
            if (biggest.first) pairs.insert(biggest);
        }
        // push rest
        else {
            containers.push_back({smallest.second, smallest.first, 0, 0});
        }
    }

    print();
}
