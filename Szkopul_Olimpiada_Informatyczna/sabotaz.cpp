#include <iostream>
#include <vector>

constexpr int max_n = 500'001;
int n, k;

int parent   [max_n];
int parent_to[max_n];

void load() {
    std::cin >> n >> k;

    for (int i = 2; i <= n; i++) {
        int x; std::cin >> x;
        parent[i] = x;
        parent_to[x]++;
    }
}

// rozmiar poddrzewa
int r[max_n];

void oblicz_rozmiary_poddrzew() {
    // wpychamy liscie do warstwy
    std::vector<int> W, nW;
    std::vector<int> signal(n + 1);

    for (int i = 1; i <= n; i++) {
        if (parent_to[i] == 0) {
            W.push_back(i);
            r[i] = 1;
        }
        signal[i] = parent_to[i];
    }

    while (W.size()) {
        for (auto v : W) {
            auto p = parent[v];
            r[p] += r[v];

            signal[p]--;
            if (!signal[p]) { // wszystkie dzieci odwiedzone
                r[p]++;       // dolicz siebie
                nW.push_back(p);
            }
        }

        std::swap(W, nW);
        nW.clear();
    }
}

// morale
double dp_morale[max_n];

void oblicz_morale() {
    for (int i = 1; i <= n; i++) {
        if (!parent_to[i]) dp_morale[i] = 1;
    }

    for (int i = n; i >= 2; i--) {
        dp_morale[parent[i]] = std::max(
            dp_morale[parent[i]],
            std::min(
                dp_morale[i],
                double(r[i]) / (r[parent[i]] - 1)
            )
        );
    }
}

// wzor na bunt: zbuntowani poddani / poddani
// poddani = rozmiar poddrzewa - 1

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);

    load();
    oblicz_rozmiary_poddrzew();
    oblicz_morale();

    double ans = 0;
    for (int i = 1; i <= n; i++) {
        if (r[i] > k) ans = std::max(dp_morale[i], ans);
    }

    std::cout.precision(10);
    std::cout << ans;
}
