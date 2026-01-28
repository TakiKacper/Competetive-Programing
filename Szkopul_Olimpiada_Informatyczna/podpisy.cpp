#include <iostream>
#include <vector>
#include <queue>
#include <bitset>

// okej czyli dowodcy tworza drzewa hierarchii
// odpowiedzia dla kazdego generala jest ilosc takich urzednikow co od nich tylko zaleza

// wypisujemy takich co maja tylko jednego generala posrednio
// czyli 

constexpr int max_n = 500;

// graf skierowany od generala, do urzednika, do urzednika, ..., po podpisach
std::vector<int> G[max_n];

// poreczenia dowodcow
int pG[max_n]; 

// dowodcy
std::vector<int> D;

std::bitset<max_n> visited;

void bfs(int d) {
    visited.reset();
    std::queue<int> Q; Q.push(d);

    while (Q.size()) {
        auto v = Q.front(); Q.pop();
        if (visited[v]) continue;
        visited[v] = true; pG[v]++;

        for (auto u : G[v]) {
            if (visited[u]) continue;
            Q.push(u);
        }
    }
}

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    int n; std::cin >> n; // liczba pracownikow <= 500

    for (int i = 0; i < n; i++) {
        int m; std::cin >> m;

        if (m == 0) {
            pG[i] = max_n;
            D.push_back(i);
        }

        for (int j = 0; j < m; j++) {
            int x; std::cin >> x; x--;
            G[x].push_back(i); // x porecza za i
        }
    }

    for (auto d : D) {
        bfs(d);
    }

    bool cos_wypisano = false;
    for (int i = 0; i < n; i++) {
        if (pG[i] <= 1) {
            std::cout << (i + 1) << '\n';
            cos_wypisano = true;
        }
    }

    if (!cos_wypisano) {
        std::cout << "BRAK\n";
    }
}
