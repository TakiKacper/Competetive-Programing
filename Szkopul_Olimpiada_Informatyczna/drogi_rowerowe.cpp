#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

// 1) znajdz odwrotny graf silnie spojnych skladowych   (kosaraju)
// 2) pósc dfs na powstałym grafie i zliczaj wierzholki (dfs)

constexpr int max_n = 50'000;
constexpr int max_m = 100'000;
int n, m;

std::vector<int>    G[max_n]; // graf z zadania
std::vector<int>    R[max_n]; // graf odwrocony
std::pair<int, int> E[max_m]; // krawedzie z zadania

std::vector<int>    S[max_n];  // graf silnie spojnych skladowych
int                 IN[max_n]; // in-degree w grafie S

int s_itr = 0;          // ilosc silnie spojnych skladowych
int ver_to_SSS[max_n];  // wiercholek a jego silnie spojna skladowa
int SSS_size[max_n];    // silnie spojna skladowa a jej wiercholki

int SSS_ans[max_n];     // odpowiedz dla SSS

std::vector<int> order; // kosaraju temp
bool vis[max_n];        // temp

void kosaraju_dfs_1(int v) {
    vis[v] = true;
    for (auto c : G[v]) if (!vis[c]) kosaraju_dfs_1(c);

    order.push_back(v);
}

void kosaraju_dfs_2(int v) {
    vis[v] = true;
    for (auto c : R[v]) if (!vis[c]) kosaraju_dfs_2(c);

    ver_to_SSS[v] = s_itr;
    SSS_size[s_itr]++;
}

void answer_dfs(int v) {
    vis[v] = true;

    for (auto c : S[v]) {
        if (!vis[c]) answer_dfs(c);
        SSS_ans[v] += SSS_ans[c];
    }

    SSS_ans[v] += SSS_size[v];
}

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);

    // Ładowanie
    std::cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int x0, x1; std::cin >> x0 >> x1; x0--; x1--;
        G[x0].push_back(x1);
        R[x1].push_back(x0);
        E[i] = {x0, x1};
    }

    // Korasaju
    for (int i = 0; i < n; i++) {
        if (vis[i]) continue;
        kosaraju_dfs_1(i);
    }

    memset(vis, false, sizeof(vis));
    for (auto itr = order.rbegin(); itr != order.rend(); itr++) {
        int v = *itr;
        if (vis[v]) continue;
        kosaraju_dfs_2(v);
        s_itr++;
    }

    // Wytwarzanie grafu SSS
    for (int i = 0; i < m; i++) {
        auto e = E[i];

        int x0 = ver_to_SSS[e.first];
        int x1 = ver_to_SSS[e.second];

        if (x0 == x1) continue;
        S[x0].push_back(x1);
        IN[x0]++;
    }

    // Kasowanie krawedzi wielokrotnych
    for (int i = 0; i < s_itr; i++) {
        auto last = std::unique(S[i].begin(), S[i].end());
        S[i].erase(last, S[i].end());
    }

    // Generuj Odpowiedzi
    memset(vis, false, sizeof(vis));
    for (int i = 0; i < s_itr; i++) {
        if (vis[i]) continue;
        answer_dfs(i);
    }

    // Odpowiadanie
    for (int i = 0; i < n; i++) {
        int s = ver_to_SSS[i];
        int ans = SSS_ans[s] - 1;
        std::cout << ans << '\n';
    }
}
