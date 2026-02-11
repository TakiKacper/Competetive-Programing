#include <iostream>
#include <vector>

using ull = unsigned long long;

constexpr ull mod   = 1000000007;
constexpr int max_n = 1e6 + 1;

// graf(y) polaczen miedzy zawodnikiami
// polacznenie oznacza wspolne proponowane pole
std::vector<int> adj[max_n];

// czy wiercholek byl wizytowany w bfs
bool vis[max_n];

// pole jest na pewno w uzyciu
int pole_zajete_przez[max_n];

// dla danego zawodnika, przypisane pole, na pewno
int odpowiedzi[max_n];

// zawodnicy proponowani na danym polu
std::vector<int> prop_pole[max_n];

// pierwsza dostepna zawodnikowi pozycja
int poz_1[max_n];

// druga dostepna zawodnikowi pozycja
int poz_2[max_n];

// zwraca true jezeli sprzeczny
bool bfs(int v1) {
    // w tym momencie znamy jakie pole zajmuje v1
    // mozliwe znamy rowniez odpowiedzi dla innych skladowych grafu
    // jezeli wypadnie, ze dwaj zawodnicy powinni byc na tym samym miejscu, mamy sprzecznosc

    // pary [wiercholek, poprzedni]
    std::vector<std::pair<int, int>> q, nq;
    
    for (auto v : adj[v1]) q.push_back({v, v1});
    vis[v1] = true;

    while (q.size()) {
        for (auto v : q) {
            if (vis[v.first]) continue;
            vis[v.first] = true;

            // wiemy ze niemozemy byc w tej samej pozycji co poprzedni
            // probujemy wiec zajac drugie dostepne nam miejsce
            auto alt = (odpowiedzi[v.second] != poz_1[v.first] ? poz_1[v.first] : poz_2[v.first]);

            // jezeli nie ma drugiego dostepnego miejsca
            // mamy sprzecznosc
            if (alt == 0) return true;
            
            // jezeli to drugie miejsce juz jest zajete
            // nie mamy zadnych opcji, wiec sprzeczonsc
            if (pole_zajete_przez[alt] && pole_zajete_przez[alt] != v.first) return true;

            // inaczej zajmujemy drugie pole
            odpowiedzi[v.first] = alt;
            pole_zajete_przez[alt] = v.first;

            // i lecimy dalej
            for (auto u : adj[v.first]) {
                if (vis[u]) continue;
                nq.push_back({u, v.first});
            }
        }

        q.swap(nq);
        nq.clear();
    }

    return false;
}

int main() {
    std::cin.tie(0);
    std::ios_base::sync_with_stdio(0);
    
    std::vector<int> pewni;

    // zaladuj dane
    int n; std::cin >> n;
    for (int z = 1; z <= n; z++) {
        char p; std::cin >> p;

        if (p == 'T') {
            int x0; std::cin >> x0;

            // polacz wszystkich innych zawodnikow
            for (auto oz : prop_pole[x0]) {
                adj[oz].push_back(z);
                adj[z].push_back(oz);
            }

            prop_pole[x0].push_back(z);

            // zajete, a tu jest na pewno? sprzecznosc!
            if (pole_zajete_przez[x0]) {
                std::cout << "NIE\n0";
                return 0;
            }

            poz_1[z] = x0;

            pole_zajete_przez[x0] = z;
            odpowiedzi[z]   = x0;

            pewni.push_back(z);
        }
        else {
            int x0, x1; std::cin >> x0 >> x1;

            poz_1[z] = x0;
            poz_2[z] = x1;
            
            for (auto oz : prop_pole[x0]) {
                adj[oz].push_back(z);
                adj[z].push_back(oz);
            }
            prop_pole[x0].push_back(z);

            for (auto oz : prop_pole[x1]) {
                adj[oz].push_back(z);
                adj[z].push_back(oz);
            }
            prop_pole[x1].push_back(z);
        }
    }

    // badamy grafy wychodzac od pewnikow
    // badajac graf moze nam wyjsc sprzecznosc!
    for (auto pew : pewni) {
        if (vis[pew]) continue;
        bool sprzeczny = bfs(pew);

        if (sprzeczny) {
            std::cout << "NIE\n0";
            return 0;
        }
    }

    // liczymy ilosc nieustalonych skladowych
    int niepewne_skladowe = 0;
    for (int z = 1; z <= n; z++) {
        if (vis[z]) continue;

        // zalozmy ze z stoi na pierwszym polu
        if (!pole_zajete_przez[poz_1[z]]) {
            pole_zajete_przez[poz_1[z]] = z;
            odpowiedzi[z] = poz_1[z];
        }
        else if (!pole_zajete_przez[poz_2[z]]) {
            pole_zajete_przez[poz_2[z]] = z;
            odpowiedzi[z] = poz_2[z];
        }
        else {
            std::cout << "NIE\n0";
            return 0;
        }

        bool sprzeczny = bfs(z);
        if (sprzeczny) {
            std::cout << "NIE\n0";
            return 0;
        }
        
        niepewne_skladowe++;
    }

    if (niepewne_skladowe == 0) {
        std::cout << "TAK\n";
        for (int z = 1; z <= n; z++) std::cout << odpowiedzi[z] << '\n';
    }
    else {
        ull kombinacje = 1;
        while (niepewne_skladowe--) (kombinacje *= 2) %= mod;
        std::cout << "NIE\n" << kombinacje;
    }
}
