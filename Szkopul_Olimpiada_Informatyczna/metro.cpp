#include <iostream>
#include <vector>
#include <set>

constexpr int max_n = 1'000'001;
std::vector<int> adj[max_n];

bool visited[max_n];
int  signals[max_n];

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    int n, l; std::cin >> n >> l;

    for (int i = 0; i < n - 1; i++) {
        int x0, x1; std::cin >> x0 >> x1;
        adj[x0].push_back(x1);
        adj[x1].push_back(x0);
    }

    int wynik = 0;
    std::set<int> W, nW; // warstwa, nowa warstwa

    // wepchnij liscie
    for (int i = 1; i <= n; i++) if (adj[i].size() == 1) W.insert(i);

    while (W.size()) {
        wynik += std::min(2 * l, (int)W.size()); // z danej warstwy wybieramy maksymalnie 2 l wierzcholkow

        for (auto v : W) visited[v] = true;
        for (auto v : W) {
            for (auto u : adj[v]) {
                if (visited[u]) continue;
                signals[u]++;

                // jezeli wszystkie dzieci danego wezla juz byly
                // zglos wezel
                if (signals[u] >= adj[u].size() - 1) {
                    nW.insert(u);
                }
            }
        }

        std::swap(W, nW);
        nW.clear();
    }

    std::cout << wynik;
}
