#include <iostream>
#include <vector>
#include <algorithm>

using ull = unsigned long long;

const int max_n_m = 100000 + 5;

int              kolory[max_n_m];
std::vector<int> pozycje[max_n_m];
std::vector<ull> pref[max_n_m];

void czysc(int m) {
    for (int c = 1; c <= m; ++c) {
        pozycje[c].clear();
        pref[c].clear();
    }
}

void zestaw() {
    int n, m, q;
    std::cin >> n >> m >> q;

    czysc(m);

    for (int i = 1; i <= n; ++i) {
        std::cin >> kolory[i];
        pozycje[kolory[i]].push_back(i);
    }

    for (int c = 1; c <= m; ++c) {
        pref[c].push_back(0);
        for (int x : pozycje[c])
            pref[c].push_back(pref[c].back() + x);
    }

    for (int qi = 0; qi < q; ++qi) {
        int a, b;
        std::cin >> a >> b;

        std::vector<int>* Pa = &pozycje[a];
        std::vector<int>* Pb = &pozycje[b];

        if (Pb->size() < Pa->size()) {
            std::swap(Pa, Pb);
            std::swap(a, b);
        }

        const std::vector<ull>& preB = pref[b];
        ull total = 0;

        for (int x : *Pa) {
            int k = std::upper_bound(Pb->begin(), Pb->end(), x) - Pb->begin();
            total += (ull)x * k - preB[k] + (preB[Pb->size()] - preB[k]) - (ull)x * (Pb->size() - k);
        }

        std::cout << total << "\n";
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int Z; 
    std::cin >> Z;
    while (Z--) zestaw();
}
