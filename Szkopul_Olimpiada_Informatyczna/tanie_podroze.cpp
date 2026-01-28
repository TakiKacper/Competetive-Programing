#include <iostream>
#include <vector>

struct stan {
    int poprzedni = -1;
    int dzien     = __INT_MAX__ - 100;
    int koszt     = __INT_MAX__ - 100;
};

// stan to najlepszy sposob PRZYBYCIA do danego miejsca
stan dp_najszybsze[1002];
stan dp_najtansze[1002];

struct hotel {
    int dystans;
    int koszt;
};

int d, h;
hotel H[1002];

struct szybkosc_first {
    bool operator()(const stan& a, const stan& b) const {
        if (a.dzien != b.dzien) return a.dzien < b.dzien;
        return a.koszt < b.koszt;
    }
};

struct koszt_first {
    bool operator()(const stan& a, const stan& b) const {
        if (a.koszt != b.koszt) return a.koszt < b.koszt;
        return a.dzien < b.dzien;
    }
};

template<class comp>
void generuj_dp(stan* dp) {
    dp[0].dzien     = 0;
    dp[0].koszt     = 0;
    dp[0].poprzedni = -1;

    for (int i = 0; i <= h + 1; i++) {
        stan cpy = dp[i];

        cpy.dzien     += 1;
        cpy.koszt     += H[i].koszt;
        cpy.poprzedni = i;
        
        int max_dst = H[i].dystans + 800;
        int j = i + 1;

        while (j <= h + 1 && H[j].dystans <= max_dst) {
            // proponujemy stan dla j hotelu
            if (comp{}(cpy, dp[j])) {
                dp[j] = cpy;
            }

            j++;
        }
    }
}

void wypisz_trase(stan* dp) {
    std::vector<int> trasa;

    int p = dp[h + 1].poprzedni;
    while (p != 0) {
        trasa.push_back(H[p].dystans);
        p = dp[p].poprzedni;
    }

    for (auto itr = trasa.rbegin(); itr != trasa.rend(); itr++) 
        std::cout << *itr << ' ';
    
    std::cout << '\n';
}

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    std::cin >> d >> h;

    H[0].dystans = 0;
    H[0].koszt   = 0;

    H[h + 1].dystans = d;
    H[h + 1].koszt   = 0;

    for (int i = 1; i <= h; i++) std::cin >> H[i].dystans >> H[i].koszt;

    generuj_dp<koszt_first>(dp_najtansze);
    generuj_dp<szybkosc_first>(dp_najszybsze);

    wypisz_trase(dp_najtansze);
    wypisz_trase(dp_najszybsze);
}
