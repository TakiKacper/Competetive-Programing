#include <iostream>
#include <vector>
#include <queue>
#include <deque>

// chcemy znalesc najtanszy cykl [zloto - metal - zloto]
// zeby najmniej zaplacic za przejscie i clo

constexpr int max_n = 5001;
constexpr int max_m = 100'001;
int n, m;

struct krawedz {
    int  u;
    uint k;
};

// graf transformacji
std::vector<krawedz> G[max_n];

// odwrotny graf transformacji
std::vector<krawedz> H[max_n];

uint clo[max_n]; // cło dla danego metalu

int koszt_ze_zlota[max_n];
int koszt_do_zlota[max_n];

struct djk_thread {
    uint k;
    int  v;
};

bool operator<(const djk_thread& a, const djk_thread& b) {
    return a.k > b.k;
}

void djk(std::vector<krawedz>* adj, int* koszty) {
    std::priority_queue<djk_thread, std::deque<djk_thread>> Q;
    Q.push({0, 1});

    while (Q.size()) {
        auto dt = Q.top(); Q.pop();
    
        if (koszty[dt.v] < dt.k) continue;
        koszty[dt.v] = dt.k;
        
        for (auto krw : adj[dt.v]) {
            uint nowy_koszt = dt.k + krw.k;
            if (koszty[krw.u] <= nowy_koszt) continue;
            koszty[krw.u] = nowy_koszt;
            Q.push({nowy_koszt, krw.u});
        }
    }
}

void load() {
    std::cin >> n; // metale

    for (int i = 1; i <= n; i++) {
        std::cin >> clo[i];
        koszt_ze_zlota [i] = __INT_MAX__;
        koszt_do_zlota [i] = __INT_MAX__;
    }
    
    std::cin >> m; // reakcje
    for (int i = 0; i < m; i++) {
        int a, b; uint k; std::cin >> a >> b >> k;
        G[a].push_back({b, k});
        H[b].push_back({a, k});
    }
}

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    load();

    // pierwsza djk zloto -> metal
    djk(G, koszt_ze_zlota);

    // druga djk metal -> zloto
    djk(H, koszt_do_zlota);

    uint koszt = __INT_MAX__;
    for (int i = 1; i <= n; i++) {
        uint k = koszt_ze_zlota[i] + (clo[i] / 2) + koszt_do_zlota[i];
        koszt = std::min(koszt, k);
    }

    std::cout << koszt;
}
