#include <iostream>
#include <vector>
#include <algorithm>

using ull = unsigned long long;

constexpr int max_n = 5000 + 1;
constexpr int max_k = 1e6 + 1;
constexpr int inf   = __INT_MAX__;

// Globalne
int n, m, k; 

// Graf
std::vector<int> adj[max_n];

// Zapytania
struct zapytanie {
    int id;
    int s, t;
    ull d;
};

bool operator<(const zapytanie& l, const zapytanie& r) {
    return l.s < r.s;
}

zapytanie zap[max_k];

// Trawersja Grafu

struct dystans {
    int parzyst_dst     = inf;
    int nieparzysty_dst = inf;
};

std::vector<dystans> dystanse;

void bfs(int s) {
    for (int i = 0; i < n; i++) dystanse[i] = {};

    std::vector<int> q, nq;
    q.push_back(s);

    int tura = 0;

    while (q.size()) {
        for (int v : q) {
            for (int u : adj[v]) {
                int  nastepna = tura + 1;
                int& dstu     = (nastepna % 2) ? dystanse[u].nieparzysty_dst : dystanse[u].parzyst_dst;

                if (nastepna < dstu) {
                    dstu = nastepna;
                    nq.push_back(u);
                }
            }
        }

        tura++;

        q.swap(nq);
        nq.clear();
    }
}

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    std::cin >> n >> m >> k;

    for (int i = 0; i < m; i++) {
        int x0, x1; std::cin >> x0 >> x1; x0--; x1--;
        adj[x0].push_back(x1);
        adj[x1].push_back(x0);
    }
    dystanse.resize(n);

    for (int i = 0; i < k; i++) {
        std::cin >> zap[i].s >> zap[i].t; zap[i].s--; zap[i].t--;
        if (zap[i].s > zap[i].t) std::swap(zap[i].s, zap[i].t); // porzadek moze ograniczyc ilosc bfs'ow

        std::cin >> zap[i].d;
        zap[i].id = i;
    }
    std::vector<bool> odpowiedzi(k, false);
    std::sort(zap, zap + k);

    int obecny_start_bfs = -1;
    for (int i = 0; i < k; i++) {
        if (zap[i].s != obecny_start_bfs) {
            obecny_start_bfs = zap[i].s;
            bfs(obecny_start_bfs);
        }

        bool opowiesc_parzysta = (zap[i].d % 2 == 0);

        auto& dst               = dystanse[zap[i].t];
        ull   minimalny_dystans = (opowiesc_parzysta ? dst.parzyst_dst : dst.nieparzysty_dst);

        odpowiedzi[zap[i].id] = (
            minimalny_dystans != inf && 
            minimalny_dystans <= zap[i].d &&
            ((zap[i].d - minimalny_dystans) % 2 == 0)
        );
    }

    for (int i = 0; i < k; i++) std::cout << (odpowiedzi[i] ? "TAK\n" : "NIE\n");
}
