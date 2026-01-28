#include <iostream>
#include <set>

int main() {
    std::cin.tie(0);
    std::ios_base::sync_with_stdio(0);

    int w, n; // 200, 30 000
    std::cin >> w >> n;

    // posortowane malejaca
    std::multiset<int, std::greater<int>> S;

    for (int i = 0; i < n; i++) {
        int x; std::cin >> x;
        S.insert(x);
    }
  
    // liczba kajakow
    int K = 0;

    // usadzamy najciezszych, z innym najciezszym mozliwym
    while (S.size()) {
        // bierzemy najciezszego
        auto itr = S.begin();
        int w1 = *(itr); S.erase(itr);
        int wr = w - w1;

        // szukamy najciezkiego do pary
        // <= wr, z definicji lower bound
        itr = S.lower_bound(wr);

        // znalaz sie taki, jego tez bierzemy
        if (itr != S.end()) S.erase(itr);

        K++;
    }

    std::cout << K;
}
