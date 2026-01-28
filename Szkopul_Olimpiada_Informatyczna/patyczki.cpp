#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

using ull = unsigned long long;

struct patyk {
    ull     dlugosc;
    uint8_t kolor;
};

bool operator<(const patyk& a, const patyk& b) {
    if (a.dlugosc != b.dlugosc) return a.dlugosc < b.dlugosc;
    return a.kolor < b.kolor;
}

patyk patyki[(int)1e6 + 1];

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    int k; std::cin >> k;

    int N = 0; // ilosc wszystkich patykow
    for (uint8_t i = 1; i <= k; i++) {
        int n; std::cin >> n;

        for (int j = 0; j < n; j++) {
            ull x; std::cin >> x;
            patyki[N + j] = {x, i};
        }

        N += n;
    }

    std::sort(patyki, patyki + N);

    if (N < 3) {
        std::cout << "NIE";
        return 0;
    }

    int p1 = 0;
    int p2 = 1;
    int p3 = 2;

    while (p3 < N) {
        bool konstukcja = (
            patyki[p1].dlugosc + patyki[p2].dlugosc > patyki[p3].dlugosc
        );

        bool roznokolorowosc = (
            patyki[p1].kolor != patyki[p2].kolor &&
            patyki[p1].kolor != patyki[p3].kolor &&
            patyki[p2].kolor != patyki[p3].kolor
        );

        if (konstukcja && roznokolorowosc) {
            std::cout 
                << (int)patyki[p1].kolor << ' ' << patyki[p1].dlugosc << ' '
                << (int)patyki[p2].kolor << ' ' << patyki[p2].dlugosc << ' '
                << (int)patyki[p3].kolor << ' ' << patyki[p3].dlugosc << '\n';

            return 0;
        }

        // dolaczamy nowy patyczek
        // proboujemy nim zastapic kolidujcy kolor
        int p = p3 + 1;

        if (patyki[p].kolor != patyki[p3].kolor && patyki[p].kolor != patyki[p2].kolor) {
            p1 = p2;
            p2 = p3;
            p3 = p;
        }

        if (patyki[p].kolor == patyki[p2].kolor) {
            p2 = p3;
            p3 = p;
        }

        if (patyki[p].kolor == patyki[p3].kolor) {
            p3 = p;
        }
    }

    std::cout << "NIE\n";
}
