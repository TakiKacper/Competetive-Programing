#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

// maja k prawnikow ongoing
// wybieramy k o najdlaszym koncu
// trzymamy set koncow
// wybieramy k'ty od konca

constexpr int max_n = 1e6 + 1;

struct granica {
    int  prawnik;
    uint wartosc;
    bool poczatek;

    uint drugi_koniec;
};

granica G[2 * max_n];

bool operator<(const granica& a, const granica& b) {
    if (a.wartosc != b.wartosc) return a.wartosc < b.wartosc;
    return a.poczatek > b.poczatek; // poczatki daj pierwsze
}

struct prawnik {
    int  numer;
    uint poczatek;
};

bool operator<(const prawnik& a, const prawnik& b) {
    if (a.poczatek != b.poczatek) return a.poczatek < b.poczatek;
    return a.numer < b.numer;
}

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    int n, k; std::cin >> n >> k;

    for (int i = 0; i < n; i++) {
        granica g;  g.prawnik = i;
        std::cin >> g.wartosc >> g.drugi_koniec;
        
        g.poczatek = true;
        G[2 * i] = g;

        g.poczatek = false;
        std::swap(g.wartosc, g.drugi_koniec);
        G[2 * i + 1] = g;
    }

    std::sort(G, G + 2 * n);
    
    int               odp_dlugosc = 0;

    std::set<prawnik> ongoing_left; // <= k
    std::set<prawnik> ongoing_right;

    int koniec_ktorego_prawnika = 0;

    for (int i = 0; i < 2 * n; i++) {
        auto g = G[i];

        prawnik p;
        p.numer    = g.prawnik;
        p.poczatek = std::min(g.wartosc, g.drugi_koniec);

        if (g.poczatek) {
            if (ongoing_left.size() < k)
                ongoing_left.insert(p);
            else if (p < *(--ongoing_left.end())) {
                ongoing_right.insert(*(--ongoing_left.end()));
                ongoing_left.erase(--ongoing_left.end());
                ongoing_left.insert(p);
            }
            else {
                ongoing_right.insert(p);
            }
        }
        else {
            // wybieramy k o najwczesniejszym poczatku
            if (ongoing_left.size() >= k) {
                uint poczatek = (--ongoing_left.end())->poczatek;
                uint koniec   = g.wartosc;

                if (koniec - poczatek > odp_dlugosc) {
                    koniec_ktorego_prawnika = p.numer;
                   // odp_prawnicy.clear();
                   odp_dlugosc = koniec - poczatek;
                   // for (auto p : ongoing_left) odp_prawnicy.push_back(p.numer);
                }
            }

            if (auto itr = ongoing_left.find(p); itr != ongoing_left.end()) {
                ongoing_left.erase(itr);

                if (ongoing_right.size()) {
                    ongoing_left.insert(*ongoing_right.begin());
                    ongoing_right.erase(ongoing_right.begin());
                }
            }
            else {
                ongoing_right.erase(p);
            }
        }
    }

    // drugie przejscie
    std::set<prawnik> ongoing_prawnicy;
    for (int i = 0; i < 2 * n; i++) {
        auto g = G[i];

        prawnik p;
        p.numer    = g.prawnik;
        p.poczatek = std::min(g.wartosc, g.drugi_koniec);

        if (g.poczatek) {
            ongoing_prawnicy.insert(p);
        }
        else {
            if (p.numer == koniec_ktorego_prawnika) {
                std::cout << odp_dlugosc << '\n';

                auto itr = ongoing_prawnicy.begin();
                for (int i = 0; i < k; i++) {
                    std::cout << (itr->numer + 1) << ' ';
                    itr++;
                }

                return 0;
            }
            ongoing_prawnicy.erase(p);
        }
    }
}
