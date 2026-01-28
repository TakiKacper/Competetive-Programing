#include <iostream>
#include <vector>

constexpr int max_n = 50001;
constexpr int max_z = 100001;

// index pary, gdzie zolnierz pojawia sie po raz pierwszy
// index zwiekszony o jeden, zeby 0 oznaczalo brak pary
int pierwsza_para[max_z];

// graf polaczenia par, krawedz <=> wspolny zolniez
std::vector<int> adj[max_n];

// czy para odwiedzona przez bfs
bool vis[max_n];

// okresla w jakiej roli zolniez o danej wysokosci juz wystapil
// 0 -> nie zbadano
// 1 -> na dole
// 2 -> na gorze
int zolniez_przeszlosc[max_z];

int gora[max_n];
int dol[max_n];

int bfs(int vp) {
    // zakladamy w przejsciu ze ulozenie pierwszej pary jest niezmienone
    zolniez_przeszlosc[dol[vp]]  = 1;
    zolniez_przeszlosc[gora[vp]] = 2;

    // lecimy bfs po kolejnych parach
    std::vector<int> q, nq;
    for (auto v : adj[vp]) q.push_back(v);

    int odwroty = 0;
    int pary    = 1;
    vis[vp] = true;

    while (q.size()) {
        for (auto v : q) {
            if (vis[v]) continue;
            vis[v] = true; pary++;

            // czy znamy przeszlosc gornego?
            if (zolniez_przeszlosc[gora[v]]) {
                // jezeli w przeszlosci byl na gorze, teraz musi byc na dole -> odwracamy
                if (zolniez_przeszlosc[gora[v]] == 2) {
                    std::swap(gora[v], dol[v]);
                    odwroty++;
                }
            }

            // czy znamy przeszlosc dolnego?
            if (zolniez_przeszlosc[dol[v]]) {
                // jezeli w przeszlosci byl na dole, teraz musi byc na gorze -> odwracamy
                if (zolniez_przeszlosc[dol[v]] == 1) {
                    std::swap(gora[v], dol[v]);
                    odwroty++;
                }
            }

            zolniez_przeszlosc[dol[v]]  = 1;
            zolniez_przeszlosc[gora[v]] = 2;

            for (auto u : adj[v]) {
                if (vis[u]) continue;
                nq.push_back(u);
            }
        }

        q.swap(nq);
        nq.clear();
    }

    return std::min(odwroty, pary - odwroty);
}

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);

    // ladujemy dane
    int n; std::cin >> n;
    for (int i = 0; i < n; i++) std::cin >> gora[i];
    for (int i = 0; i < n; i++) std::cin >> dol[i];

    // lacz pary, ktore 
    for (int i = 0; i < n; i++) {
        int g = gora[i];

        // ten zolniez jescze nie wystapil
        if (pierwsza_para[g] == 0) {
            pierwsza_para[g] = i + 1;
        }
        // juz wystapil wczesniej, laczymy pary
        else {
            adj[pierwsza_para[g] - 1].push_back(i);
            adj[i].push_back(pierwsza_para[g] - 1);
        }

        int d = dol[i];

        // ten zolniez jescze nie wystapil
        if (pierwsza_para[d] == 0) {
            pierwsza_para[d] = i + 1;
        }
        // juz wystapil wczesniej, laczymy pary
        else {
            adj[pierwsza_para[d] - 1].push_back(i);
            adj[i].push_back(pierwsza_para[d] - 1);
        }
    }

    // idziemy po kolejnych grafach par, i tak je obracamy 
    // zeby grafy w podgrafie spelnialy warunek
    int wynik = 0;
    for (int i = 0; i < n; i++) {
        if (vis[i]) continue;
        wynik += bfs(i);
    }

    std::cout << wynik;
}
