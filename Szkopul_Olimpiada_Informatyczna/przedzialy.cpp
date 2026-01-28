#include <iostream>
#include <algorithm>

struct granica {
    int  wartosc;
    bool poczatek;
};

bool operator<(const granica& l, const granica& r) {
    if (l.wartosc != r.wartosc) return l.wartosc < r.wartosc;
    return l.poczatek > r.poczatek; // niech poczatek = true, bedzie na poczatku
}

constexpr int max_n = 50000;
granica G[2 * max_n];

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    int n; std::cin >> n;

    for (int i = 0; i < n; i++) {
        int a, b; std::cin >> a >> b;
        G[2 * i]     = {a, true};
        G[2 * i + 1] = {b, false};
    }

    std::sort(G, G + 2 * n);

    int ongoing  = 0;
    int poczatek = 0;

    for (int i = 0; i < 2 * n; i++) {
        auto g = G[i];

        if (g.poczatek) {
            if (ongoing == 0) poczatek = g.wartosc;
            ongoing++;
        }
        else {
            ongoing--;
            if (ongoing == 0) {
                std::cout << poczatek << ' ' << g.wartosc << '\n';
            }
        }
    }
}
