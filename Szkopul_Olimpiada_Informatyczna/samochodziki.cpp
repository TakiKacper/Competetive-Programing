#include <iostream>
#include <queue>
#include <bitset>

// sposrod k na ziemi wywalamy ten
// ktory wystepuje najdalej w ciagu

constexpr int max_n = 100000;

int n, k, p; // samochodzik, nastepne wystapienie (-1 jezeli juz jest ostatnim)
std::vector<std::pair<int, int>> ciag;

void laduj() {
    std::cin >> n >> k >> p;
    std::vector<int> poprzednie_wystapienia(max_n, -1);

    ciag.resize(p);
    for (int i = 0; i < p; i++) {
        int x; std::cin >> x;

        if (poprzednie_wystapienia[x] != -1) {
            ciag[poprzednie_wystapienia[x]].second = i;
        }

        poprzednie_wystapienia[x] = i;
        ciag[i] = {x, -1};
    }
}

// drzewo trzymajace najdalszy samochodzik
// first - auto, second - dystans
constexpr int rounded_n = (1 << 17);
std::pair<int, int> nastepne[2 * rounded_n];

void push(std::pair<int, int> S) {
    int v = S.second == -1 ? (int)1e6 + 128 : S.second;
    int p = S.first + rounded_n;

    S.second = v;
    nastepne[p] = S;

    p /= 2;
    while (p != 0) {
        auto l = nastepne[p * 2];
        auto r = nastepne[p * 2 + 1];
        nastepne[p] = (l.second > r.second) ? l : r;
        p /= 2;
    }
}

std::pair<int, int> get_top() {
    return nastepne[1];
}

int rozwiaz() {
    std::bitset<max_n> zdjete;
    int ilosc_zdjetych = 0;
    
    int wynik = 0;

    for (int i = 0; i < p; i++) {
        const auto& p = ciag[i];

        // mamy goscia
        if (zdjete[p.first]) {
            push({p.first, p.second});
        }
        // nie mamy
        else {
            wynik++;

            // cos musimy oddac
            if (ilosc_zdjetych >= k) {
                auto t = get_top();
                zdjete[t.first] = false;
                ilosc_zdjetych--;
                push({t.first, 0});
            }

            ilosc_zdjetych++;
            zdjete[p.first] = true;
            push(p);
        }
    }

    return wynik;
}

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    
    laduj();
    int wynik = rozwiaz();

    std::cout << wynik;
}
